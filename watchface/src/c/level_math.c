#include "level_math.h"

#ifndef LEVEL_HOST
#include <pebble.h>
#else
int32_t atan2_lookup(int16_t y, int16_t x);
#endif

static int32_t wrap_angle(int32_t angle) {
  while (angle > LEVEL_TRIG_MAX / 2) angle -= LEVEL_TRIG_MAX;
  while (angle < -LEVEL_TRIG_MAX / 2) angle += LEVEL_TRIG_MAX;
  return angle;
}

bool level_projection_valid(int16_t x, int16_t y) {
  return (int32_t)x * x + (int32_t)y * y >= 250 * 250;
}

int32_t level_target_rotation(int16_t x, int16_t y, int32_t previous_rotation) {
  if (!level_projection_valid(x, y)) return previous_rotation;
  // Gravity is +X to the right and -Y toward the bottom of the watch screen.
  // Counter-rotate against the case's roll to keep the rendered baseline level.
  return wrap_angle(-atan2_lookup(x, -y));
}

int32_t level_smooth_rotation(int32_t current_rotation, int32_t target_rotation) {
  int32_t delta = wrap_angle(target_rotation - current_rotation);
  if (delta > -LEVEL_TRIG_MAX / 180 && delta < LEVEL_TRIG_MAX / 180) {
    return current_rotation;
  }
  int32_t step = delta / 2;
  if (step == 0) step = delta > 0 ? 1 : -1;
  return wrap_angle(current_rotation + step);
}
