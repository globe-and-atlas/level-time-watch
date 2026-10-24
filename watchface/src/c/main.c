#include <pebble.h>
#include <string.h>

#include "level_math.h"

#define SOURCE_W 180
#define SOURCE_H 84
#define PERSIST_STYLE 1
#define PERSIST_DATE 2

typedef struct {
  GColor background;
  GColor time;
  GColor detail;
  GColor accent;
} Style;

static Window *s_window;
static Layer *s_face_layer;
static GBitmap *s_text_bitmap;
static bool s_bitmap_dirty = true;
static int s_style = 0;
static int s_date = 0;
static int32_t s_rotation = 0;
static bool s_rotation_ready = false;
static char s_time_text[8];
static char s_detail_text[16];

static Style style_for(int style) {
  switch (style) {
    case 1: return (Style){GColorFromHEX(0xFFFFAA), GColorBlack,
                           GColorDarkGray, GColorBlack};
    case 2: return (Style){GColorBlack, GColorChromeYellow,
                           GColorChromeYellow, GColorChromeYellow};
    case 3: return (Style){GColorFromHEX(0x555500), GColorWhite,
                           GColorLightGray, GColorWhite};
    case 4: return (Style){GColorBlack, GColorWhite,
                           GColorWhite, GColorOrange};
    case 5: return (Style){GColorLightGray, GColorBlack,
                           GColorDarkGray, GColorBlack};
    default: return (Style){GColorBlack, GColorWhite,
                            GColorLightGray, GColorWhite};
  }
}

static void refresh_clock(void) {
  time_t now = time(NULL);
  struct tm *local = localtime(&now);
  if (!local) return;
  char next_time[sizeof(s_time_text)];
  char next_detail[sizeof(s_detail_text)] = "";
  strftime(next_time, sizeof(next_time), clock_is_24h_style() ? "%H:%M" : "%I:%M", local);
  if (!clock_is_24h_style() && next_time[0] == '0') {
    memmove(next_time, next_time + 1, strlen(next_time));
  }
  if (s_date == 1) strftime(next_detail, sizeof(next_detail), "%Y-%m-%d", local);
  if (s_date == 2) strftime(next_detail, sizeof(next_detail), "%m/%d/%Y", local);
  if (s_date == 3) strftime(next_detail, sizeof(next_detail), "%d/%m/%Y", local);
  if (strcmp(s_time_text, next_time) || strcmp(s_detail_text, next_detail)) {
    strncpy(s_time_text, next_time, sizeof(s_time_text));
    strncpy(s_detail_text, next_detail, sizeof(s_detail_text));
    s_bitmap_dirty = true;
  }
}

static void capture_text(GContext *ctx, Style palette) {
  if (!s_text_bitmap) return;
  graphics_context_set_fill_color(ctx, palette.background);
  graphics_fill_rect(ctx, GRect(0, 0, SOURCE_W, SOURCE_H), 0, GCornerNone);
  graphics_context_set_text_color(ctx, palette.time);
  GFont time_font = fonts_get_system_font(s_style == 5 ? FONT_KEY_BITHAM_42_LIGHT
                                                 : FONT_KEY_LECO_60_BOLD_NUMBERS_AM_PM);
  graphics_draw_text(ctx, s_time_text, time_font,
                     GRect(0, 0, SOURCE_W, 62), GTextOverflowModeTrailingEllipsis,
                     GTextAlignmentCenter, NULL);

  if (s_style == 2) {
    BatteryChargeState battery = battery_state_service_peek();
    int fill = 30 * battery.charge_percent / 100;
    graphics_context_set_stroke_color(ctx, palette.detail);
    graphics_draw_rect(ctx, GRect(73, 66, 34, 9));
    graphics_context_set_fill_color(ctx, palette.detail);
    graphics_fill_rect(ctx, GRect(75, 68, fill, 5), 0, GCornerNone);
  } else {
    if (s_style == 4) {
      graphics_context_set_fill_color(ctx, palette.accent);
      graphics_fill_circle(ctx, GPoint(42, 70), 3);
    }
    if (s_detail_text[0]) {
      graphics_context_set_text_color(ctx, palette.detail);
      graphics_draw_text(ctx, s_detail_text,
                         fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
                         GRect(0, 56, SOURCE_W, 28),
                         GTextOverflowModeTrailingEllipsis,
                         GTextAlignmentCenter, NULL);
    }
  }

  GBitmap *framebuffer = graphics_capture_frame_buffer_format(ctx, GBitmapFormat8Bit);
  if (!framebuffer) return;
  for (int y = 0; y < SOURCE_H; y++) {
    GBitmapDataRowInfo source = gbitmap_get_data_row_info(framebuffer, y);
    GBitmapDataRowInfo dest = gbitmap_get_data_row_info(s_text_bitmap, y);
    for (int x = 0; x < SOURCE_W; x++) {
      uint8_t pixel = source.data[x];
      dest.data[x] = pixel == palette.background.argb ? 0 : pixel;
    }
  }
  graphics_release_frame_buffer(ctx, framebuffer);
  s_bitmap_dirty = false;
}

