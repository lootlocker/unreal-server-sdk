# Path-specific instructions: Private ServerAPI implementations

Applies to: `LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/**/*.cpp`

## Core rule
- Implement request execution by using `ULootLockerServerHttpClient` and existing endpoints.

## Transport conventions
- Prefer `ULootLockerServerHttpClient::SendRequest<ResponseType>(...)`.
- Only use `SendRawRequest` / `SendRawWWWFormUrlEncodedRequest` when the payload must be handcrafted.

## Endpoints and params
- Use `ULootLockerServerEndpoints::<EndpointName>`.
- Path params: pass ordered arguments via `TArray<FStringFormatArg>{ ... }` (do not pre-encode).
- Query params: use `TMultiMap<FString, FString>` and only add params when meaningful (e.g., `Count > 0`).

## Auth headers
- Do not manually add `x-auth-token`.
  - The HTTP client adds it automatically when `ULootLockerServerStateData` has a token.
- Only add custom headers when required (e.g., `x-server-key` in session start).

## Responses and errors
- Responses should inherit `FLootLockerServerResponse` so callers consistently get:
  - `Success`, `StatusCode`, `ErrorData`, `RequestContext`, `FullTextFromServer`
- Do not introduce alternate error channels.

## Deprecation-aware changes
- Follow the repo deprecation flow in `.github/instructions/style-guide.md` ("Deprecation practices").
- If an API needs to change behavior or migrate to a new backend route, prefer:
  - keeping the old request method working (or forwarding it internally to the new endpoint)
  - adding a new request method/type for the new behavior
- Avoid silent breaking behavior changes in existing requests unless explicitly requested.

## Logging and secrets
- Do not log server keys, auth tokens, or other sensitive data unless obfuscating it.
- Be mindful that HTTP logging captures request/response bodies and headers (especially when file logging is enabled).

## Diff hygiene
- Keep changes scoped to the request being implemented.
- Avoid refactors/renames in this folder unless explicitly requested.
