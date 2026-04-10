# Add-TypeDocComments.ps1
#
# PURPOSE
#   Adds Doxygen /** ... */ doc comments to undocumented DECLARE_DELEGATE_*
#   invocations and to undocumented UENUM / enum class declarations in all
#   ServerAPI handler header files.
#
#   Without doc comments, Doxygen will not create documentation entries for
#   these types (EXTRACT_ALL = NO, HIDE_UNDOC_MEMBERS = YES), so they cannot
#   be linked from function-signature parameter types.
#
# WHEN TO RUN
#   Run this script whenever new DECLARE_DELEGATE_* declarations or new enum
#   classes are added to a ServerAPI handler file without a doc comment.
#   Run from the repo root:
#       powershell -File .doxygen/scripts/Add-TypeDocComments.ps1 [-DryRun]
#
#   -DryRun: list what would be added without modifying files.
#
# ADDING NEW ENUM DESCRIPTIONS
#   Add the new enum name and its one-sentence description to $enumDescriptions
#   below.  The description should complete the sentence "This enum specifies..."
#   but be written as a standalone fragment (e.g. "Status values for X.").

param([switch]$DryRun)

$enc = New-Object System.Text.UTF8Encoding($false)

# One-sentence descriptions for each file-scope enum class that may lack a
# doc comment.  Add new entries here whenever new enums are introduced.
$enumDescriptions = [ordered]@{
    # LootLockerServerBalanceRequest.h
    "ELootLockerServerWalletHolderTypes"              = "Entity types that can hold a wallet."

    # LootLockerServerLeaderboardRequest.h
    "ELootLockerServerLeaderboardType"                = "Types of leaderboards."
    "ELootLockerServerLeaderboardDirection"           = "Sort direction for leaderboard entries."
    "ELootLockerServerLeaderboardRewardEntityKind"    = "Entity kinds that can be given as leaderboard rewards."

    # LootLockerServerMetadataRequest.h
    "ELootLockerServerMetadataSources"                = "Sources that can own metadata entries."
    "ELootLockerServerMetadataTypes"                  = "Value types for metadata entries."
    "ELootLockerServerMetadataActions"                = "Batch-write operations available for metadata entries."
    "ELootLockerServerMetadataParserOutputTypes"      = "Output types produced by the metadata content parser."

    # LootLockerServerNotificationsRequest.h
    "ELootLockerServerNotificationPriority"           = "Priority levels for notifications."

    # LootLockerServerPlayerRequest.h
    "ELootLockerServerCreatePlayerPlatforms"          = "Platform identifiers for creating a player."
    "ELootLockerServerPlayerNameLookupIdType"         = "Identifier types accepted when looking up player data."
}

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

function IsAlreadyDocumented {
    param([string[]]$Lines, [int]$LineIndex)
    # Walk backward from $LineIndex-1, skipping blank lines and Doxygen group
    # directive lines (/// @addtogroup, /// @{, /// @}, /// @ingroup, etc.)
    $j = $LineIndex - 1
    while ($j -ge 0) {
        $l = $Lines[$j]
        if ($l -match '^\s*$') { $j--; continue }            # blank
        if ($l -match '^\s*///\s*@') { $j--; continue }      # /// @addtogroup / @{ / @}
        break
    }
    if ($j -lt 0) { return $false }
    $l = $Lines[$j]
    # Treat as documented if the preceding significant line closes a /** */ block
    # OR is a /// single-line doc comment.
    return ($l -match '\*/\s*$' -or $l -match '^\s*///')
}

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

$base           = "LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI"
$files          = Get-ChildItem $base -Filter "*.h"
$totalDelegates = 0
$totalEnums     = 0

foreach ($f in $files) {
    $lines      = [IO.File]::ReadAllLines($f.FullName, $enc)
    # Key = line index to insert BEFORE; Value = comment string to insert.
    # Using generic Dictionary; we'll sort descending before applying.
    $insertions = [System.Collections.Generic.Dictionary[int,string]]::new()

    # ------------------------------------------------------------------
    # Pass 1 — DECLARE_DELEGATE_* without doc comments
    # ------------------------------------------------------------------
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -notmatch '^\s*DECLARE_DELEGATE_\w+\s*\(') { continue }

        # Parse delegate name (arg 0) and first type argument (arg 1).
        if ($lines[$i] -notmatch 'DECLARE_DELEGATE_\w+\s*\(\s*(\w+)\s*,\s*(\w+)') { continue }
        $responseType = $Matches[2]

        if (IsAlreadyDocumented -Lines $lines -LineIndex $i) { continue }

        $comment = "/** C++ response callback delegate; receives an @ref $responseType result. */"
        if (-not $insertions.ContainsKey($i)) {
            $insertions[$i] = $comment
            $totalDelegates++
        }
    }

    # ------------------------------------------------------------------
    # Pass 2 — enum class E… without doc comments
    # ------------------------------------------------------------------
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -notmatch '^\s*enum\s+class\s+(E\w+)') { continue }
        $enumName = $Matches[1]

        $desc = $enumDescriptions[$enumName]
        if (-not $desc) {
            Write-Warning "$($f.Name): no description for $enumName (add it to enumDescriptions)"
            continue
        }

        # Locate the UENUM line that precedes this enum class (if any).
        # That is the line we want the doc comment to go before.
        $uenumIdx = $i - 1
        while ($uenumIdx -ge 0 -and $lines[$uenumIdx] -match '^\s*$') { $uenumIdx-- }
        $insertAt = if ($uenumIdx -ge 0 -and $lines[$uenumIdx] -match '^\s*UENUM\s*\(') {
            $uenumIdx
        } else {
            $i
        }

        if (IsAlreadyDocumented -Lines $lines -LineIndex $insertAt) { continue }

        $comment = "/** $desc */"
        if (-not $insertions.ContainsKey($insertAt)) {
            $insertions[$insertAt] = $comment
            $totalEnums++
        }
    }

    # ------------------------------------------------------------------
    # Apply insertions bottom → top so earlier line indices stay valid
    # ------------------------------------------------------------------
    if ($insertions.Count -eq 0) {
        Write-Verbose "$($f.Name): nothing to add"
        continue
    }

    $label = if ($DryRun) { "[DRY RUN]" } else { "" }
    Write-Host "$label $($f.Name): inserting $($insertions.Count) doc comment(s)"
    foreach ($kvp in ($insertions.GetEnumerator() | Sort-Object Key -Descending)) {
        if ($DryRun) {
            Write-Host "  line $($kvp.Key + 1): $($kvp.Value)"
        }
    }

    if (-not $DryRun) {
        $out = [System.Collections.Generic.List[string]]::new($lines)
        foreach ($kvp in ($insertions.GetEnumerator() | Sort-Object Key -Descending)) {
            $out.Insert($kvp.Key, $kvp.Value)
        }
        [IO.File]::WriteAllBytes(
            $f.FullName,
            $enc.GetBytes(($out -join "`n") + "`n")
        )
    }
}

$dryMsg = if ($DryRun) { " (dry run - no files modified)" } else { "" }
Write-Host ""
Write-Host "Done$dryMsg. Added $totalDelegates delegate comment(s) and $totalEnums enum comment(s)."
