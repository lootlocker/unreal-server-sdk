# Path-specific instructions: LootLockerServerForBlueprints facade

Applies to `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForBlueprints.h` (and corresponding `.cpp`).

## Public facade rules
- Treat this file as the primary, customer-facing API surface. Preserve backward compatibility.
- Prefer additive changes (new methods/overloads) over breaking changes to existing signatures, default values, namespaces, or behavior.
- Keep diffs minimal and commit unrelated changes in separate commits/PRs.
- Always place methods in this file in a `//==================================================\n// Leaderboards\n//==================================================` block corresponding to their feature set (for example, Authentication, Inventory, etc.) and keep them organized with related methods.
- Docs are required for any API you add or change. Match the existing doc style in this file, including clear `param` descriptions and any practical usage notes.

## Deprecation (Blueprint facade)
- Follow the repo deprecation flow in `.github/instructions/style-guide.md` ("Deprecation practices").
- Prefer deprecating old Blueprint-callable methods over removing/renaming them.
- Mark deprecated Blueprint-callable methods with:
  - `meta=(DeprecatedFunction, DeprecationMessage="Deprecated on <YYYY-MM-DD>. Use <Replacement>.")`
- If a C++ facade method is deprecated and still exposed to Blueprints, keep the BP wrapper and mark it deprecated too to preserve parity.

## Blueprint API conventions
- Blueprint facade methods:
  - are `UFUNCTION(BlueprintCallable, ...)`
  - return a `FString` request id
  - expose the return value as `UPARAM(DisplayName = "RequestId")`
- Use the existing dynamic delegate types (suffix `ResponseBP`) and pass the typed response struct.

## Required method documentation (rigorous)
For every new or changed method, include a doc block that covers:
- Purpose, parameter meaning + constraints, and any defaults.
- Return value: explain request id correlation.
- Link to Server API reference when applicable.
- Here's a template for documentation:
```cpp
    /**
    One sentence description of what this method does.
    
    Optional additional context or usage notes.
    
    @param Param1 Describe parameter purpose and constraints
    @param OptParam1 Optional: Describe parameter purpose and constraints, and note that it is optional (e.g., "if not provided, defaults to 50")
    @param OnCompletedRequestBP Delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    UFUNCTION(BlueprintCallable, Category = "LootLockerServer Methods | <feature>", meta = (AdvancedDisplay = "OptParam1", OptParam1 = 50))
    static UPARAM(DisplayName = "RequestId") FString ExampleMethod(int Param1, int OptParam1, const FLootLockerExampleResponseBP& OnCompletedRequestBP);
    */
```

## Implementation expectations (wrapper only)
- The Blueprint facade should not implement request logic.
- It should call the C++ facade and bridge the callback using `CreateLambda` that simply executes the BP delegate:
  - `...ResponseDelegate::CreateLambda([OnCompletedRequest](const ResponseType& Response){ OnCompletedRequest.ExecuteIfBound(Response); })`

## Categories and naming
- Use the established category format: `"LootLockerServer Methods | <Feature>"`.
- Keep method names aligned with the C++ facade for discoverability.
