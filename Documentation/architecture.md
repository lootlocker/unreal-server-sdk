# Unreal Server SDK Architecture

This document describes the internal structure of the LootLocker **Unreal Server SDK** so contributors (and coding agents) can place changes correctly and avoid unintended public API expansion.

## What this repo is
- **Type:** Unreal Engine **plugin** (`LootLockerServerSDK/LootLockerServerSDK.uplugin`)
- **Integration:** Copy the `LootLockerServerSDK/` folder into a game’s `Plugins/` directory and add `LootLockerServerSDK` as a dependency in the game module.
- **Distribution model:** Compiled Unreal modules (not a standalone library, not header-only).

## Repo map (real paths)

Top level:
- `LootLockerServerSDK/` — Unreal plugin root
  - `LootLockerServerSDK.uplugin` — plugin descriptor (modules, version, metadata)
  - `Source/` — module source
    - `LootLockerServerSDK/` — runtime module
      - `LootLockerServerSDK.Build.cs`
      - `Public/` — **public API surface**
      - `Private/` — implementation
      - `Tests/` — Unreal automation tests
    - `LootLockerServerSDKEditor/` — editor module
      - `LootLockerServerSDKEditor.Build.cs`
      - `Public/`, `Private/` — editor-only tooling
  - `Config/` — plugin defaults / redirects
  - `Binaries/`, `Intermediate/` — build outputs (do not edit)

## Modules and boundaries

### Runtime module: `LootLockerServerSDK`
Path: `LootLockerServerSDK/Source/LootLockerServerSDK/`

Responsibilities:
- Public API for game/runtime code (C++ and Blueprints)
- Endpoint catalog and URL formatting
- HTTP transport (Unreal `HTTP` module)
- JSON serialization/deserialization (`JsonUtilities` via `FJsonObjectConverter`)
- Auth/session token state
- Logging and request context capture

