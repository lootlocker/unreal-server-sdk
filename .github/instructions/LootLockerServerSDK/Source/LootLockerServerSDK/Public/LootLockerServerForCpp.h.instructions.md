# Path-specific instructions: LootLockerServerForCpp facade

Applies to: `LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForCpp.h` (and corresponding `.cpp`).

## Public facade rules
- Treat this file as the primary, customer-facing API surface. Preserve backward compatibility.
- Prefer additive changes (new methods/overloads) over breaking changes to existing signatures, default values, namespaces, or behavior.
- Keep diffs minimal and commit unrelated changes in separate commits/PRs.
- Always place methods in this file in a `//==================================================\n// Leaderboards\n//==================================================` block corresponding to their feature set (for example, Authentication, Inventory, etc.) and keep them organized with related methods.
- Docs are required for any API you add or change. Match the existing doc style in this file, including clear `param` descriptions and any practical usage notes.

## Deprecation (public facade)
- Follow the repo deprecation flow in `.github/instructions/style-guide.md` ("Deprecation practices").
- Prefer deprecating old methods over removing/renaming them.
- Mark deprecated C++ methods/types with `UE_DEPRECATED(<UE version>, "Deprecated on <YYYY-MM-DD>. Use <Replacement>.")`.
- Do deprecations in their own commits and call them out explicitly.

## When adding a new facade method
- Forward request logic to the existing request class in `Public/ServerAPI/` + `Private/ServerAPI/`.
- Keep the facade implementation thin: forward call + return request id.

## Required method documentation (rigorous)
For every new or changed method, include a doc block that covers:
- One-sentence purpose.
- Link to the relevant Server API reference (usually `https://ref.lootlocker.com/server-api/#...`) when applicable.
- Parameter docs including:
  - constraints (valid ranges)
  - pagination semantics (`count`/`after`, cursor vs index)
  - optional behavior and defaults
- Return value: state that the returned `FString` is a request id used to correlate callbacks.
- Auth/session requirements when relevant (e.g., requires `StartSession` beforehand).
- Here's a template for documentation:
```cpp
    /**
    One sentence description of what this method does.
    
    Optional additional context or usage notes.
    
    @param Param1 Describe parameter purpose and constraints
    @param OptParam1 Optional: Describe parameter purpose and constraints, and note that it is optional (e.g., "if not provided, defaults to 50")
    @param OnCompletedRequest Delegate for handling the server response
    
    @return A unique id for this request, use this to match callbacks to requests when you have multiple simultaneous requests outbound
    static FString ExampleMethod(int Param1, const FLootLockerExampleResponseDelegate& OnCompletedRequest, int OptParam1 = 50);
    */
```

## Signature and behavior conventions
- Public facade methods are `static` and typically return a `FString` request id.
- Use the existing delegate types (suffix `ResponseDelegate`).
- Don’t invent new async patterns; stay consistent with existing delegates + request id.

## Cross-surface consistency
- If you add a method here that should be available to Blueprint users, ensure the Blueprint facade has the corresponding wrapper method (or explicitly document why it does not).
