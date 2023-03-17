#include "../ApplicationSettings.h"
#include "SendingCommandDialog.h"

SendingCommandDialog::SendingCommandDialog(const CommandMessage& command, const std::vector<DevicePanel*>& devicePanels)
        : Dialog(BinaryData::progress_svg, "Sending Command " + command.json, "Retry", "Cancel", &closeWhenCompleteButton, std::numeric_limits<int>::max(), true)
{
    addAndMakeVisible(deviceLabel);
    addAndMakeVisible(connectionLabel);
    addAndMakeVisible(completeLabel);
    addAndMakeVisible(table);
    addAndMakeVisible(closeWhenCompleteButton);

    const int colourTagColumnWidth = DevicePanelHeader::colourTagWidth + 5;
    table.getHeader().addColumn("", (int) ColumnIDs::colourTag, colourTagColumnWidth, colourTagColumnWidth, colourTagColumnWidth);
    table.getHeader().addColumn("", (int) ColumnIDs::device, 1);
    table.getHeader().addColumn("", (int) ColumnIDs::connection, 1);
    table.getHeader().addColumn("", (int) ColumnIDs::complete, 70, 70, 70);
    table.getHeader().setStretchToFitActive(true);
    table.setHeaderHeight(0);
    table.getViewport()->setScrollBarsShown(true, false);
    table.setColour(juce::TableListBox::backgroundColourId, UIColours::backgroundDark);
    table.updateContent();
    table.setWantsKeyboardFocus(false);

    for (auto* const devicePanel : devicePanels)
    {
        rows.push_back({ *devicePanel });
    }

    closeWhenCompleteButton.setClickingTogglesState(true);
    closeWhenCompleteButton.setToggleState(ApplicationSettings::getSingleton().closeSendingCommandDialogWhenComplete, juce::dontSendNotification);
    closeWhenCompleteButton.onClick = [&]
    {
        ApplicationSettings::getSingleton().closeSendingCommandDialogWhenComplete = closeWhenCompleteButton.getToggleState();
    };

    okCallback = [&, command]
    {
        for (auto& row : rows)
        {
            if (row.state == Row::State::complete)
            {
                continue;
            }

            row.state = Row::State::inProgress;

            row.devicePanel.sendCommands({ command }, this, [&, row = &row](const auto&, const auto& failedCommands)
            {
                row->state = (failedCommands.empty() == false) ? Row::State::failed : Row::State::complete;
                table.updateContent();

                for (const auto& row_ : rows)
                {
                    if (row_.state == Row::State::inProgress)
                    {
                        return;
                    }
                }

                for (size_t index = 0; index < rows.size(); index++)
                {
                    if (rows[index].state == Row::State::failed)
                    {
                        setOkButton(true);
                        setCancelButton(true);
                        table.scrollToEnsureRowIsOnscreen((int) index);
                        return;
                    }
                }

                okCallback = [&]
                {
                    return true;
                };
                setOkButton(true, "Close");
                setCancelButton(false);

                if (ApplicationSettings::getSingleton().closeSendingCommandDialogWhenComplete)
                {
                    startTimer(1000);
                }
            });
        }

        setOkButton(false);
        setCancelButton(false);

        table.updateContent();

        return false;
    };

    okCallback();

    setSize(600, calculateHeight(6));
}

void SendingCommandDialog::resized()
{
    Dialog::resized();

    auto bounds = getContentBounds(true);

    static constexpr int headerHeight = 30;
    bounds.removeFromTop(headerHeight);
    deviceLabel.setBounds(table.getHeader().getColumnPosition((int) ColumnIDs::device - 1).withHeight(headerHeight));
    connectionLabel.setBounds(table.getHeader().getColumnPosition((int) ColumnIDs::connection - 1).withHeight(headerHeight));
    completeLabel.setBounds(table.getHeader().getColumnPosition((int) ColumnIDs::complete - 1).withHeight(headerHeight));

    table.setBounds(bounds);
}

int SendingCommandDialog::getNumRows()
{
    return (int) rows.size();
}

void SendingCommandDialog::paintRowBackground(juce::Graphics& g, int rowNumber, int height, int, bool)
{
    if (rowNumber >= (int) rows.size())
    {
        return; // index may exceed size on Windows if display scaling >100%
    }

    g.setColour(rows[(size_t) rowNumber].devicePanel.getColourTag());
    g.fillRect(0, 0, DevicePanelHeader::colourTagWidth, height);
}

juce::Component* SendingCommandDialog::refreshComponentForCell(int rowNumber, int columnID, bool, juce::Component* existingComponentToUpdate)
{
    if (rowNumber >= (int) rows.size())
    {
        return existingComponentToUpdate; // index may exceed size on Windows if display scaling >100%
    }

    delete existingComponentToUpdate;

    switch ((ColumnIDs) columnID)
    {
        case ColumnIDs::colourTag:
            return nullptr;

        case ColumnIDs::device:
            return new SimpleLabel(rows[(size_t) rowNumber].devicePanel.getDeviceDescriptor());

        case ColumnIDs::connection:
            return new SimpleLabel(rows[(size_t) rowNumber].devicePanel.getConnection().getInfo()->toString());

        case ColumnIDs::complete:
            switch (rows[(size_t) rowNumber].state)
            {
                case Row::State::inProgress:
                    return new Icon(BinaryData::progress_svg, "In Progress", 0.6f);

                case Row::State::failed:
                    return new Icon(BinaryData::warning_orange_svg, "Failed", 0.6f);

                case Row::State::complete:
                    return new Icon(BinaryData::tick_green_svg, "Complete", 0.6f);

                default:
                    return nullptr;
            }

        default:
            return nullptr;
    }
}

void SendingCommandDialog::timerCallback()
{
    DialogLauncher::launchDialog(nullptr);
}
