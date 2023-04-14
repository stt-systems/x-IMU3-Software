// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#include "../../Convert.h"
#include "RssiPercentageGraphWindow.h"

Graph::Settings RssiPercentageGraphWindow::settings = Graph::Settings(false);

RssiPercentageGraphWindow::RssiPercentageGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, DevicePanel& devicePanel_, GLRenderer& glRenderer)
        : GraphWindow(windowLayout, type_, devicePanel_, glRenderer, "Percentage (%)", {{{}, juce::Colours::yellow }}, settings)
{
    callbackIDs.push_back(devicePanel.getConnection().addRssiCallback(rssiCallback = [&](auto message)
    {
        update(message.timestamp, { message.percentage });
    }));
}

RssiPercentageGraphWindow::~RssiPercentageGraphWindow()
{
    for (const auto callbackID : callbackIDs)
    {
        devicePanel.getConnection().removeCallback(callbackID);
    }
}
