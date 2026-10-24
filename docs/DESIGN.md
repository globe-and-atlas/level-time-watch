---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:11:39-05:00"
---
# Level Time design brief

## Core behavior

On Pebble Time 2, the time is a flat 2D element within the watch display. When the case rolls left or right, the time counter-rotates so the digit baseline stays approximately level with the ground. The display background and physical bezel roll with the watch. The time never gains perspective, depth, a card outline, or a hologram effect.

The user's [orientation diagram](../design/reference-orientation.png) is the geometric source of truth. The six [style renders](../design/renders/) are visual explorations of that same behavior. A future native capture must be checked against the diagram before a style is accepted.

An accelerometer measures gravity relative to the watch. It can estimate roll when gravity has a useful projection into the display plane. It cannot find the viewer's eyes. When the watch lies near horizontal and that projection becomes too small, hold the last stable orientation or fall back to screen-upright time rather than letting digits spin unpredictably. Filter small sensor changes so the time rests quietly at a glance. Keep the clock legible and inside the screen throughout the supported roll range.

## Settings contract

`Appearance → Style` is a six-choice selector with these stable names and order:

| Value | Name | Palette and typography | Default supporting detail |
| --- | --- | --- | --- |
| 0 | Ink | White bold sans on black | Small gray date |
| 1 | Paper | Charcoal sans on warm ivory | Small dark date |
| 2 | Amber | Amber numerals on black | Small amber battery indicator |
| 3 | Field | Off-white bold sans on dark olive | Small pale date |
| 4 | Signal | White bold sans on black | Orange accent dot and date |
| 5 | Quiet | Charcoal sans on light gray | Small gray date |

Ink is the first-launch default. The choice persists across watchface restarts. No blue is used in these six default styles. A style changes colors, type treatment, and supporting detail; it never changes the level-time motion rule. The Signal dot is a visual accent only and must not imply a notification or connection state.

Provide a date setting with Off, YYYY-MM-DD, MM/DD/YYYY, and DD/MM/YYYY choices, per this workspace's Pebble convention. The render shorthand `SAT 24` is illustrative; the native date should follow the selected setting. The watch's 12-hour or 24-hour preference controls time format. A battery indicator can be shown in Amber without requiring a phone connection.

## Initial target and validation

- Native watchface target: Pebble Time 2 (`emery`, 200 × 228 pixels).
- Source of time: the watch clock.
- Source of roll: the watch accelerometer.
- Settings path: the Pebble phone app configuration page.
- Implementation evidence: a successful native build, host checks of roll math, and emulator screenshots at distinct accelerometer poses.
- Physical-watch evidence: wrist legibility, motion feel, and battery impact must be checked separately from emulator success.

This brief does not claim native implementation, device behavior, a PBW, or a store listing.
