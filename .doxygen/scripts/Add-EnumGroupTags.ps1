# Add-EnumGroupTags.ps1
#
# PURPOSE
#   Wraps each UENUM / enum class declaration in GameAPI handler files in a
#   Doxygen @addtogroup/@{ ... @} block so enumerations are registered as
#   group members.  Without this, file-scope enums have no linkable anchor
#   (because SOURCE_BROWSER = NO; file pages aren't generated).  Adding the
#   group tag causes enum types to appear in the group HTML with an anchor ID
#   that other pages can link to from function signatures.
#
# WHEN TO RUN
#   Run whenever a new enum class is added to a GameAPI handler file without
#   an @addtogroup wrapper:
#       powershell -File .doxygen/scripts/Add-EnumGroupTags.ps1
#
# NOTES
#   - Works together with Add-TypeDocComments.ps1 (which adds /** */ doc
#     comments before the enum class line).
#   - The JS nav filter already hides E/F-prefixed type names from the Topics
#     sidebar, so these enum entries won't clutter navigation.
#   - The script is idempotent: re-running it on already-tagged files is safe.
#
# GROUP MAP
#   Must match @defgroup names in .doxygen/groups.dox.

param([switch]$DryRun)

$enc = New-Object System.Text.UTF8Encoding($false)

$groupMap = @{
    "LootLockerAssetInstancesRequestHandler.h"       = "AssetInstance"
    "LootLockerAssetsRequestHandler.h"               = "Assets"
    "LootLockerAuthenticationRequestHandler.h"       = "Authentication"
    "LootLockerBalanceRequestHandler.h"              = "Balances"
    "LootLockerBroadcastRequestHandler.h"            = "Broadcasts"
    "LootLockerCatalogRequestHandler.h"              = "Catalog"
    "LootLockerCharacterRequestHandler.h"            = "Hero"
    "LootLockerCollectablesRequestHandler.h"         = "Collectables"
    "LootLockerConnectedAccountsRequestHandler.h"    = "ConnectedAccounts"
    "LootLockerCurrencyRequestHandler.h"             = "Currency"
    "LootLockerDropTablesRequestHandler.h"           = "DropTables"
    "LootLockerEntitlementRequestHandler.h"          = "Entitlements"
    "LootLockerFeedbackRequestHandler.h"             = "Feedback"
    "LootLockerFollowersRequestHandler.h"            = "Followers"
    "LootLockerFriendsRequestHandler.h"              = "Friends"
    "LootLockerHeroRequestHandler.h"                 = "Hero"
    "LootLockerLeaderboardArchiveRequestHandler.h"   = "Leaderboard"
    "LootLockerLeaderboardRequestHandler.h"          = "Leaderboard"
    "LootLockerMapsRequestHandler.h"                 = "Maps"
    "LootLockerMessagesRequestHandler.h"             = "Messages"
    "LootLockerMetadataRequestHandler.h"             = "Metadata"
    "LootLockerMiscellaneousRequestHandler.h"        = "Misc"
    "LootLockerMissionsRequestHandler.h"             = "Missions"
    "LootLockerNotificationsRequestHandler.h"        = "Notifications"
    "LootLockerPersistentStorageRequestHandler.h"    = "PlayerStorage"
    "LootLockerPlayerFilesRequestHandler.h"          = "PlayerFiles"
    "LootLockerPlayerRequestHandler.h"               = "Player"
    "LootLockerProgressionsRequestHandler.h"         = "Progressions"
    "LootLockerPurchasesRequestHandler.h"            = "Purchasing"
    "LootLockerRemoteSessionRequestHandler.h"        = "RemoteSessions"
    "LootLockerTriggersRequestHandler.h"             = "Triggers"
    "LootLockerUserGeneratedContentRequestHandler.h" = "UserGeneratedContent"
}

$base  = "LootLockerSDK/Source/LootLockerSDK/Public/GameAPI"
$files = Get-ChildItem $base -Filter "*.h"
$totalTagged = 0

