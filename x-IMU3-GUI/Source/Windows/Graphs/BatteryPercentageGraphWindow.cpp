// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#include "../../Convert.h"
#include "../../DevicePanel/DevicePanel.h"
#include "BatteryPercentageGraphWindow.h"

juce::ValueTree BatteryPercentageGraphWindow::settingsTree_("BatteryPercentageGraphSettings");

BatteryPercentageGraphWindow::BatteryPercentageGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, DevicePanel& devicePanel_, GLRenderer& glRenderer)
        : GraphWindow(windowLayout, type_, devicePanel_,
                      glRenderer,
                      "Percentage (%)",
                      { "" },
                      { UIColours::graphChannel1 },
                      settingsTree_,
                      true)
{
    callbackIDs.push_back(devicePanel.getConnection()->addBatteryCallback(batteryCallback = [&](auto message)
    {
        update(message.timestamp, { message.percentage });
    }));
}

BatteryPercentageGraphWindow::~BatteryPercentageGraphWindow()
{
    for (const auto callbackID : callbackIDs)
    {
        devicePanel.getConnection()->removeCallback(callbackID);
    }
}
