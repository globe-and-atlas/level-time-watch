---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:11:39-05:00"
---
# Build Level Time

## Goal

Create a native Pebble Time 2 watchface whose on-screen time remains level as the case rolls, with six selectable styles matching `docs/DESIGN.md`.

## Inputs

- `docs/DESIGN.md` for the motion and settings contract.
- `design/reference-orientation.png` for the exact geometric relationship.
- `design/renders/` for style direction.
- The current Pebble SDK and Emery target.

## Execution

1. Implement roll math in a Pebble-header-free C module so host tests can drive known gravity vectors.
2. Draw clock glyphs in a screen buffer with counter-rotation while keeping the background attached to the watch.
3. Implement all six style identifiers and persist the selected value.
4. Expose the style choice in the Pebble phone settings page.
5. Offer the required date formats.
6. Build for Emery and verify the bundle target.
7. Run `python3 execution/capture_media.py` to capture native emulator frames at left, neutral, and right roll.
8. Run `python3 execution/create_promo_gif.py` for an illustrated 720 × 320 banner based on those native frames.
9. Compare digit baselines against the orientation diagram.
10. Check motion and battery on a physical watch before making device-tested claims.

## Edge cases

- Hold a stable angle or show screen-upright time when the watch is nearly horizontal.
- Prevent high-frequency sensor noise from making the text jitter.
- Keep time inside the 200 × 228 screen at the supported roll extremes.
- If settings data is missing or invalid, use Ink.

## Outputs

- Native source, settings page, host checks, and Emery PBW.
- Native screenshots for the six styles and three roll poses.
- A separate record of physical-watch observations, when available.

## Safety

- Keep temporary build and probe output in `.tmp/` when possible.
- Do not commit `.env`, `.lock-waf*`, tokens, or transient emulator files.
- The user authorized watchface-store publication on 2026-10-24. Keep physical-watch claims separate from emulator evidence.
- Do not create a remote repository without a separate request.
