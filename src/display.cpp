#include <display.h>
#include <touch.h>
#include "ui/ui_helpers.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    TFT_DE, TFT_VSYNC, TFT_HSYNC, TFT_PCLK,
    TFT_R0, TFT_R1, TFT_R2, TFT_R3, TFT_R4,
    TFT_G0, TFT_G1, TFT_G2, TFT_G3, TFT_G4, TFT_G5,
    TFT_B0, TFT_B1, TFT_B2, TFT_B3, TFT_B4,
    TFT_HSYNC_POLARITY, TFT_HSYNC_FRONT_PORCH, TFT_HSYNC_PULSE_WIDTH, TFT_HSYNC_BACK_PORCH,
    TFT_VSYNC_POLARITY, TFT_VSYNC_FRONT_PORCH, TFT_VSYNC_PULSE_WIDTH, TFT_VSYNC_BACK_PORCH,
    TFT_PCLK_ACTIVE_NEG, TFT_PREFER_SPEED);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    TFT_WIDTH, TFT_HEIGHT, bus );

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  if (touch_has_signal()) {
    if (touch_touched()) {

      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;

      #ifdef PRINT_TOUCH_DATA
        Serial.print("Data x: ");
        Serial.println(data->point.x);
        Serial.print("Data y: ");
        Serial.println(data->point.y);
      #endif
    } else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void display_init() {

  // configure BackLight
  ledcSetup(TFT_BL_CHANNEL, TFT_BL_FREQ, TFT_BL_RESOLUTION);
  ledcAttachPin(TFT_BL, TFT_BL_CHANNEL);
  ledcWrite(TFT_BL_CHANNEL, TFT_BL_MAX);

  // Init Display
  gfx->begin();

  //  touch.setTouch( calData );
}

void display_init2() {

  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * TFT_WIDTH * TFT_HEIGHT / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  if (!disp_draw_buf) {
    Serial.println("LVGL disp_draw_buf allocate failed!");
  } else {
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, TFT_WIDTH * TFT_HEIGHT / 4);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Initialize the (dummy) input device driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

  }
}

