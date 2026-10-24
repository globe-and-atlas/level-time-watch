---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T16:15:00-05:00"
---
# Build and capture Level Time

1. In `watchface/`, run `npm ci`, then `pebble clean` and `pebble build`.
2. Confirm Emery is the active emulator before installing. If a successful install still displays another face, terminate only the stale Emery QEMU process gracefully, restart Emery, and reinstall.
3. Run `python3 execution/capture_media.py --dry-run` to inspect output paths, then `python3 execution/capture_media.py` at the repository root. The script sets 10 Hz accelerometer fixtures, waits 1.2 seconds per pose, and captures exact 200 × 228 emulator frames.
4. Run `python3 execution/create_promo_gif.py` to build the 720 × 320 illustrated banner. It uses the native tilt frames but the bezel is a drawing.
5. Review the first frame and every motion frame for intact, readable digits before publishing. The first GIF frame is upright so the store poster is legible.

The emulator verifies code and pixels, but does not measure physical-watch battery use or wrist readability.

For a long-time layout probe, set the style first, then inject `23:58:58` for 24-hour or `12:58:58` for 12-hour mode with `pebble emu-set-time --emulator emery`. Wait until the next minute tick before capturing. In the 0.1.1 test setup, a subsequent style message refreshed the app's clock and replaced the injected time with local wall time. Restore the current time and original format after the probe.
