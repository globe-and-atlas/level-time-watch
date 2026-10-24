"""Make a store banner from native Emery frames to show the whole watch rolling."""

from __future__ import annotations

import argparse
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[1]
FRAMES = ROOT / ".tmp" / "capture_media"
OUTPUT = ROOT / "media" / "store" / "emery_banner.gif"
POSES = ((0, 0), (1, -15), (2, -30), (4, -30), (5, -15),
         (6, 0), (7, 15), (8, 30), (10, 30), (11, 15), (12, 0))


def watch_sprite(display: Image.Image) -> Image.Image:
    sprite = Image.new("RGBA", (266, 350), (0, 0, 0, 0))
    draw = ImageDraw.Draw(sprite)
    draw.rounded_rectangle((91, 0, 175, 350), 22, fill="#141414")
    draw.rounded_rectangle((8, 43, 258, 307), 32, fill="#101010", outline="#4b4b4b", width=4)
    draw.rounded_rectangle((22, 57, 244, 293), 17, fill="#030303")
    sprite.paste(display.convert("RGBA"), (33, 61))
    draw.rounded_rectangle((31, 59, 235, 291), 3, outline="#606060", width=2)
    for top in (107, 153, 199):
        draw.rounded_rectangle((257, top, 265, top + 23), 3, fill="#333333")
    return sprite


def banner(frame_path: Path, roll: int) -> Image.Image:
    with Image.open(frame_path) as screenshot:
        if screenshot.size != (200, 228):
            raise ValueError(f"Expected 200 x 228 native screenshot: {frame_path}")
        sprite = watch_sprite(screenshot)
    rotated = sprite.rotate(-roll, resample=Image.Resampling.BICUBIC, expand=True)
    image = Image.new("RGBA", (720, 320), "#202020")
    image.alpha_composite(rotated, (190 - rotated.width // 2, 160 - rotated.height // 2))
    draw = ImageDraw.Draw(image)
    font_bold = ImageFont.truetype("/System/Library/Fonts/Supplemental/Arial Bold.ttf", 46)
    font_regular = ImageFont.truetype("/System/Library/Fonts/Supplemental/Arial.ttf", 23)
    draw.text((350, 75), "LEVEL TIME", font=font_bold, fill="white")
    draw.rectangle((350, 138, 650, 141), fill="#ff9c20")
    draw.text((350, 164), "The watch rolls.", font=font_regular, fill="#ececec")
    draw.text((350, 194), "The time stays level.", font=font_regular, fill="#ececec")
    draw.text((350, 263), "Six styles  ·  Pebble Time 2", font=font_regular, fill="#bfbfbf")
    return image.convert("RGB")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    if args.dry_run:
        print(OUTPUT)
        return
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    images = [banner(FRAMES / f"tilt_{index:02d}.png", roll) for index, roll in POSES]
    images[0].save(OUTPUT, save_all=True, append_images=images[1:], duration=450,
                   loop=0, optimize=True, disposal=2)
    with Image.open(OUTPUT) as gif:
        if gif.size != (720, 320) or gif.n_frames != len(POSES):
            raise RuntimeError("Store banner GIF failed dimension or frame validation")
    if OUTPUT.stat().st_size > 4_400_000:
        raise RuntimeError("Store banner GIF exceeds the 4.4 MB limit")
    print(f"Created {OUTPUT} ({OUTPUT.stat().st_size} bytes)")


if __name__ == "__main__":
    main()
