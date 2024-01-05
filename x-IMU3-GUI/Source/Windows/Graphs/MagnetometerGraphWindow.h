// This file was generated by x-IMU3-GUI/Source/Windows/Graphs/generate_graph_windows.py

#pragma once

#include "GraphWindow.h"
#include "OpenGL/Common/GLRenderer.h"
#include "Ximu3.hpp"

class MagnetometerGraphWindow : public GraphWindow
{
public:
    MagnetometerGraphWindow(const juce::ValueTree& windowLayout_, const juce::Identifier& type_, ConnectionPanel& connectionPanel_, GLRenderer& glRenderer);

    ~MagnetometerGraphWindow() override;

private:
    std::vector<uint64_t> callbackIDs;
    std::function<void(ximu3::XIMU3_MagnetometerMessage)> magnetometerCallback;
};
