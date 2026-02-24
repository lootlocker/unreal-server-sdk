# Unreal Server SDK — Conventions & Style Guide

This guide documents **how code in this repo is structured and written** so changes stay consistent, keep diffs small, and avoid accidentally expanding the public API.

Scope:
- Runtime module only unless explicitly asked: `LootLockerServerSDK/Source/LootLockerServerSDK/`
- **Docs-first, search-first:** reuse existing request/transport patterns.

## A) Public API boundaries (server SDK)

### Scoped path-specific instructions (recommended reading)

This repo uses path-specific custom instructions under `.github/instructions/**/*.instructions.md` to avoid leaking rules globally.

High-impact public interface files:
- `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForCpp.h.instructions.md`
- `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForBlueprints.h.instructions.md`

Request layer (ServerAPI):
- `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/ServerAPI.instructions.md`
- `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/ServerAPI.instructions.md`

### What is public API
Everything under:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/`

…is **public API**. Any change there should be treated as a compatibility and build-time decision.

High-impact facade headers (widely included by consumers):
- `.../Public/LootLockerServerForCpp.h`
- `.../Public/LootLockerServerForBlueprints.h`

### Rules for adding/changing public API

1) Prefer implementation in `Private/`
- Put request execution logic in `Private/ServerAPI/*.cpp`.
- Put internal helpers in `Private/Utils/`.

2) Be intentional when changing facade headers and avoid pulling new heavy includes into facade headers unless necessary.

3) Keep public headers “stable-shaped”
- Avoid renames or signature churn.
- Avoid moving types between files.
- Avoid drive-by formatting changes.

4) Treat public changes as API changes
- Any new `public` method, signature change, rename, or behavior change should be treated as an API change and should go through a deprecation period if needed.

### Documentation expectations (public-facing)

- **Facade methods** in `LootLockerServerForCpp.h` and `LootLockerServerForBlueprints.h` require rigorous method docs:
  - What it does (1–2 lines)
  - Link to API docs when available (often `https://ref.lootlocker.com/server-api/#...`)
  - Parameters: meaning + constraints (ranges, optionality, pagination behavior)
  - Return value: request id semantics (see below)
  - Auth/session requirements if relevant

- Request/response **data objects** (USTRUCTs used for JSON) should document fields clearly, especially when:
  - a field is optional/nullable
  - string-typed fields are used to represent optional numbers/bools
  - the server uses `Snake_case` naming (leading capital) that must be preserved

### Deprecation practices

Go through a deprecation flow when:
- A public method/DTO is going out of support.
- A public method/DTO signature has been updated in a way that is not backwards compatible.

How to deprecate (Unreal conventions):
- **C++ methods/types:** use `UE_DEPRECATED(<UE version>, "Deprecated on <YYYY-MM-DD>. Use <Replacement>.")` on the declaration where possible.
- **Blueprint-callable methods:** add `meta=(DeprecatedFunction, DeprecationMessage="Deprecated on <YYYY-MM-DD>. Use <Replacement>.")` to the `UFUNCTION`.
- **Deprecated fields:** prefer keeping serialized fields for compatibility; if a field must be discouraged, mark the `UPROPERTY` with `meta=(DeprecatedProperty, DeprecationMessage="...")`.

Process:
- Deprecations should be done in their own commits and explicitly stated.
- Deprecations require mention in release notes and an update of user-facing documentation.

## B) Request/response conventions

### Where request classes live
- Public API (types + entrypoints): `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/*.h`
- Implementations: `LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/*.cpp`

### Shape of a request header
Typically the header contains, in this order:
- `// Data Type Definitions` (USTRUCT models)
- `// Request Definitions` (USTRUCT request bodies)
- `// Response Definitions` (USTRUCT responses inheriting `FLootLockerServerResponse`)
- `// Delegate Definitions` (C++ delegates)
- `UCLASS` request object exposing `static` methods

### Delegates

C++ delegates (request layer):
- `DECLARE_DELEGATE_OneParam(FLootLockerServer<Operation>ResponseDelegate, FLootLockerServer<Operation>Response);`

Blueprint delegates (Blueprint facade layer):
- `DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerServer<Operation>ResponseBP, FLootLockerServer<Operation>Response, Response);`

Naming:
- Suffix `ResponseDelegate` for C++
- Suffix `ResponseBP` for Blueprint

### Return values: request id

Most request functions return a `FString` **request id**.
- The id comes from the HTTP client (`FGuid::NewGuid().ToString()`).
- Blueprint facades expose it as `UPARAM(DisplayName = "RequestId") FString ...`.

### USTRUCT / UPROPERTY rules (JSON + BP)

- Use `USTRUCT(BlueprintType)` for request/response/data models that are used in responses or Blueprint-facing APIs.
- Expose fields with `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")` where appropriate.

ServerAPI note:
- The request/response structs in `Public/ServerAPI/` are serialized/deserialized with `FJsonObjectConverter`.
- Preserve the existing backend field naming patterns and optional-field conventions in that folder.
- For the strict rules, see the path-specific ServerAPI instruction files referenced above.

## C) HTTP / JSON / auth conventions

### Central rule: use the HTTP client
All network calls should go through:
- `ULootLockerServerHttpClient` (`Public/LootLockerServerHttpClient.h`, `Private/LootLockerServerHttpClient.cpp`)

Use:
- `ULootLockerServerHttpClient::SendRequest<ResponseType>(RequestStruct, Endpoint, OrderedArgs, QueryParams, OnCompletedRequest, /*optional*/ ResponseInspector, /*optional*/ CustomHeaders)`
- `SendRawRequest` / `SendRawWWWFormUrlEncodedRequest` only when you must craft the body manually.

### Endpoints
- Endpoints are defined in `Public/LootLockerServerEndpoints.h` and initialized in `Private/LootLockerServerEndpoints.cpp`.
- Endpoints are `FLootLockerServerEndPoint` values created via `InitEndpoint("path", ELootLockerServerHTTPMethod::GET/POST/...)`.

### Path params and query params
- Path params are passed as ordered `TArray<FStringFormatArg>` and are URL-encoded by the HTTP client.
- Query params are passed as `TMultiMap<FString, FString>`.
  - Follow existing pattern: only add `count`, `after`, etc. if values are non-zero / non-empty.

### JSON serialization
- Requests and responses are serialized/deserialized via `FJsonObjectConverter`.
- The empty request body pattern is `FLootLockerServerEmptyRequest{}`.

### Auth headers and token handling

- `x-auth-token`
  - Automatically added by the HTTP client when `ULootLockerServerStateData::GetServerToken()` is non-empty.
  - Most requests should **not** manually add it.

- `x-server-key`
  - Used for `StartSession` via `CustomHeaders` from the auth request implementation.

- Token storage
  - In-memory token is stored in `ULootLockerServerStateData`.
  - `StartSession` uses a response-inspector callback to store the token.

### Error propagation
- Responses inherit from `FLootLockerServerResponse` and always populate:
  - `Success`, `StatusCode`, `FullTextFromServer`, `ErrorData`, `RequestContext`
- For non-success responses, the HTTP client attempts to parse `FLootLockerServerErrorData` from the body and also reads the `retry-after` header into `Retry_after_seconds`.

## D) Logging & secrets

Logging utilities:
- `FLootLockerServerLogger` (`Public/LootLockerServerLogger.h`, `Private/LootLockerServerLogger.cpp`)
- Runtime-configurable logging lives in `ULootLockerServerConfig` (file logging + runtime log level).

Do not log secrets:
- LootLocker server key (`LootLockerServerKey`)
- Auth token (`x-auth-token`, server session token)
- Any PII or customer data that can appear in request/response bodies

Important note:
- The HTTP client captures request/response data and headers for logging. When adding new requests, be mindful of what you put into headers/body, especially at verbose log levels and when file logging is enabled.

## E) Formatting / tooling & diff hygiene

Tooling:
- No repo-wide `.clang-format` / `.editorconfig` is currently enforced. Follow surrounding file style.

Diff hygiene rules:
- Keep changes minimal and scoped.
- Don’t reformat unrelated code.
- Don’t reorder large include blocks unless required.
- Don’t touch build outputs (`Binaries/`, `Intermediate/`).

Search-first:
- Before adding a new request or data type, search for existing equivalents in `Public/ServerAPI/` and reuse patterns/types when possible.
