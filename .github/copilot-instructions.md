# Copilot Instructions (Unreal Server SDK)

You are working in the **LootLocker Unreal Server SDK** repository.

## Non-negotiables
- PRs must target `dev` (no direct commits to `dev`).
- Keep diffs minimal and scoped to the request.
- Search before adding new code; reuse existing patterns.
- Treat anything under `LootLockerServerSDK/Source/LootLockerServerSDK/Public/` as **public API**.
- Prefer implementation details in `Private/`.

## More context
- Architecture: `.github/instructions/architecture.md`
- Guardrails: `.github/instructions/guardrails.md`
- Style guide: `.github/instructions/style-guide.md`
- Patterns: `.github/instructions/patterns.md`
- Path-specific instructions:
  - C++ facade: `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForCpp.h.instructions.md`
  - Blueprint facade: `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/LootLockerServerForBlueprints.h.instructions.md`
  - Public ServerAPI headers: `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Public/ServerAPI/ServerAPI.instructions.md`
  - Private ServerAPI implementations: `.github/instructions/LootLockerServerSDK/Source/LootLockerServerSDK/Private/ServerAPI/ServerAPI.instructions.md`
