#ifndef DISPLAY_TFT_H
#define DISPLAY_TFT_H

#include <Arduino_GFX_Library.h>

#define TFT_BL 2
#define TFT_BL_CHANNEL 0
#define TFT_BL_FREQ 5000
#define TFT_BL_RESOLUTION 8
#define TFT_BL_MAX 255

#define TFT_DE 41
#define TFT_VSYNC 40
#define TFT_HSYNC 39
#define TFT_PCLK 42
#define TFT_R0 14
#define TFT_R1 21
#define TFT_R2 47
#define TFT_R3 48
#define TFT_R4 45
#define TFT_G0 9
#define TFT_G1 46
#define TFT_G2 3
#define TFT_G3 8
#define TFT_G4 16
#define TFT_G5 1
#define TFT_B0 15
#define TFT_B1 7
#define TFT_B2 6
#define TFT_B3 5
#define TFT_B4 4
#define TFT_HSYNC_POLARITY 0
#define TFT_HSYNC_FRONT_PORCH 210
#define TFT_HSYNC_PULSE_WIDTH 30
#define TFT_HSYNC_BACK_PORCH 16
#define TFT_VSYNC_POLARITY 0
#define TFT_VSYNC_FRONT_PORCH 22
#define TFT_VSYNC_PULSE_WIDTH 13
#define TFT_VSYNC_BACK_PORCH 10
#define TFT_PCLK_ACTIVE_NEG 1
#define TFT_PREFER_SPEED 16000000
#define TFT_WIDTH 800
#define TFT_HEIGHT 480

#define PRINT_TOUCH_DATA

extern Arduino_ESP32RGBPanel *bus;

extern Arduino_RGB_Display *gfx;

void display_init();
void display_init2();
#endif
