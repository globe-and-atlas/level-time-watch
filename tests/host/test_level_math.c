#include <assert.h>
#include <math.h>
#include <stdint.h>

#include "level_math.h"

int32_t atan2_lookup(int16_t y, int16_t x) {
  const double radians = atan2((double)y, (double)x);
  return (int32_t)lround(radians * LEVEL_TRIG_MAX / (2.0 * 3.141592653589793));
}

static int near(int32_t actual, int32_t expected) {
  return actual >= expected - 2 && actual <= expected + 2;
}

int main(void) {
  assert(level_projection_valid(0, -1000));
  assert(!level_projection_valid(0, 0));
  assert(!level_projection_valid(200, 0));
  assert(near(level_target_rotation(0, -1000, 123), 0));
  assert(near(level_target_rotation(707, -707, 0), -LEVEL_TRIG_MAX / 8));
  assert(near(level_target_rotation(-707, -707, 0), LEVEL_TRIG_MAX / 8));
  assert(level_target_rotation(0, 0, 4321) == 4321);
  assert(level_smooth_rotation(0, -LEVEL_TRIG_MAX / 8) < 0);
  assert(level_smooth_rotation(0, LEVEL_TRIG_MAX / 8) > 0);
  assert(level_smooth_rotation(100, 101) == 100);
  return 0;
}