foreach ($f in $files) {
    $group = $groupMap[$f.Name]
    if (-not $group) { Write-Warning "No group for $($f.Name) - skipping"; continue }

    $lines = [System.Collections.Generic.List[string]]::new(
        [IO.File]::ReadAllLines($f.FullName, $enc)
    )
    $fileTagged = 0

    # Walk bottom→top so insertions don't shift upcoming indices.
    $i = $lines.Count - 1
    while ($i -ge 0) {
        if ($lines[$i] -notmatch '^\s*enum\s+class\s+E\w+') { $i--; continue }

        # Already inside a group block?
        # Check preceding lines (above UENUM) for an unhclosed /// @{
        # Simple heuristic: if the line immediately before the UENUM (or
        # before the doc comment between UENUM and enum class) contains /// @{
        # then this enum is already tagged.
        $uenumIdx = $i - 1
        $inDocComment = $false
        while ($uenumIdx -ge 0 -and $lines[$uenumIdx] -notmatch '^\s*UENUM\s*\(') {
            $l = $lines[$uenumIdx]
            # Track state: are we inside a /** */ block?
            if (-not $inDocComment -and $l -match '\*/\s*$') { $inDocComment = $true }
            if ($inDocComment) {
                if ($l -match '/\*\*') { $inDocComment = $false }  # reached opening, done
                $uenumIdx--; continue
            }
            # Outside a doc comment: skip only blank lines
            if ($l -match '^\s*$') { $uenumIdx--; continue }
            break  # any other non-blank line → stop searching
        }
        if ($uenumIdx -lt 0 -or $lines[$uenumIdx] -notmatch '^\s*UENUM\s*\(') {
            # No UENUM line found above
            $i--; continue
        }

        # Check if UENUM is already preceded by /// @{
        $checkIdx = $uenumIdx - 1
        while ($checkIdx -ge 0 -and $lines[$checkIdx] -match '^\s*$') { $checkIdx-- }
        if ($checkIdx -ge 0 -and $lines[$checkIdx] -match '^\s*\/\/\/\s*@\{') {
            Write-Verbose "$($f.Name) line $($i+1): already tagged"
            $i = $uenumIdx - 1
            continue
        }

        # Find the closing brace of the enum body
        $closeIdx = $i + 1
        $depth = 0
        $found = $false
        while ($closeIdx -lt $lines.Count) {
            if ($lines[$closeIdx] -match '\{') { $depth++ }
            if ($lines[$closeIdx] -match '\}') {
                $depth--
                if ($depth -eq 0) { $found = $true; break }
            }
            $closeIdx++
        }
        if (-not $found) { $i--; continue }

        if ($DryRun) {
            Write-Host "[DRY RUN] $($f.Name) line $($i+1): would wrap in @addtogroup $group"
            $fileTagged++
            $i = $uenumIdx - 1
            continue
        }

        # Insert /// @} after the closing brace line
        $lines.Insert($closeIdx + 1, '/// @}')

        # Insert /// @addtogroup + /// @{ before the UENUM line
        $lines.Insert($uenumIdx, '/// @{')
        $lines.Insert($uenumIdx, "/// @addtogroup $group")

        $fileTagged++
        $totalTagged++

        # Jump above the newly inserted lines
        $i = $uenumIdx - 1
    }

    if ($fileTagged -gt 0 -and -not $DryRun) {
        [IO.File]::WriteAllBytes(
            $f.FullName,
            $enc.GetBytes(($lines -join "`n") + "`n")
        )
        Write-Host "$($f.Name): wrapped $fileTagged enum(s) in @addtogroup $group"
    }
}

$dryMsg = if ($DryRun) { " (dry run)" } else { "" }
Write-Host ""
Write-Host ("Done" + $dryMsg + '. Wrapped ' + $totalTagged + ' enum(s) in @addtogroup blocks.')
