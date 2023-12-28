#include <lvgl.h>
#include <display.h>
#include <touch.h>
#include "ui/ui.h"
#include <screensaver.h>

ulong nextStepScreenSaver;
ulong goScreenSaver;
bool screenSaverActive = false;

void setup()
{
  delay(1000);
  Serial.begin(115200);
  while (!Serial)
  {
    yield();
  };

  Serial.println("-- setup --");
  display_init();
  Serial.println("-- display initialized --");
  lv_init();
  Serial.println("-- lv initialized --");
  touch_init();
  Serial.println("-- touch initialized --");
  display_init2();
  Serial.println("-- display initialized --");
  ui_init();
  Serial.println("-- ui initialized --");
  Serial.println("-- setup done --");

  goScreenSaver = millis() + 5000;
}

void loop()
{

  auto const now = millis();
  if (screenSaverActive)
  {
    if (now > nextStepScreenSaver)
    {
      // Serial.println("Stepping screensaver");
      nextStepScreenSaver = now + 40;
      stepScreenSaver();
    }
  }
  else
  {
    if (now > goScreenSaver)
    {
      Serial.println("Going to screensaver");
      screensaver_init();
      lv_disp_load_scr(ui_ScreenSaver);
      screenSaverActive = true;
    }
  }

  lv_timer_handler(); /* let the GUI do its work */
}