static void draw_face(Layer *layer, GContext *ctx) {
  Style palette = style_for(s_style);
  GRect bounds = layer_get_bounds(layer);
  graphics_context_set_fill_color(ctx, palette.background);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  if (s_bitmap_dirty) capture_text(ctx, palette);
  graphics_context_set_fill_color(ctx, palette.background);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  if (s_text_bitmap) {
    graphics_context_set_compositing_mode(ctx, GCompOpSet);
    graphics_draw_rotated_bitmap(ctx, s_text_bitmap,
                                 GPoint(SOURCE_W / 2, SOURCE_H / 2),
                                 s_rotation,
                                 GPoint(bounds.size.w / 2, bounds.size.h / 2));
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits changed) {
  (void)tick_time;
  (void)changed;
  refresh_clock();
  layer_mark_dirty(s_face_layer);
}

static void accel_handler(AccelData *samples, uint32_t count) {
  if (!count || samples[count - 1].did_vibrate) return;
  AccelData sample = samples[count - 1];
  int32_t target = level_target_rotation(sample.x, sample.y, s_rotation);
  int32_t next = s_rotation_ready ? level_smooth_rotation(s_rotation, target) : target;
  s_rotation_ready = true;
  if (next != s_rotation) {
    s_rotation = next;
    layer_mark_dirty(s_face_layer);
  }
}

static void inbox_received(DictionaryIterator *iterator, void *context) {
  (void)context;
  Tuple *style = dict_find(iterator, MESSAGE_KEY_SETTING_STYLE);
  Tuple *date = dict_find(iterator, MESSAGE_KEY_SETTING_DATE);
  if (style && style->value->int32 >= 0 && style->value->int32 <= 5) {
    s_style = style->value->int32;
    persist_write_int(PERSIST_STYLE, s_style);
    s_bitmap_dirty = true;
  }
  if (date && date->value->int32 >= 0 && date->value->int32 <= 3) {
    s_date = date->value->int32;
    persist_write_int(PERSIST_DATE, s_date);
    refresh_clock();
    s_bitmap_dirty = true;
  }
  layer_mark_dirty(s_face_layer);
}

static void init(void) {
  s_style = persist_exists(PERSIST_STYLE) ? persist_read_int(PERSIST_STYLE) : 0;
  if (s_style < 0 || s_style > 5) s_style = 0;
  s_date = persist_exists(PERSIST_DATE) ? persist_read_int(PERSIST_DATE) : 0;
  if (s_date < 0 || s_date > 3) s_date = 0;
  s_text_bitmap = gbitmap_create_blank(GSize(SOURCE_W, SOURCE_H), GBitmapFormat8Bit);
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  s_face_layer = layer_create(layer_get_bounds(window_get_root_layer(s_window)));
  layer_set_update_proc(s_face_layer, draw_face);
  layer_add_child(window_get_root_layer(s_window), s_face_layer);
  window_stack_push(s_window, true);
  refresh_clock();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  accel_data_service_subscribe(10, accel_handler);
  app_message_register_inbox_received(inbox_received);
  app_message_open(128, 128);
}

static void deinit(void) {
  accel_data_service_unsubscribe();
  tick_timer_service_unsubscribe();
  app_message_deregister_callbacks();
  if (s_text_bitmap) gbitmap_destroy(s_text_bitmap);
  if (s_face_layer) layer_destroy(s_face_layer);
  if (s_window) window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
