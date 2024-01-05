// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#include "ConnectionPanel/ConnectionPanel.h"
#include "Convert.h"
#include "ReceivedMessageRateGraphWindow.h"

ReceivedMessageRateGraphWindow::ReceivedMessageRateGraphWindow(const juce::ValueTree& windowLayout_, const juce::Identifier& type_, ConnectionPanel& connectionPanel_, GLRenderer& glRenderer)
        : GraphWindow(windowLayout_, type_, connectionPanel_,
                      glRenderer,
                      "Throughput (messages/s)",
                      { "" },
                      { UIColours::graphChannel1 },
                      true)
{
    callbackIDs.push_back(connectionPanel.getConnection()->addStatisticsCallback(statisticsCallback = [&](auto message)
    {
        update(message.timestamp, { (float) message.message_rate });
    }));
}

ReceivedMessageRateGraphWindow::~ReceivedMessageRateGraphWindow()
{
    for (const auto callbackID : callbackIDs)
    {
        connectionPanel.getConnection()->removeCallback(callbackID);
    }
}
