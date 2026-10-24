# Decisions

## 2026-10-24 — Dedicated Level Time repository

- Decision: create `level-time-watch` as an independent local repository through the workspace project template. Use the workflow-python scaffold for directives, knowledge, and future host-side checks; the product runtime will be native Pebble SDK.
- Alternatives considered: adding the face to the `pebble-time` collection or modifying Gridcore. That collection is an index of individually importable projects, and Gridcore has a different visual behavior.
- Reason: keep the new face's source, settings, tests, and eventual CloudPebble import isolated.
- Scope: local project setup only. No remote repository or watchface listing was created.

## 2026-10-24 — Product name and settings baseline

- Decision: name the face **Level Time**. Store search did not surface an exact-name RePebble listing; name availability beyond that search is unconfirmed.
- Decision: make Ink the default style and retain Paper, Amber, Field, Signal, and Quiet as the other five selectable styles.
- Decision: all styles share the same level-time orientation rule. The user-supplied diagram outranks generated renders if they differ.
- Reason: the name describes the visible behavior, and one selector preserves the six looks the user accepted.

## 2026-10-24 — Native motion and first release

- Decision: target Emery only for version 0.1.0. The 200 × 228 color display supports the six approved palettes and native store captures.
- Decision: render the clock into a transparent bitmap and rotate that bitmap against accelerometer-derived screen roll. Batch 10 Hz samples into one update per second, smooth large angle changes, and hold the last angle when the in-plane gravity vector is too small.
- Alternatives considered: drawing each glyph separately at a rotated position or pretending to know the viewer's eye line. The bitmap path keeps digits flat as one unit; the accelerometer only provides gravity-relative orientation.
- Decision: use native emulator pixels for store screenshots and a separately labeled illustrated banner for promotion. A physical-watch check is still required before device-performance claims.
