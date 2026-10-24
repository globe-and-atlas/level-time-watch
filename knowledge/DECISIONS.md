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
