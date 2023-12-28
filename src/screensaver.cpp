#include <ui/ui.h>
#include <screensaver.h>
#include <HardwareSerial.h>

#define SCREENSAVER_SPEED 6
int imageX;
int imageY;
int directionX = 1;
int directionY = 1;
int stepX;
int stepY;
int boundaryX;
int boundaryY;

void calculateY() {
    lv_sqrt_res_t res;
    lv_sqrt(SCREENSAVER_SPEED * SCREENSAVER_SPEED - stepX * stepX, &res, 0x800);
    stepY = res.i;
}

void calculateVector() {
    stepX = rand() % SCREENSAVER_SPEED;
    calculateY();
    Serial.print("stepX: ");
      Serial.println(stepX);
    Serial.print("stepY: ");
      Serial.println(stepY);
}

void screensaver_init() {
    Serial.println("initializing screensaver");
    lv_obj_set_align(ui_imageStation, LV_ALIGN_TOP_LEFT);
    lv_obj_set_parent(ui_imageStation,ui_ScreenSaver);
    lv_obj_set_align(ui_imageStation, LV_ALIGN_TOP_LEFT);
    boundaryX = lv_obj_get_width(ui_ScreenSaver) - lv_obj_get_width(ui_imageStation);
    boundaryY = lv_obj_get_height(ui_ScreenSaver) - lv_obj_get_height(ui_imageStation);
    lv_obj_set_pos(ui_imageStation, boundaryX / 2, boundaryY / 2);
    calculateVector();
}

void stepScreenSaver() {
    bool newVector = false;
    int newX;
    int newY;
    if (directionX == 1) {
        newX = lv_obj_get_x(ui_imageStation) + stepX;
        if (newX >= boundaryX) {
            newX = boundaryX;
            newVector = true;
            directionX = -1;
        }
    } else {
        newX = lv_obj_get_x(ui_imageStation) - stepX;
        if (newX <= 0) {
            newX = 0;
            newVector = true;
            directionX = 1;
        }
    }
    if (directionY == 1) {
        newY = lv_obj_get_y(ui_imageStation) + stepY;
        if (newY >= boundaryY) {
            newY = boundaryY;
            newVector = true;
            directionY = -1;
        }
    } else {
        newY = lv_obj_get_y(ui_imageStation) - stepY;
        if (newY <= 0) {
            newY = 0;
            newVector = true;
            directionY = 1;
        }
    }
    lv_obj_set_pos(ui_imageStation, newX, newY);
    if (newVector) {
        newVector = false;
        calculateVector();
    }

}

