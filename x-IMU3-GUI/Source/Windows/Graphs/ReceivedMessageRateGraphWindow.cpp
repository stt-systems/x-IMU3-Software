// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#include "Convert.h"
#include "DevicePanel/DevicePanel.h"
#include "ReceivedMessageRateGraphWindow.h"

juce::ValueTree ReceivedMessageRateGraphWindow::settingsTree_("ReceivedMessageRateGraphSettings");

ReceivedMessageRateGraphWindow::ReceivedMessageRateGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, DevicePanel& devicePanel_, GLRenderer& glRenderer)
        : GraphWindow(windowLayout, type_, devicePanel_,
                      glRenderer,
                      "Throughput (messages/s)",
                      { "" },
                      { UIColours::graphChannel1 },
                      settingsTree_,
                      true)
{
    callbackIDs.push_back(devicePanel.getConnection()->addStatisticsCallback(statisticsCallback = [&](auto message)
    {
        update(message.timestamp, { (float) message.message_rate });
    }));
}

ReceivedMessageRateGraphWindow::~ReceivedMessageRateGraphWindow()
{
    for (const auto callbackID : callbackIDs)
    {
        devicePanel.getConnection()->removeCallback(callbackID);
    }
}
