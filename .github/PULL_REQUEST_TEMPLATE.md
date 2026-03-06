## Tracking Issue

<!-- Link the relevant lootlocker/index issue. Use "Closes lootlocker/index#NNN" to auto-close, or a plain link if this PR only partially addresses it. -->

Closes lootlocker/index#

## Description

<!-- What changed and why? Keep it concise. -->

## Type of Change

- [ ] Bug fix
- [ ] New feature
- [ ] Refactor
- [ ] Docs
- [ ] Chore / CI / meta

## Checklist

- [ ] PR targets `dev` (not `main`)
- [ ] Branch follows naming convention (`feat/`, `fix/`, `docs/`, `refactor/`, `chore/`, `ci/`, `meta/`, `scout/`)
- [ ] Diff is minimal and scoped — no unrelated changes, no drive-by refactors
- [ ] No version bumps or release metadata changes (unless explicitly requested)
- [ ] No new helpers introduced without first searching for existing ones
- [ ] Changes to `LootLockerServerSDK/Public/` are intentional public API additions/changes
- [ ] C++ server facade (`LootLockerServerForCpp.h`) updated if the feature is C++-accessible
- [ ] Blueprint server facade (`LootLockerServerForBlueprints.h`) updated if the feature is Blueprint-accessible
- [ ] Compile Check CI workflow passes (or `scripts/verify-compile.ps1` run locally)
- [ ] Tracking issue in `lootlocker/index` is linked, status set to **In Review**, and PR link posted as a comment on the tracking issue

## Testing Notes

<!-- How was this change verified? Include any manual steps, CI results, or test scenarios exercised. -->

## Additional Notes

<!-- Anything the reviewer should know that isn't covered above. Delete this section if not needed. -->
