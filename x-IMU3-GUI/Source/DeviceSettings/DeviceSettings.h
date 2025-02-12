#pragma once

#include "CommandMessage.h"
#include "DeviceSettingsItem.h"
#include <juce_gui_basics/juce_gui_basics.h>

class DeviceSettings : public juce::TreeView,
                       private juce::ValueTree::Listener
{
public:
    DeviceSettings();

    ~DeviceSettings() override;

    std::vector<CommandMessage> getReadCommands() const;

    std::vector<CommandMessage> getWriteCommands(const bool replaceReadOnlyValuesWithNull) const;

    void setValue(const CommandMessage& response);

    juce::var getValue(const juce::String& key) const;

    void setStatus(const juce::String& key, const Setting::Status status, const juce::String& statusTooltip);

    std::function<void(const CommandMessage&)> onSettingModified;

private:
    juce::ValueTree settingsTree = juce::ValueTree::fromXml(BinaryData::DeviceSettings_xml);
    std::map<juce::String, juce::ValueTree> settingsMap = flatten(settingsTree);
    DeviceSettingsItem rootItem { settingsTree, settingsMap };

    bool ignoreCallback = false;

    static std::map<juce::String, juce::ValueTree> flatten(const juce::ValueTree& parent);

    static CommandMessage getWriteCommand(juce::ValueTree setting);

    void valueTreePropertyChanged(juce::ValueTree& tree, const juce::Identifier&) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeviceSettings)
};
