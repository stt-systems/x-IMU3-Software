// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

#pragma once

#include "../../../C/Ximu3.h"

using namespace System;

namespace Ximu3
{
    public ref class QuaternionMessage
    {
    internal:
        QuaternionMessage(ximu3::XIMU3_QuaternionMessage message) : message{ new ximu3::XIMU3_QuaternionMessage{message} }
        {
        }

    public:
        ~QuaternionMessage()
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

        property float WElement
        {
            float get()
            {
                return message->w_element;
            }
        }

        property float XElement
        {
            float get()
            {
                return message->x_element;
            }
        }

        property float YElement
        {
            float get()
            {
                return message->y_element;
            }
        }

        property float ZElement
        {
            float get()
            {
                return message->z_element;
            }
        }

        String^ ToString() override
        {
            return gcnew String(ximu3::XIMU3_quaternion_message_to_string(*message));
        }

    private:
        ximu3::XIMU3_QuaternionMessage* message;
    };
}
