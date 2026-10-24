---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:55:00-05:00"
---
# Level Time 0.1.0 store release

- Listing: https://apps.repebble.com/450af5416e634355b0e326f9
- Developer Dashboard state observed: Listed, release 0.1.0 Published, Emery platform.
- PBW: `release/Level-Time-0.1.0.pbw`; SHA-256 `bf2236ee129722e9bd54f711e97030474c0e5e01350b70cad6b8b882666574f6`.
- Initial store gallery: native Emery tilt GIF first, then Paper, Amber, Field, and Quiet PNGs. The public image URL for screenshot 1 ends in `.gif` and reports 200 × 228 pixels.
- 2026-10-24 gallery update: the dashboard saved the tilt GIF first, a six-theme native GIF second, then Paper, Amber, and Quiet PNGs. The second GIF cycles Field, Signal, Quiet, Ink, Paper, and Amber. It uses unaltered 200 × 228 native frames, each shown for 1.5 seconds. The public listing HTML references the new GIF in slot 2; its downloadable asset is 200 × 228 with six frames and matches the local file size. The in-app browser still showed its older client-side cache during the check.
- Local media: six native style PNGs, one native 13-frame tilt GIF, one native six-theme GIF, and one illustrated 11-frame banner GIF.
- The dashboard accepted the banner but served it as a 720 × 320 PNG. The current public page shows the five screenshots; its DOM does not expose the banner.
- Verified: host roll test, native build, PBW manifest, emulator motion and style captures, 12/24-hour display, watch persistence of style, store media dimensions, and public listing.
- Not yet verified: phone settings Save on a real phone, wrist readability, and physical battery impact.
