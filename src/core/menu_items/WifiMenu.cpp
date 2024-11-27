#include "WifiMenu.h"
#include "core/display.h"
#include "core/wifi_common.h"
#include "core/wg.h"
#include "modules/wifi/clients.h"
#include "modules/wifi/dpwo.h"
#include "modules/wifi/evil_portal.h"
#include "modules/wifi/scan_hosts.h"
#include "modules/wifi/sniffer.h"
#include "modules/wifi/wardriving.h"
#include "modules/wifi/wifi_atks.h"
#include "modules/wifi/ap_info.h"

#ifndef LITE_VERSION
#include "modules/pwnagotchi/pwnagotchi.h"
#endif

void WifiMenu::optionsMenu() {
    if(!wifiConnected) {
        options = {
            {"polacz z wifi", [=]()  { wifiConnectMenu(WIFI_STA); }},  
            {"utworz ap",      [=]()  { wifiConnectMenu(WIFI_AP); displayInfo("pwd: " + bruceConfig.wifiAp.pwd, true); }},
        };
    } else {
        options = {{"rozlacz z wifi",   [=]()  { wifiDisconnect(); }} };
        if(WiFi.getMode() == WIFI_MODE_STA) options.push_back({"info o ap",   [=]()  { displayAPInfo(); }});
    }
    options.push_back({"ataki na wifi", [=]()     { wifi_atk_menu(); }});
    options.push_back({"wifi portal", [=]()   { EvilPortal(); }});
    options.push_back({"wardriving", [=]()    { Wardriving(); }});
#ifndef LITE_VERSION
    options.push_back({"telnet", [=]()        { telnet_setup(); }});
    options.push_back({"ssh", [=]()           { ssh_setup(); }});
    options.push_back({"dpwo", [=]()          { dpwo_setup(); }});
    options.push_back({"raw sniffer", [=]()   { sniffer_setup(); }});
    options.push_back({"skanuj hosty", [=]()    { local_scan_setup(); }});
    options.push_back({"wireguard", [=]()     { wg_setup(); }});
    options.push_back({"nygusgotchi",  [=]()   { brucegotchi_start(); }});
#endif
    options.push_back({"wroc do menu", [=]()     { backToMenu(); }});

    delay(200);
    loopOptions(options,false,true,"WiFi");
}

String WifiMenu::getName() {
    return _name;
}

void WifiMenu::draw() {
    tft.fillRect(iconX,iconY,80,80,bruceConfig.bgColor);
    tft.fillCircle(40+iconX,60+iconY,6,bruceConfig.priColor);
    tft.drawArc(40+iconX,60+iconY,26,20,130,230,bruceConfig.priColor, bruceConfig.bgColor);
    tft.drawArc(40+iconX,60+iconY,46,40,130,230,bruceConfig.priColor, bruceConfig.bgColor);
}
