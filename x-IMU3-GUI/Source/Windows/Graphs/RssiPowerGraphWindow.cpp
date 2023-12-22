// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#include "ConnectionPanel/ConnectionPanel.h"
#include "Convert.h"
#include "RssiPowerGraphWindow.h"

RssiPowerGraphWindow::RssiPowerGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, ConnectionPanel& connectionPanel_, GLRenderer& glRenderer)
        : GraphWindow(windowLayout, type_, connectionPanel_,
                      glRenderer,
                      "Power (dBm)",
                      { "" },
                      { UIColours::graphChannel1 },
                      true)
{
    callbackIDs.push_back(connectionPanel.getConnection()->addRssiCallback(rssiCallback = [&](auto message)
    {
        update(message.timestamp, { message.power });
    }));
}

RssiPowerGraphWindow::~RssiPowerGraphWindow()
{
    for (const auto callbackID : callbackIDs)
    {
        connectionPanel.getConnection()->removeCallback(callbackID);
    }
}
