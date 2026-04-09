# Add-TypeDocComments.ps1
#
# PURPOSE
#   Adds Doxygen /** ... */ doc comments to undocumented DECLARE_DELEGATE_*
#   invocations and to undocumented UENUM / enum class declarations in all
#   GameAPI handler header files.
#
#   Without doc comments, Doxygen will not create documentation entries for
#   these types (EXTRACT_ALL = NO, HIDE_UNDOC_MEMBERS = YES), so they cannot
#   be linked from function-signature parameter types.
#
# WHEN TO RUN
#   Run this script whenever new DECLARE_DELEGATE_* declarations or new enum
#   classes are added to a GameAPI handler file without a doc comment.
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
    # LootLockerAssetsRequestHandler.h
    "ELootLockerAssetFilter"                       = "Filters applicable when querying the asset list."
    "ELootLockerOrderAssetListBy"                  = "Fields by which an asset list can be ordered."
    "ELootLockerOrderAssetListDirection"           = "Sort direction when ordering an asset list."

    # LootLockerAuthenticationRequestHandler.h
    "ELootLockerGoogleClientPlatform"              = "Google client platform identifiers for Google sessions."

    # LootLockerBalanceRequestHandler.h
    "ELootLockerWalletHolderTypes"                 = "Entity types that can hold a wallet."

    # LootLockerCatalogRequestHandler.h
    "ELootLockerCatalogEntryEntityKind"            = "Entity kinds that can appear as entries in a catalog."

    # LootLockerConnectedAccountsRequestHandler.h
    "ELootLockerAccountProvider"                   = "Third-party providers available for connected accounts."
    "EGoogleAccountProviderPlatform"               = "Platform subtype for Google connected accounts."

    # LootLockerEntitlementRequestHandler.h
    "ELootLockerEntitlementHistoryListingStore"    = "Stores from which entitlement history entries can originate."
    "ELootLockerEntitlementHistoryListingStatus"   = "Status values for entitlement history entries."
    "ELootLockerEntitlementHistoryListingType"     = "Types of entitlement history listing entries."
    "ELootLockerEntitlementRewardEntityKind"       = "Entity kinds that can be provided as entitlement rewards."

    # LootLockerFeedbackRequestHandler.h
    "ELootLockerFeedbackType"                      = "Feedback category types that can be submitted."

    # LootLockerLeaderboardRequestHandler.h
    "ELootLockerLeaderboardRewardEntityKind"       = "Entity kinds that can be given as leaderboard rewards."

    # LootLockerMetadataRequestHandler.h
    "ELootLockerMetadataSources"                   = "Sources that can own metadata entries."
    "ELootLockerMetadataTypes"                     = "Value types for metadata entries."
    "ELootLockerMetadataActions"                   = "Batch-write operations available for metadata entries."
    "ELootLockerMetadataParserOutputTypes"         = "Output types produced by the metadata content parser."

    # LootLockerNotificationsRequestHandler.h
    "ELootLockerNotificationPriority"              = "Priority levels for notifications."
    "ELootLockerNotificationSource"                = "Sources that can originate a notification."
    "ELootLockerNotificationContentBodyType"       = "Content body types within a notification payload."
    "ELootLockerNotificationContentRewardKind"     = "Reward kinds that can be attached to a notification."
    "ELootLockerCustomNotificationFiltering"       = "Filtering modes for listing custom notifications."

    # LootLockerPlayerRequestHandler.h
    "ELootLockerPlayerDataLookupIdType"            = "Identifier types accepted when looking up player data."

    # LootLockerPurchasesRequestHandler.h
    "ELootLockerSteamPurchaseRedemptionStatus"     = "Status values for a Steam purchase redemption."
    "ELootLockerRefundInventoryEventAction"        = "Actions that can be taken on an inventory refund event."
    "ELootLockerRefundNonReversibleRewardKind"     = "Kinds of non-reversible rewards involved in a refund."
    "ELootLockerRefundWarningDetailType"           = "Warning detail types returned during a refund operation."
    "ELootLockerAsyncPurchaseStatus"               = "Status values for an asynchronous purchase."

    # LootLockerRemoteSessionRequestHandler.h
    "ELootLockerRemoteSessionLeaseStatus"          = "Status values for a remote session lease."
    "ELootLockerRemoteSessionLeaseIntent"          = "Intent options when leasing a remote session."

    # LootLockerTriggersRequestHandler.h
    "ELootLockerTriggerFailureReasons"             = "Reasons a trigger invocation can fail."

    # LootLockerUserGeneratedContentRequestHandler.h
    "ELootLockerAssetFilePurpose"                  = "Purpose values for files attached to an asset candidate."
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

$base           = "LootLockerSDK/Source/LootLockerSDK/Public/GameAPI"
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
