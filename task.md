---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:11:39-05:00"
---
# Level Time native build and store release

## Contract
- Target directive: `directives/build_watchface.md`.
- Intended execution scripts: host renderer checks and screenshot capture tools under `execution/`.
- Output artifacts: Emery PBW, native screenshots, animated tilt GIF, store listing.
- Safety: keep temporary outputs in `.tmp/`.
- Safety: do not stage `.env` or `.lock-waf*`.
- Safety: publish only a PBW that passed the native build and screenshot checks.

## Validation Contract
- The PBW includes an Emery watchface binary.
- The time reads the Pebble clock in 12-hour mode.
- The time reads the Pebble clock in 24-hour mode.
- An upright watch shows upright digits.
- A left roll changes the digits' angle against the screen.
- A right roll changes the digits' angle against the screen.
- The digit baseline stays level in the native tilt captures.
- A near-horizontal watch does not spin the time unpredictably.
- Ink is the default style on a fresh install.
- The phone configuration offers Ink.
- The phone configuration offers Paper.
- The phone configuration offers Amber.
- The phone configuration offers Field.
- The phone configuration offers Signal.
- The phone configuration offers Quiet.
- The selected style survives watchface restart.
- The phone configuration offers Off as a date choice.
- The phone configuration offers YYYY-MM-DD as a date choice.
- The phone configuration offers MM/DD/YYYY as a date choice.
- The phone configuration offers DD/MM/YYYY as a date choice.
- The store media includes a native 200 × 228 Ink screenshot.
- The store media includes a native 200 × 228 animated tilt GIF.
- The GIF shows the case-relative text rotation across distinct emulator poses.
- A fresh verifier reviews the PBW and store media before upload.
- The store listing contains the requested PBW and media after upload.

## Progress
- [x] Implement native watchface and six styles.
- [x] Run host checks and Pebble build.
- [x] Capture native screenshots and tilt GIF.
- [x] Complete fresh verification.
- [x] Upload PBW and media to the watchface store.
- [x] Inspect the saved public listing.

## Previous milestone
The dedicated repository and design brief were created in commit `f6c0991`.