Key directories:
- Public API: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/`
- Implementation: `LootLockerServerSDK/Source/LootLockerServerSDK/Private/`
- Feature request implementations:
  - Headers: `.../Public/ServerAPI/*.h`
  - Sources: `.../Private/ServerAPI/*.cpp`

### Editor module: `LootLockerServerSDKEditor`
Path: `LootLockerServerSDK/Source/LootLockerServerSDKEditor/`

Responsibilities:
- Editor-only UX/tooling (Slate/UnrealEd)
- Depends on the runtime module (`LootLockerServerSDKEditor.Build.cs` lists `LootLockerServerSDK`)

Rule of thumb:
- If it must run in a packaged game/server build, it belongs in the runtime module.
- If it is editor UI, visualization, menus, or developer tooling, it belongs in the editor module.

## Public headers boundary (public API)

Everything under `LootLockerServerSDK/Source/LootLockerServerSDK/Public/` is part of the module’s public interface.

High-impact headers (widely included by consumers):
- `.../Public/LootLockerServerForCpp.h` — high-level C++ facade aggregating most requests
- `.../Public/LootLockerServerForBlueprints.h` — high-level Blueprint facade aggregating most requests
- `.../Public/ServerAPI/*.h` — request/response models and request entrypoints

Guidance:
- Prefer to keep implementation helpers in `Private/`.
- Adding new headers to `Public/` (or adding includes to the large facade headers) is an API and build-time decision; keep it intentional.

## Transport, serialization, auth

### HTTP transport
- Central transport is `ULootLockerServerHttpClient`:
  - Header: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerHttpClient.h`
  - Impl: `LootLockerServerSDK/Source/LootLockerServerSDK/Private/LootLockerServerHttpClient.cpp`

Implementation notes:
- Uses Unreal’s `FHttpModule` / `IHttpRequest`.
- Requests are asynchronous and completed via `OnProcessRequestComplete()` delegates.
- Request IDs are generated with `FGuid` and returned to callers.

### Endpoints and URL construction
- Endpoint catalog lives in:
  - `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerEndpoints.h`
  - `LootLockerServerSDK/Source/LootLockerServerSDK/Private/LootLockerServerEndpoints.cpp`

Notes:
- Base URL is chosen via compile-time define `LOOTLOCKER_USE_STAGE_URL` (wired in `LootLockerServerSDK.Build.cs`).
- Endpoints use format strings and ordered path parameters (`{0}`, `{1}`, …).
- Domain key injection is handled when formatting the endpoint in the HTTP client.

### JSON / serialization
Primary serialization/deserialization:
- `FJsonObjectConverter` (`JsonUtilities`) is used in `LootLockerServerHttpClient`:
  - Serialize request structs to JSON strings.
  - Parse JSON response strings into response structs.

Utility helpers:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/Utils/LootLockerServerUtilities.h`
- `LootLockerServerSDK/Source/LootLockerServerSDK/Private/Utils/LootLockerServerUtilities.cpp`

### Auth / session handling
- Start/maintain server session:
  - `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/LootLockerServerAuthRequest.h`
  - `LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/LootLockerServerAuthRequest.cpp`

Token storage:
- In-memory token: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerStateData.h` (implementation in `Private/`)
- Persistable shape: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerPersistedState.h`

Header behavior:
- `StartSession` sends `x-server-key` from `ULootLockerServerConfig`.
- The HTTP client adds `x-auth-token` when a server token exists.

OAuth token exchange:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/LootLockerServerOAuthRequest.h`
- `LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/LootLockerServerOAuthRequest.cpp`

## Call flow (typical request)

1. Consumer calls a high-level facade method:
   - C++: `ULootLockerServerForCpp::SomeOperation(...)`
   - Blueprint: `ULootLockerServerForBlueprints::SomeOperation(...)`
2. Facade forwards to a per-feature request class in `Public/ServerAPI/*`.
3. Request selects an endpoint from `ULootLockerServerEndpoints`.
4. Request calls `ULootLockerServerHttpClient::SendRequest` / `SendRawRequest`.
5. HTTP client:
   - Formats URL (+ domain key, path params, query params)
   - Applies headers (`x-auth-token`, request-specific headers)
   - Serializes request struct with `FJsonObjectConverter`
6. Completion callback receives a typed response struct; errors populate `FLootLockerServerErrorData`.

## Where do I implement X? (decision table)

| Change you need | Put it here | Notes |
|---|---|---|
| Add a new endpoint URL/method | `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerEndpoints.h` + `.../Private/LootLockerServerEndpoints.cpp` | Add the `FLootLockerServerEndPoint` static and initialize in `.cpp`. |
| Add a new API call (feature request class) | `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/<Feature>Request.h` + `.../Private/ServerAPI/<Feature>Request.cpp` | Follow existing pattern: `USTRUCT` models + `static` request functions returning request id. |
| Add request/response models | `.../Public/ServerAPI/<Feature>Request.h` | Keep fields `UPROPERTY`-annotated for BP where needed. |
| Wire a call into the C++ facade | `.../Public/LootLockerServerForCpp.h` + `.../Private/LootLockerServerForCpp.cpp` | Prefer adding only what’s needed; this header is widely included. |
| Wire a call into the Blueprint facade | `.../Public/LootLockerServerForBlueprints.h` + `.../Private/LootLockerServerForBlueprints.cpp` | Blueprint facade typically wraps the C++ facade using dynamic delegates. |
| Change auth/session behavior | `.../Public/ServerAPI/LootLockerServerAuthRequest.h` + `.../Private/ServerAPI/LootLockerServerAuthRequest.cpp` and/or `.../Public/LootLockerServerStateData.h` | Keep header semantics stable; token is applied as `x-auth-token`. |
| Change HTTP retry/logging/header behavior | `.../Public/LootLockerServerHttpClient.h` + `.../Private/LootLockerServerHttpClient.cpp` | Be careful: impacts every request. |
| Change JSON parsing/serialization helpers | `.../Public/Utils/LootLockerServerUtilities.h` + `.../Private/Utils/LootLockerServerUtilities.cpp` | Prefer adding narrowly-scoped helpers. |
| Add/adjust tests | `LootLockerServerSDK/Source/LootLockerServerSDK/Tests/` | Uses Unreal automation tests (see `Authentication.cpp`). |
| Add samples/examples | (None in-repo currently) | Prefer docs updates in `README.md` or add a dedicated samples folder only if requested. |

## Common pitfalls
- **Accidentally expanding public API:** adding new `Public/` headers or extra includes in `LootLockerServerForCpp.h`/`LootLockerServerForBlueprints.h` has wide impact.
- **Runtime/editor leakage:** don’t introduce Slate/UnrealEd dependencies into the runtime module.
- **Duplicating patterns:** many request classes already exist under `Public/ServerAPI/`; reuse conventions.
- **Touching build artifacts:** never edit `Binaries/` or `Intermediate/`.
- **Large refactors:** keep diffs minimal; prefer targeted changes.

## Guardrails
- Coding agent guardrails: `.github/agent-docs/guardrails.md`
