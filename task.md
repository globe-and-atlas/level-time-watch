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

## Theme gallery update — 2026-10-24

The Emery store gallery permits five images. Keep the original tilt GIF first while using another slot to show every selectable theme.

### Acceptance

- The first store image remains the native tilt GIF.
- A second 200 × 228 GIF cycles through Ink.
- The second GIF cycles through Paper.
- The second GIF cycles through Amber.
- The second GIF cycles through Field.
- The second GIF cycles through Signal.
- The second GIF cycles through Quiet.
- The live listing retains five media items.
- The updated public listing shows the theme GIF.

### Progress

- [x] Create the native theme GIF.
- [x] Update the store gallery.
- [x] Verify the public listing.

## Typography correction — 2026-10-24

The user observed that five styles shared one numeral font. Update the actual Emery watchface so style choice changes typography, then refresh the published binary and gallery.

### Contract

- Target directive: `directives/build_watchface.md`.
- Intended execution: native Pebble build, host motion check, `execution/capture_media.py`, and store listing edit.
- Output artifacts: version 0.1.1 PBW, six native style captures, tilt GIF, theme GIF, and updated public listing.
- Safety: preserve the watchface UUID and saved style identifiers.
- Safety: do not stage `.env`, `.tmp/`, or `.lock-waf*`.

### Acceptance

- Ink renders in a block numeral font.
- Paper renders in a serif numeral font.
- Amber renders in a monospaced numeral font.
- Field renders in a bold geometric numeral font.
- Signal renders in a condensed angular numeral font.
- Quiet renders in a light sans numeral font.
- The six time glyph silhouettes differ in the native captures.
- A 24-hour time fits inside the screen in each style.
- A 12-hour time fits inside the screen in each style.
- The date remains readable in each style that shows it.
- The selected style persists after watchface restart.
- The roll behavior still passes the host check.
- The Emery PBW version is 0.1.1.
- A fresh verifier reviews the PBW and native captures.
- The store serves version 0.1.1.
- The live gallery uses captures from version 0.1.1.

### Progress

- [x] Add licensed font resources.
- [x] Wire distinct numeral fonts by style.
- [x] Build and inspect Emery captures.
- [x] Complete fresh verification.
- [x] Publish 0.1.1 and replace store media.
- [x] Verify the public listing.
