---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:11:39-05:00"
---
# Level Time

A Pebble Time 2 watchface concept: the watch rolls with your wrist while the digital time counter-rotates so its digits stay level. The time remains flat, legible 2D text on the watch screen. The watchface does not draw a floating card or project a hologram.

This repository is a **project and design brief**, not a built watchface yet. The native Pebble implementation and settings screen are the next milestone.

## Six settings styles

The planned **Appearance → Style** selector includes all six accepted looks. Ink is the default.

| Style | Display | Time | Supporting detail |
| --- | --- | --- | --- |
| [Ink](design/renders/ink.png) | Black | White | Small gray date |
| [Paper](design/renders/paper.png) | Warm ivory | Charcoal | Small dark date |
| [Amber](design/renders/amber.png) | Black | Amber | Small battery indicator |
| [Field](design/renders/field.png) | Dark olive | Off-white | Small pale date |
| [Signal](design/renders/signal.png) | Black | White | Orange accent dot and date |
| [Quiet](design/renders/quiet.png) | Light gray | Charcoal | Small gray date |

The reference renders show each style at three watch angles. Their colors and layouts are design targets; they are not emulator captures or proof of final Pebble pixels.

See [the design brief](docs/DESIGN.md) for the motion rule, settings contract, and implementation limits. See [task.md](task.md) for the current milestone.
