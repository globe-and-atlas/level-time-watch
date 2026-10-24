---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:55:00-05:00"
---
# Level Time store releases

## Version 0.1.0 — initial release

- Listing: https://apps.repebble.com/450af5416e634355b0e326f9
- Developer Dashboard state observed: Listed, release 0.1.0 Published, Emery platform.
- PBW: `release/Level-Time-0.1.0.pbw`; SHA-256 `bf2236ee129722e9bd54f711e97030474c0e5e01350b70cad6b8b882666574f6`.
- Initial store gallery: native Emery tilt GIF first, then Paper, Amber, Field, and Quiet PNGs. The public image URL for screenshot 1 ends in `.gif` and reports 200 × 228 pixels.
- 2026-10-24 gallery update: the dashboard saved the tilt GIF first, a six-theme native GIF second, then Paper, Amber, and Quiet PNGs. The second GIF cycles Field, Signal, Quiet, Ink, Paper, and Amber. It uses unaltered 200 × 228 native frames, each shown for 1.5 seconds. The public listing HTML references the new GIF in slot 2; its downloadable asset is 200 × 228 with six frames and matches the local file size. The in-app browser still showed its older client-side cache during the check.
- Local media: six native style PNGs, one native 13-frame tilt GIF, one native six-theme GIF, and one illustrated 11-frame banner GIF.
- The dashboard accepted the banner but served it as a 720 × 320 PNG. The current public page shows the five screenshots; its DOM does not expose the banner.
- Verified: host roll test, native build, PBW manifest, emulator motion and style captures, 12/24-hour display, watch persistence of style, store media dimensions, and public listing.
- Not yet verified: phone settings Save on a real phone, wrist readability, and physical battery impact.

## Version 0.1.1 — distinct typography

- Store state observed: release 0.1.1 Published and listing Listed for Emery.
- PBW: `release/Level-Time-0.1.1.pbw`; SHA-256 `080bbb4c80e0556b923b8b85ed4055ff5277411f9c84888f3dd0fbd5818447ff`.
- The public PBW download matched the local release SHA-256 exactly.
- The public listing HTML exposes the 0.1.1 version, updated typography description, and five current screenshot asset IDs.
- The two public GIF assets matched local SHA-256 values. The gallery retains the tilt GIF first and cycles all six current native fonts in the second GIF.
- Six current emulator stills and an optional 3 × 2 typography comparison are saved under `media/`.
- Validation: Pebble clean build, host roll test, six native style captures, 12-hour samples, normal 24-hour samples, isolated `23:59` Paper capture, persisted Field style after reinstall, media integrity checks, and independent prepublish review. A broad injected-time probe stalled the Emery emulator and did not validate every style at `23:59`.
- Physical-watch readability, battery use, and real-phone Clay Save remain untested.
