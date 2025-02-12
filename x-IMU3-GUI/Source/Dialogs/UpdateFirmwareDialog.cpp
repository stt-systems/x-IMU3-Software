#include "ApplicationSettings.h"
#include "Firmware/Firmware.h"
#include "UpdateFirmwareDialog.h"
#include "UpdatingFirmwareDialog.h"

UpdateFirmwareDialog::UpdateFirmwareDialog() : Dialog(BinaryData::tools_svg, "Update Firmware", "Update", "Cancel", &warningIcon, iconButtonWidth)
{
    addAndMakeVisible(deviceLabel);
    addAndMakeVisible(deviceValue);
    addAndMakeVisible(hexFileLabel);
    addAndMakeVisible(hexFileSelector);
    addAndMakeVisible(warningIcon);
    addAndMakeVisible(warningLabel);

    const auto hexFile = ApplicationSettings::getDirectory().getChildFile(Firmware::hexFile);
    hexFile.replaceWithData(Firmware::memoryBlock.getData(), Firmware::memoryBlock.getSize());
    hexFileSelector.setFiles({hexFile});

    deviceValue.onChange = hexFileSelector.onChange = [&]
    {
        setOkButton(getConnectionInfo() != nullptr && hexFileSelector.isValid());
    };
    setOkButton(false);

    setSize(600, calculateHeight(2));
}

void UpdateFirmwareDialog::resized()
{
    Dialog::resized();

    auto bounds = getContentBounds();

    auto deviceRow = bounds.removeFromTop(UILayout::textComponentHeight);
    deviceLabel.setBounds(deviceRow.removeFromLeft(columnWidth));
    deviceValue.setBounds(deviceRow);

    bounds.removeFromTop(Dialog::margin);

    auto hexFileRow = bounds.removeFromTop(UILayout::textComponentHeight);
    hexFileLabel.setBounds(hexFileRow.removeFromLeft(columnWidth));
    hexFileSelector.setBounds(hexFileRow);

    warningLabel.setBounds(juce::Rectangle<int>::leftTopRightBottom(warningIcon.getRight(), warningIcon.getY(), bounds.getRight(), warningIcon.getBottom()));
}

std::unique_ptr<ximu3::ConnectionInfo> UpdateFirmwareDialog::getConnectionInfo() const
{
    if (deviceValue.getSelectedId() == 0)
    {
        return nullptr;
    }

    const auto& device = devices[(size_t) deviceValue.getSelectedId() - 1];
    switch (device.connection_type)
    {
        case ximu3::XIMU3_ConnectionTypeUsb:
            return std::make_unique<ximu3::UsbConnectionInfo>(device.usb_connection_info);
        case ximu3::XIMU3_ConnectionTypeSerial:
            return std::make_unique<ximu3::SerialConnectionInfo>(device.serial_connection_info);
        case ximu3::XIMU3_ConnectionTypeBluetooth:
        case ximu3::XIMU3_ConnectionTypeTcp:
        case ximu3::XIMU3_ConnectionTypeUdp:
        case ximu3::XIMU3_ConnectionTypeFile:
            return nullptr;
    }

    return nullptr;
}

juce::File UpdateFirmwareDialog::getHexFile() const
{
    return hexFileSelector.getFiles()[0];
}

void UpdateFirmwareDialog::launch(juce::ThreadPool& threadPool)
{
    DialogQueue::getSingleton().pushFront(std::make_unique<UpdateFirmwareDialog>(), [&threadPool]
    {
        if (const auto* const updateFirmwareDialog = dynamic_cast<UpdateFirmwareDialog*>(DialogQueue::getSingleton().getActive()))
        {
            DialogQueue::getSingleton().pushFront(std::make_unique<UpdatingFirmwareDialog>(updateFirmwareDialog->getConnectionInfo(), updateFirmwareDialog->getHexFile(), threadPool));
        }
        return true;
    });
}
