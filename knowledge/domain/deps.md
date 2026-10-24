---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T16:15:00-05:00"
---
# Build and media dependencies

- Pebble SDK 4.33.1 and Pebble CLI 5.0.40: used for the Emery build, emulator, screenshots, and store publishing. Keep the CLI and SDK versions visible in release notes when behavior changes.
- `@rebble/clay` 1.1.0: pinned in `watchface/package.json` for the six-style and date configuration page. Run `npm ci` in `watchface/` after cloning.
- Pillow 12.3.0: installed locally for native GIF assembly and the illustrated store banner. Project requirement is `Pillow>=12.3,<13`; capture scripts fail at import if it is absent. The PBW itself does not depend on Pillow.
