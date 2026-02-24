# Path-specific instructions: Public ServerAPI headers

Applies to: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/**/*.h`

## Public API + data model rules
- Treat these headers as **public API**.
- Keep diffs minimal; avoid drive-by reformatting.

## JSON serialization compatibility (critical)
- These structs are serialized/deserialized with `FJsonObjectConverter`.
- Preserve backend field naming (this repo commonly uses **Snake_case** member names with a leading capital, e.g. `Instance_id`).
- Do not rename fields (e.g., `Instance_id` → `InstanceId`) unless you also handle JSON compatibility intentionally.

## Deprecation (DTOs, fields, and request/response types)
- Follow the repo deprecation flow in `.github/instructions/style-guide.md` ("Deprecation practices").
- Prefer additive changes to DTOs. Avoid removing or renaming existing `UPROPERTY` fields because it can break:
  - user code (compile-time)
  - JSON expectations (wire compatibility)
  - Blueprint pins (graph compatibility)
- If a field must be discouraged, keep it and mark the `UPROPERTY` with `meta=(DeprecatedProperty, DeprecationMessage="Deprecated on <YYYY-MM-DD>. Use <Replacement>.")`.
- If a request/response type must be phased out, prefer keeping the old type and introducing a replacement type, and (where supported) mark the old C++ type as deprecated with `UE_DEPRECATED(...)`.

## USTRUCT / UPROPERTY conventions
- Use `USTRUCT(BlueprintType)` for request/response/data models that are exposed to users.
- Use `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLockerServer")` where appropriate.

## Documentation expectations
- Document all fields of public-facing USTRUCTs, especially when:
  - a field is optional/nullable
  - optional / may be omitted
  - represented as `FString` even though they are numeric/bool-like (explain how to interpret)
  - large (e.g., base64 payloads) or sensitive

## File structure
Prefer the existing section layout:
- Data Type Definitions
- Request Definitions
- Response Definitions
- Delegate Definitions
- API Class Definition (`UCLASS` with `static` methods)

## Delegates
- C++ delegates are `DECLARE_DELEGATE_OneParam(...)` with suffix `ResponseDelegate`.
- Keep naming consistent and avoid introducing new delegate styles.
