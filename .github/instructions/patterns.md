# Unreal Server SDK — Common implementation patterns

This doc is a practical companion to the style guide. It shows the **existing** request/facade/transport patterns used in this repo.

For file- and folder-specific rules (to avoid leaking instructions globally), also see the path-specific instruction files under `.github/instructions/**/*.instructions.md`.

## Pattern 1: Add a new Server API request

### 0) Define or reuse an endpoint
Before adding a new request method, confirm the endpoint exists in:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerEndpoints.h`
- `LootLockerServerSDK/Source/LootLockerServerSDK/Private/LootLockerServerEndpoints.cpp`

Conventions:
- Search first: reuse an existing `ULootLockerServerEndpoints::<Name>` if it already matches.
- Endpoints are initialized in the `.cpp` via `InitEndpoint("path", ELootLockerServerHTTPMethod::GET/POST/...)`.
- Prefer adding new endpoints only when a new backend route is introduced.

### 1) Add models + delegates + request entrypoint (Public)
Create/update a header under:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/<Feature>Request.h`

Typical layout:
- Data models: `USTRUCT(BlueprintType)` + `UPROPERTY(... Category = "LootLockerServer")`
- Request body struct (if any)
- Response struct inheriting `FLootLockerServerResponse`
- C++ delegate: `DECLARE_DELEGATE_OneParam(...)`
- `UCLASS()` request object with `static` method(s)

Conventions to follow:
- Preserve backend field naming (often `Snake_case` with a leading capital, e.g. `Instance_id`) for `FJsonObjectConverter`.
- Document optional/nullable fields.

### 2) Implement the request (Private)
Implement in:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/<Feature>Request.cpp`

Use the centralized HTTP client:
- `ULootLockerServerHttpClient::SendRequest<ResponseType>(RequestStructOrEmpty, Endpoint, OrderedArgs, QueryParams, OnCompletedRequest, /*optional*/ ResponseInspector, /*optional*/ CustomHeaders)`

Query params:
- Use `TMultiMap<FString, FString> QueryParams;`.
- Only add entries when the value is meaningful (e.g. `Count > 0`).

Path params:
- Pass ordered path params as `TArray<FStringFormatArg>{ ... }`.
- Don’t pre-encode; the HTTP client URL-encodes.

## Pattern 2: Wire into the C++ facade

If the new request is a common consumer need, add a facade method.

Where:
- Public declaration: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForCpp.h`
- Implementation: `LootLockerServerSDK/Source/LootLockerServerSDK/Private/LootLockerServerForCpp.cpp`

Facade convention:
- Keep the facade thin: forward to the request class and return the request id.
- Add method docs (purpose, params, constraints, API doc link, return value).

## Pattern 3: Wire into the Blueprint facade

Blueprint users call:
- `ULootLockerServerForBlueprints` (`Public/LootLockerServerForBlueprints.h`, `Private/LootLockerServerForBlueprints.cpp`)

Convention:
- Blueprint facade wraps the C++ facade by creating a C++ delegate via `CreateLambda` that simply calls the BP delegate:
  - `FLootLockerServer<Op>ResponseDelegate::CreateLambda([OnCompletedRequest](const FLootLockerServer<Op>Response& Response) { OnCompletedRequest.ExecuteIfBound(Response); })`

Blueprint method signature:
- Returns request id: `static UPARAM(DisplayName = "RequestId") FString ...`
- Is `UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | <Feature>")`

## Pattern 4: Auth/session behavior

- `StartSession` (auth request) adds `x-server-key` via `CustomHeaders` and stores the returned token via a response-inspector callback.
- After that, `x-auth-token` is automatically added by the HTTP client when a token exists in `ULootLockerServerStateData`.

Guidance:
- Do not manually add `x-auth-token` in new requests.
- Only requests that truly require special headers should pass `CustomHeaders`.

## Pattern 5: Error handling expectations

Every response type should inherit `FLootLockerServerResponse` so callers can rely on:
- `Success` boolean
- `StatusCode`
- `ErrorData` (parsed when possible)
- `RequestContext` (request id, url, method, etc.)

Avoid custom error channels when you can reuse the common response shape.
