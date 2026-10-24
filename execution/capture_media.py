"""Capture native Emery style stills and a wrist-roll GIF from the Pebble emulator."""

from __future__ import annotations

import argparse
import json
import math
import subprocess
import time
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
WATCHFACE = ROOT / "watchface"
MEDIA = ROOT / "media" / "native"
TEMP = ROOT / ".tmp" / "capture_media"
STYLES = ("ink", "paper", "amber", "field", "signal", "quiet")


def run(*args: str) -> None:
    subprocess.run(args, cwd=WATCHFACE, check=True, timeout=45)


def pose(angle_degrees: int) -> None:
    radians = math.radians(angle_degrees)
    x = round(1000 * math.sin(radians))
    y = round(-1000 * math.cos(radians))
    fixture = TEMP / f"roll_{angle_degrees:+03d}.accel"
    fixture.write_text(f"{x},{y},0\n" * 40)
    run("pebble", "emu-accel", "--emulator", "emery", "custom", str(fixture))
    time.sleep(1.2)


def settings(style: int, date: int) -> None:
    package = json.loads((WATCHFACE / "package.json").read_text())
    keys = json.loads((WATCHFACE / "build/js/message_keys.json").read_text())
    run(
        "pebble", "send-app-message", "--emulator", "emery",
        "--app-uuid", package["pebble"]["uuid"],
        "--int", f"{keys['SETTING_STYLE']}={style}", f"{keys['SETTING_DATE']}={date}",
    )
    time.sleep(0.35)


def screenshot(path: Path) -> None:
    run("pebble", "screenshot", "--emulator", "emery", "--no-open", "--no-correction", str(path))
    with Image.open(path) as frame:
        if frame.size != (200, 228):
            raise RuntimeError(f"Unexpected Emery image size: {frame.size}")
        if len(frame.convert("RGB").getcolors(200 * 228) or []) < 2:
            raise RuntimeError(f"Empty or single-color emulator frame: {path}")


def make_gif(frames: list[Path], destination: Path) -> None:
    images = [Image.open(path).convert("P", palette=Image.Palette.ADAPTIVE, colors=64) for path in frames]
    try:
        images[0].save(
            destination,
            save_all=True,
            append_images=images[1:],
            duration=320,
            loop=0,
            optimize=True,
            disposal=2,
        )
    finally:
        for image in images:
            image.close()
    if destination.stat().st_size > 4_400_000:
        raise RuntimeError("GIF exceeds Pebble store's 4.4 MB limit")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true", help="List output files without driving the emulator")
    args = parser.parse_args()
    outputs = [MEDIA / f"emery_{i + 1:02d}_{name}.png" for i, name in enumerate(STYLES)]
    gif = MEDIA / "emery_00_tilt.gif"
    if args.dry_run:
        for output in [gif, *outputs]:
            print(output)
        return

    MEDIA.mkdir(parents=True, exist_ok=True)
    TEMP.mkdir(parents=True, exist_ok=True)
    pose(0)
    for index, destination in enumerate(outputs):
        settings(index, 0 if index == 2 else 1)
        screenshot(destination)

    settings(0, 0)
    frames: list[Path] = []
    for index, angle in enumerate((0, -15, -30, -45, -30, -15, 0, 15, 30, 45, 30, 15, 0)):
        pose(angle)
        frame = TEMP / f"tilt_{index:02d}.png"
        screenshot(frame)
        frames.append(frame)
    make_gif(frames, gif)
    pose(0)
    settings(0, 0)
    print(f"Captured {len(outputs)} native stills and {len(frames)} GIF frames in {MEDIA}")


if __name__ == "__main__":
    main()
