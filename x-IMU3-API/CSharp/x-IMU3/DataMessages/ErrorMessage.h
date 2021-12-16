// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

#pragma once

#include "../../../C/Ximu3.h"

using namespace System;

namespace Ximu3
{
    public ref class ErrorMessage
    {
    internal:
        ErrorMessage(ximu3::XIMU3_ErrorMessage message) : message{ new ximu3::XIMU3_ErrorMessage{message} }
        {
        }

    public:
        ~ErrorMessage()
        {
            delete message;
        }

        property UInt64 Timestamp
        {
            UInt64 get()
            {
                return message->timestamp;
            }
        }

        property String^ BytesAsString
        {
            String^ get()
            {
                return gcnew String(message->char_array);
            }
        }

        property array<System::Byte>^ Bytes
        {
            array<System::Byte>^ get()
            {
                array<System::Byte>^ bytes = gcnew array<System::Byte>((int)message->number_of_bytes);

                for (int index = 0; index < bytes->Length; index++)
                {
                    bytes[index] = message->char_array[index];
                }

                return bytes;
            }
        }

        String^ ToString() override
        {
            return gcnew String(ximu3::XIMU3_error_message_to_string(*message));
        }

    private:
        ximu3::XIMU3_ErrorMessage* message;
    };
}
