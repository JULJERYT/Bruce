#include "OthersMenu.h"
#include "core/display.h"
#include "core/sd_functions.h"
#include "modules/others/openhaystack.h"
#include "modules/others/gps_tracker.h"
#include "modules/others/tururururu.h"
#include "modules/others/webInterface.h"
#include "modules/others/qrcode_menu.h"
#include "modules/others/mic.h"
#include "modules/bjs_interpreter/interpreter.h"

#include "modules/others/bad_usb.h"
#ifdef HAS_RGB_LED
#include "modules/others/led_control.h"
#endif

void OthersMenu::optionsMenu() {
    options = {
        {"sd card",      [=]() { loopSD(SD); }},
        {"littlefs",     [=]() { loopSD(LittleFS); }},
        {"webui",        [=]() { loopOptionsWebUi(); }},
        {"kody qr",      [=]() { qrcode_menu(); }},
        {"tracker gps",  [=]() { GPSTracker(); }},
        {"gierka",    [=]() { shark_setup(); }},
    #ifdef MIC_SPM1423
        {"mic spectrum", [=]() { mic_test(); }},
    #endif
        {"bad usb",       [=]()  { usb_setup(); }},
    #ifdef HAS_KEYBOARD_HID
        {"USB Keyboard", [=]()  { usb_keyboard(); }},
    #endif
    #ifdef HAS_RGB_LED
        {"LED Control",  [=]()  { ledrgb_setup(); }},  // IncursioHack
        {"LED FLash",    [=]()  { ledrgb_flash(); }},  // IncursioHack
    #endif
    #ifndef LITE_VERSION
        {"fake airtag", [=]()  { openhaystack_setup(); }},
    #endif
    #if !defined(CORE) && !defined(CORE2)
        {"interpreter", [=]()   { run_bjs_script(); }},
    #endif
        {"wroc do menu",    [=]()  { backToMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,"Others");
}

String OthersMenu::getName() {
    return _name;
}

void OthersMenu::draw() {
    tft.fillRect(iconX,iconY,80,80,bruceConfig.bgColor);
    tft.fillCircle(40+iconX,40+iconY,7,bruceConfig.priColor);
    tft.drawArc(40+iconX,40+iconY,18,15,0,340,bruceConfig.priColor,bruceConfig.bgColor);
    tft.drawArc(40+iconX,40+iconY,25,22,20,360,bruceConfig.priColor,bruceConfig.bgColor);
    tft.drawArc(40+iconX,40+iconY,32,29,0,200,bruceConfig.priColor,bruceConfig.bgColor);
    tft.drawArc(40+iconX,40+iconY,32,29,240,360,bruceConfig.priColor,bruceConfig.bgColor);
}