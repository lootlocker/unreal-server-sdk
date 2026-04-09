# Add-DelegateGroupTags.ps1
#
# PURPOSE
#   Wraps the DECLARE_DELEGATE section of each GameAPI handler file in a
#   Doxygen @addtogroup/@{ ... @} block so those typedefs are registered as
#   members of the correct feature group.  This makes delegate names clickable
#   in function signatures on the group documentation page.
#
# WHEN TO RUN
#   Run this script whenever a new GameAPI handler file is added to the SDK.
#   Add the new file and its group to $groupMap below, then run the script
#   from the repo root:
#       powershell -File .doxygen/scripts/Add-DelegateGroupTags.ps1
#
#   The script is idempotent for files that already have the correct tags.
#
# GROUPS
#   Group names must match the @defgroup names declared in .doxygen/groups.dox.

$enc = New-Object System.Text.UTF8Encoding($false)

# Map each handler file to its primary feature group.
# Group name must match a @defgroup declared in .doxygen/groups.dox.
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
$count = 0

foreach ($f in $files) {
    $group = $groupMap[$f.Name]
    if (-not $group) { Write-Warning "No group mapping for $($f.Name) - skipping (add it to groupMap)"; continue }

    $lines = [IO.File]::ReadAllLines($f.FullName, $enc)

    # Skip if already tagged
    if ($lines | Where-Object { $_ -match "/// @addtogroup $group" }) {
        Write-Host "$($f.Name) already tagged - skipping"
        continue
    }

    $firstDelegate = -1
    $uclassLine    = -1

    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($firstDelegate -lt 0 -and $lines[$i] -match '^\s*DECLARE_DELEGATE_') { $firstDelegate = $i }
    }

    if ($firstDelegate -lt 0) { Write-Warning "No DECLARE_DELEGATE in $($f.Name) - skipping"; continue }

    # Find the first UCLASS() that appears AFTER the delegate declarations
    for ($i = $firstDelegate; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match '^\s*UCLASS\s*\(') { $uclassLine = $i; break }
    }

    # Walk backward from firstDelegate to include any preceding doc comment block
    # inside the group (@addtogroup/@{ go before the /** comment, not before DECLARE_DELEGATE)
    $groupOpenAt = $firstDelegate
    $k = $firstDelegate - 1
    while ($k -ge 0 -and $lines[$k] -match '^\s*$') { $k-- }
    if ($k -ge 0 -and $lines[$k] -match '^\s*\*/') {
        while ($k -ge 0 -and $lines[$k] -notmatch '^\s*/\*\*') { $k-- }
        if ($k -ge 0) { $groupOpenAt = $k }
    }

    # Walk backward from UCLASS to find where to close the group
    $closeAt = $uclassLine
    if ($uclassLine -gt 0) {
        $j = $uclassLine - 1
        while ($j -ge 0 -and $lines[$j] -match '^\s*$') { $j-- }
        if ($j -ge 0 -and $lines[$j] -match '^\s*\*/') {
            while ($j -ge 0 -and $lines[$j] -notmatch '^\s*/\*\*') { $j-- }
            if ($j -ge 0) { $closeAt = $j }
        }
    }

    $out = [System.Collections.Generic.List[string]]::new()
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($i -eq $groupOpenAt) {
            $out.Add("/// @addtogroup $group")
            $out.Add("/// @{")
        }
        if ($uclassLine -gt 0 -and $i -eq $closeAt) {
            $out.Add("/// @}")
        }
        $out.Add($lines[$i])
    }

    if ($uclassLine -lt 0) {
        while ($out.Count -gt 0 -and $out[$out.Count-1] -eq '') { $out.RemoveAt($out.Count-1) }
        $out.Add("/// @}")
        $out.Add("")
    }

    [IO.File]::WriteAllBytes($f.FullName, $enc.GetBytes(($out -join "`n") + "`n"))
    $count++
    Write-Host "Tagged $($f.Name) -> $group"
}

Write-Host "Done. Tagged delegate sections in $count files."
