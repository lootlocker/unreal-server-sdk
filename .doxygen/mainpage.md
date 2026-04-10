@mainpage LootLocker Unreal Server SDK — API Reference

@image html lootlocker-logo.png width=280px

[LootLocker](https://lootlocker.com) is a **game backend-as-a-service** that ships fully-managed, cross-platform
systems so your team can focus on making the game instead of maintaining infrastructure.
This reference covers every public method and type in the **server-side** C++ SDK.

The Server SDK runs on your **game server or trusted backend** and authenticates with a
Server API Key. Use it to manage players, award items and currency, fire triggers, and
interact with leaderboards authoritatively — without trusting the game client.

---

@section mainpage_quickstart Quick Start

**1. Install**

Add the plugin to your server project's `Plugins/` folder.
Enable the **LootLockerServerSDK** plugin in **Edit → Plugins**.

**2. Configure**

Open **Edit → Project Settings → LootLocker Server SDK** and paste your **Server API Key**
from the [LootLocker console](https://console.lootlocker.com/settings/api-keys).

**3. Start a session**

```cpp
ULootLockerServerAuthRequest::StartSession(
    FLootLockerServerAuthResponseDelegate::CreateLambda([](FLootLockerServerAuthenticationResponse Response)
    {
        if (!Response.Success)
        {
            UE_LOG(LogTemp, Warning, TEXT("Server session failed: %s"), *Response.ErrorData.Message);
            return;
        }
        UE_LOG(LogTemp, Log, TEXT("Server session started"));
    })
);
```

All SDK calls are **static methods on the request handler classes** and return results
asynchronously via a delegate callback whose first argument derives from
@ref FLootLockerServerResponse.
Check `Response.Success` before accessing the payload fields.

---

@section mainpage_navigation Navigating This Reference

The **Topics** tab (left sidebar or top nav) is the recommended entry point.
Methods are grouped by feature — start there to find everything related to a
particular system without needing to know which class or file it lives in.

| Topic | What it covers |
|-------|---------------|
| @ref Init "Initialization" | Configure and start a server session before calling any other API. |
| @ref Authentication "Authentication" | Start and manage a server session with the LootLocker backend. |
| @ref TokenExchange "Token Exchange" | Exchange player-held game API tokens for use on the server. |
| @ref Player "Player" | Manage player profiles and accounts from the server. |
| @ref PlayerFiles "Player Files" | Server-side management of CDN-backed files scoped to a player's profile. |
| @ref PlayerStorage "Player Storage" | Server-side read and write of a player's persistent key-value store. |
| @ref Friends "Friends" | Query and manage player friend lists from the server. |
| @ref ConnectedAccounts "Connected Accounts" | Server-side management of linked platform accounts. |
| @ref Hero "Hero" | Server-side management of player hero instances. |
| @ref Characters "Characters" | Server-side management of player characters. |
| @ref Currency "Currency" | Query virtual currency types from the server. |
| @ref Balances "Balances" | Read and adjust player currency balances from the server. |
| @ref DropTables "Drop Tables" | Server-side evaluation and claiming of weighted loot rolls. |
| @ref Assets "Assets" | Browse the asset catalogue from the server. |
| @ref AssetInstance "Asset Instances" | Server-side management of asset instances in players' inventories. |
| @ref PlayerProgressions "Player Progressions" | Award and query player progression tiers from the server. |
| @ref CharacterProgressions "Character Progressions" | Award and query per-character progression tiers from the server. |
| @ref AssetInstanceProgressions "Asset Instance Progressions" | Award and query progression tiers for a specific asset instance. |
| @ref Progressions "Progressions" | Definitions and infrastructure shared across all progression types. |
| @ref Leaderboard "Leaderboards" | Submit and read leaderboard scores from the server. |
| @ref Triggers "Triggers" | Fire named trigger events on behalf of players from the server. |
| @ref Metadata "Metadata" | Attach and retrieve typed key-value metadata on LootLocker entities. |
| @ref Notifications "Notifications" | Create and manage player event notifications from the server. |

---

@section mainpage_response Response Conventions

Every callback receives a response struct deriving from @ref FLootLockerServerResponse :

| Field | Type | Meaning |
|-------|------|---------|
| `Success` | `bool` | `true` when the request completed without error |
| `StatusCode` | `int` | HTTP status code |
| `ErrorData` | `FLootLockerServerErrorData` | Detail when `Success == false` |
| `FullTextFromServer` | `FString` | Raw JSON body for debugging |

Always check `Response.Success` before reading payload fields.

---

@section mainpage_links Useful Links

- [LootLocker Documentation](https://docs.lootlocker.com/)
- [Server API Reference (ApiDog)](https://ref.lootlocker.com/server)
- [LootLocker Console](https://console.lootlocker.com/)
- [GitHub — LootLocker Unreal Server SDK](https://github.com/lootlocker/unreal-server-sdk)
