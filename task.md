---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-10-24T15:11:39-05:00"
---
# Level Time project setup

## Contract
- Target directive: `directives/build_watchface.md`.
- Intended execution script: none for this setup milestone.
- Output artifacts: `README.md`, `docs/DESIGN.md`, `design/renders/`.
- Safety: keep temporary outputs in `.tmp/`.
- Safety: do not publish the repository or watchface during setup.

## Validation Contract
- The repository is an independent Git checkout at `/Users/danielbally/Git/level-time-watch`.
- The design brief states that displayed digits stay horizontal while the watch rolls.
- The design brief names the target watch as Pebble Time 2.
- The settings specification lists Ink.
- The settings specification lists Paper.
- The settings specification lists Amber.
- The settings specification lists Field.
- The settings specification lists Signal.
- The settings specification lists Quiet.
- The settings specification selects Ink by default.
- Each named style has one local reference render.
- `python3 scripts/health_check.py` exits successfully.
- A fresh verifier reviews the setup against the user request.

## Progress
- [x] Create the independent project with the workspace template.
- [x] Record the watchface behavior and six settings styles.
- [x] Copy the six accepted reference renders into the project.
- [x] Check the project files and health command.
- [x] Run fresh verification.

## Next implementation milestone
- Implement a native Emery watchface that counter-rotates the time against wrist roll.
- Expose the six styles through Pebble phone settings.
- Test readability, orientation, and battery use on the emulator and physical watch separately.
