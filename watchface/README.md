# Level Time Pebble package

Native Pebble Time 2 (`emery`) watchface. The accelerometer controls counter-rotation of a flat clock bitmap; the phone-side Clay page selects one of six styles and a date format.

```sh
npm ci
pebble build
pebble install --emulator emery
```

The build output is `build/watchface.pbw`. The repository root [README](../README.md) links to the published store listing, native screenshots, motion GIF, and host test.

Paper, Amber, Signal, and Quiet use bundled TrueType resources. Their source licenses are in `resources/licenses/`; the build subsets the font resources to digits and colon. Ink and Field use Pebble system fonts.
