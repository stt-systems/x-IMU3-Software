// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#pragma once

#include "../../OpenGL/Common/GLRenderer.h"
#include "GraphWindow.h"
#include "Ximu3.hpp"

class ReceivedMessageRateGraphWindow : public GraphWindow
{
public:
    ReceivedMessageRateGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, DevicePanel& devicePanel_, GLRenderer& glRenderer);

    ~ReceivedMessageRateGraphWindow() override;

private:
    static juce::ValueTree settingsTree_;

    std::vector<uint64_t> callbackIDs;
    std::function<void(ximu3::XIMU3_Statistics)> statisticsCallback;
};
