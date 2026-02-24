# Coding Agent Guardrails (Unreal Server SDK)

This repository is the **LootLocker Unreal Server SDK** distributed as an **Unreal Engine plugin**.

These guardrails exist to help automation (Copilot/Coding Agent) place changes correctly, respect architectural boundaries, and keep diffs reviewable.

## Non‑negotiable repo rules

### Branching / PR targets
- `main` = latest released state. PRs into `main` are **manual** and come from `dev`.
- `dev` = working trunk. **No direct commits**.
- Work branches: `feat/`, `fix/`, `docs/`, `chore/`, `refactor/`, `meta/`, `ci/`, `scout/`.
- PRs must target `dev`.

## Architectural boundaries (runtime vs editor)
This plugin contains two modules:
- Runtime: `LootLockerServerSDK/Source/LootLockerServerSDK/`
- Editor: `LootLockerServerSDK/Source/LootLockerServerSDKEditor/`

Guardrails:
- Runtime API behavior belongs in the runtime module.
- Editor tooling (widgets, menus, editor-only UI) belongs in the editor module.
- Avoid leaking editor-only dependencies into runtime.

## Public API safety
Unreal module public surface is everything under:
- `LootLockerServerSDK/Source/LootLockerServerSDK/Public/`

Rules:
- Treat **any new or modified header** in `Public/` as a **public API change**.
- Prefer putting helpers/implementation details in `Private/`.
- Remember to keep public interfaces up to date with changed request code:
  - `Public/LootLockerServerForCpp.h`
  - `Public/LootLockerServerForBlueprints.h`

## Change discipline
- Search before adding: reuse existing request/response patterns and utilities.
- Keep diffs minimal; drive-by refactors, renames, or reformatting should be done in separate commits and if large; separate PRs.
- Don’t touch generated or build output directories:
  - `LootLockerServerSDK/Binaries/`
  - `LootLockerServerSDK/Intermediate/`

## When unclear
Stop and ask a small number of clarifying questions when:
- A change might expand the public API.
- It’s unclear whether code belongs in runtime vs editor.
- There are multiple competing conventions in the code.

## Pre‑PR checklist
- [ ] PR targets `dev`
- [ ] No changes to `.uplugin` or `*.Build.cs`
- [ ] No changes under `Binaries/` or `Intermediate/`
- [ ] Public API changes are intentional and justified
- [ ] Only requested files changed for docs-only tasks

## Related docs
- Architecture overview: `.github/instructions/architecture.md`
- Copilot workspace instructions: `.github/copilot-instructions.md`
