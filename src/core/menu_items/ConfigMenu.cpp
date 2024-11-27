#include "ConfigMenu.h"
#include "core/display.h"
#include "core/settings.h"
#include "core/i2c_finder.h"
#include "core/wifi_common.h"

void ConfigMenu::optionsMenu() {
    options = {
        {"jasnosc",    [=]() { setBrightnessMenu(); }},
        {"wygaszanie",      [=]() { setDimmerTimeMenu(); }},
        {"orientacja",   [=]() { gsetRotation(true); }},
        {"kolor ui",      [=]() { setUIColor(); }},
        {"dzwiek",  [=]() { setSoundConfig(); }},
        {"startup wifi",  [=]() { setWifiStartupConfig(); }},
        {"startup app",   [=]() { setStartupApp(); }},
        {"zegar",         [=]() { setClock(); }},
        {"uspij",         [=]() { setSleepMode(); }},
        {"restartuj",       [=]() { ESP.restart(); }},
    };

  #if defined(T_EMBED_1101)
    options.push_back({"wylacz",  [=]() { digitalWrite(PIN_POWER_ON,LOW); esp_sleep_enable_ext0_wakeup(GPIO_NUM_6,LOW); esp_deep_sleep_start(); }});
  #endif
    if (bruceConfig.devMode) options.push_back({"dev mode", [=]() { devMenu(); }});

    options.push_back({"wroc do menu", [=]() { backToMenu(); }});

    delay(200);
    loopOptions(options,false,true,"Config");
}

void ConfigMenu::devMenu(){
    options = {
        {"adres mac",   [=]() { checkMAC(); }},
        {"I2C finder",    [=]() { find_i2c_addresses(); }},
        {"wroc",          [=]() { optionsMenu(); }},
    };

    delay(200);
    loopOptions(options,false,true,"dev mode");
}

String ConfigMenu::getName() {
    return _name;
}

void ConfigMenu::draw() {
    tft.fillRect(iconX,iconY,80,80,bruceConfig.bgColor);
    int i=0;
    for(i=0;i<6;i++) {
        tft.drawArc(40+iconX,40+iconY,30,20,15+60*i,45+60*i,bruceConfig.priColor,bruceConfig.bgColor,true);
    }
    tft.drawArc(40+iconX,40+iconY,22,8,0,360,bruceConfig.priColor,bruceConfig.bgColor,false);
}