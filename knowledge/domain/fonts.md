---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T17:00:00-05:00"
---
# Level Time font resources

Pebble custom fonts must be TrueType resources whose names end in the intended point size. `characterRegex` limits generated glyphs, and each loaded `GFont` must be unloaded on app shutdown. Level Time uses four custom fonts, restricted to `[0-9:]`, plus two Pebble system fonts. The Emery build reports 12,664 bytes of compiled resources for the four fonts.

| Style | Numeral font | Resource |
| --- | --- | --- |
| Ink | LECO 60 Bold | Pebble system |
| Paper | DM Serif Display Regular 46 | `FONT_PAPER_46` |
| Amber | IBM Plex Mono SemiBold 46 | `FONT_AMBER_46` |
| Field | Bitham 42 Bold | Pebble system |
| Signal | Rajdhani Bold 48 | `FONT_SIGNAL_48` |
| Quiet | Lato Light 46 | `FONT_QUIET_46` |

The source TrueType files and individual SIL Open Font License files live under `watchface/resources/`. Version 0.1.1 preserves style numbers and persistence keys from version 0.1.0.

Source: https://developer.repebble.com/guides/app-resources/fonts/
