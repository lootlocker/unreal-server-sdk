# Verification (Unreal Server SDK)

This repository is an **Unreal Engine plugin**. The fastest, most deterministic compile verification is to run Unreal Automation Tool (UAT) `BuildPlugin`.

This doc describes the two supported verification paths:
- **Local (Windows):** for contributors using the repo on a workstation.
- **CI (GitHub Actions):** for cloud verification and GH Coding Agent.

## A) Local compile verification (Windows)

### Prerequisites
- Unreal Engine installed locally (e.g. UE 5.5)
- Visual Studio / MSVC toolchain that matches your UE install

### Command

From repo root:

```powershell
# Run UAT BuildPlugin for Win64 (full clean build)
.\github\scripts\verify-compilation.ps1 -Clean

# Incremental build (skip clean)
.\github\scripts\verify-compilation.ps1
```

### Configuring your local Unreal Engine path

Create a repo-local, gitignored file in repo root: `unreal-dev-settings.json`

```json
{ "unreal_engine_path": "C:\\Program Files\\Epic Games\\UE_5.5" }
```

`.github\scripts\verify-compilation.ps1` reads this file automatically.

### Outputs
- Build output: `Build~\PluginBuild\`
- Log file: `Build~\UAT.log`

## B) CI compile verification (GitHub Actions)

The lightweight workflow runs the same check in a single Unreal Engine container image:
- Workflow: `.github/workflows/verify-compile.yml`
- Script invoked inside the container: `scripts/verify-compile.sh`

### Default behavior
- Uses `vars.AGENT_CHECK_UE_IMAGE`.
- If not set, defaults to `dev-5.5`.
- Runs `RunUAT.sh BuildPlugin` for `Linux`.
- Uploads the UAT log as an artifact.

### Manual runs
You can override the UE image tag via the workflow dispatch input `ueImage`.

## What "compile verified" means here

A change is considered compile-verified when:
- Local: `scripts/verify-compile.ps1` exits with code `0`.
- CI: the `Verify compile (quick)` workflow job succeeds.

This check is intentionally narrower than the full matrix builds (it is meant to be a fast per-commit gate). For broad version coverage, use the existing matrix workflow.
