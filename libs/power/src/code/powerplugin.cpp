#include "powerplugin.h"

#include <QQmlEngine>

#include "brightnesscontrol.h"
#include "batteryinfo.h"
#include "powerprofile.h"

void PowerPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<BrightnessControl>(uri, 1, 0, "BrightnessControl");
    qmlRegisterType<BatteryInfo>(uri, 1, 0, "BatteryInfo");
    qmlRegisterUncreatableType<Battery>(uri, 1, 0, "Battery", QStringLiteral("To be referenced from the model or controller."));
    qmlRegisterType<PowerProfile>(uri, 1, 0, "PowerProfile");
}
