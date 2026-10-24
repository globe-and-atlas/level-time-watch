"""Assemble the six native Emery style captures into one store gallery GIF."""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image, ImageChops

ROOT = Path(__file__).resolve().parents[1]
NATIVE = ROOT / "media" / "native"
OUTPUT = ROOT / "media" / "store" / "emery_01_six_styles.gif"
STYLES = ((4, "field"), (5, "signal"), (6, "quiet"),
          (1, "ink"), (2, "paper"), (3, "amber"))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    if args.dry_run:
        print(OUTPUT)
        return

    paths = [NATIVE / f"emery_{number:02d}_{style}.png" for number, style in STYLES]
    frames: list[Image.Image] = []
    try:
        for path in paths:
            if not path.is_file():
                raise FileNotFoundError(path)
            with Image.open(path) as native:
                if native.size != (200, 228):
                    raise ValueError(f"Expected 200 x 228 native screenshot: {path}")
                frames.append(native.convert("RGB"))
        OUTPUT.parent.mkdir(parents=True, exist_ok=True)
        frames[0].save(OUTPUT, save_all=True, append_images=frames[1:], duration=1500,
                       loop=0, optimize=True, disposal=2)
        with Image.open(OUTPUT) as gif:
            if gif.size != (200, 228) or gif.n_frames != len(STYLES):
                raise RuntimeError("Theme GIF dimensions or frame count changed")
            for index, source in enumerate(frames):
                gif.seek(index)
                if ImageChops.difference(gif.convert("RGB"), source).getbbox():
                    raise RuntimeError(f"Theme GIF frame {index} differs from its native capture")
        if OUTPUT.stat().st_size > 4_400_000:
            raise RuntimeError("Theme GIF exceeds the store's 4.4 MB image limit")
        print(f"Created {OUTPUT} ({OUTPUT.stat().st_size} bytes)")
    finally:
        for frame in frames:
            frame.close()


if __name__ == "__main__":
    main()
