// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#pragma once

#include "GraphWindow.h"
#include "OpenGL/Common/GLRenderer.h"
#include "Ximu3.hpp"

class RssiPercentageGraphWindow : public GraphWindow
{
public:
    RssiPercentageGraphWindow(const juce::ValueTree& windowLayout, const juce::Identifier& type_, ConnectionPanel& connectionPanel_, GLRenderer& glRenderer);

    ~RssiPercentageGraphWindow() override;

private:
    std::vector<uint64_t> callbackIDs;
    std::function<void(ximu3::XIMU3_RssiMessage)> rssiCallback;
};
