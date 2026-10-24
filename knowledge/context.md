# Project Context

## Identity

- Product name: Level Time.
- Local repository: `level-time-watch`.
- Initial watch target: Pebble Time 2 (`emery`, 200 × 228).
- Scaffold profile: `workflow-python`; runtime: Pebble SDK. This profile supplies project governance and future deterministic checks, not a Python watchface runtime.
- Deployment state: local project only.

## Purpose

Keep the clock easy to read when the wrist rolls. The user-supplied orientation diagram fixes the essential relationship: watch and screen rotate; 2D digits stay level. The six approved no-blue render styles are settings presets, not separate watchfaces.

## Constraints

- Accelerometer data estimates orientation relative to gravity; it does not locate the viewer's eyes.
- Near-horizontal wrist positions have an ambiguous in-plane gravity direction.
- The screen uses Pebble's finite pixel and color palette, so image-generation renders are direction rather than pixel evidence.
- Physical-watch battery and readability remain separate checks after native implementation.

## Current state

- Project scaffold, design brief, reference diagram, and six renders exist locally.
- Native watchface source and settings implementation have not started.
