#ifndef LEVEL_MATH_H
#define LEVEL_MATH_H

#include <stdbool.h>
#include <stdint.h>

#define LEVEL_TRIG_MAX 65536

bool level_projection_valid(int16_t x, int16_t y);
int32_t level_target_rotation(int16_t x, int16_t y, int32_t previous_rotation);
int32_t level_smooth_rotation(int32_t current_rotation, int32_t target_rotation);

#endif
