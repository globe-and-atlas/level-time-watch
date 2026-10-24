# Errors

Record deterministic errors, root causes, and fixes here.

## 2026-10-24 — Stale Emery emulator face after successful install

- Symptom: `pebble install --emulator emery` reported success while QEMU kept displaying a different project's watchface.
- Cause: a long-running Emery QEMU instance retained its active face across installs.
- Fix: identify the Emery QEMU process, send `TERM`, restart Emery, reinstall the PBW, and select Level Time. Leave Gabbro and other emulator instances alone.
- Graduated to: `knowledge/procedural/build_and_capture.md`.

## 2026-10-24 — Partial glyphs in initial GIF frames

- Symptom: some screenshots caught the rotated bitmap while the emulator was redrawing.
- Cause: capture began too close to a pose change during frequent accelerometer callbacks.
- Fix: batch 10 samples at 10 Hz, wait 1.2 seconds after each pose, then capture. Review each frame before publication.
- Graduated to: `knowledge/procedural/build_and_capture.md`.
