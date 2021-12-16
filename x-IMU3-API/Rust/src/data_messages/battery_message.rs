// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

use std::fmt;
use std::mem::size_of;
use crate::data_messages::*;
use crate::decode_error::*;

#[repr(C)]
#[derive(Copy, Clone)]
pub struct BatteryMessage {
    pub timestamp: u64,
    pub percentage: f32,
    pub voltage: f32,
    pub charging_status: f32,
}

impl DataMessage for BatteryMessage {
    fn get_ascii_id() -> u8 {
        'B' as u8
    }

    fn parse_ascii(message: &str) -> Result<Self, DecodeError> {
        match scan_fmt!( message, "{},{d},{f},{f},{f}\r\n",  char, u64, f32, f32, f32) {
            Ok((_, timestamp, percentage, voltage, charging_status)) => Ok(BatteryMessage { timestamp, percentage, voltage, charging_status }),
            Err(_) => Err(DecodeError::UnableToParseAsciiMessage),
        }
    }

    fn parse_binary(message: &[u8]) -> Result<Self, DecodeError> {
        #[repr(C, packed)]
        struct BinaryMessage {
            id: u8,
            timestamp: u64,
            percentage: f32,
            voltage: f32,
            charging_status: f32,
            termination: u8,
        }

        if message.len() != size_of::<BinaryMessage>() {
            return Err(DecodeError::InvalidBinaryMessageLength);
        }

        let binary_message = unsafe {
            let ref binary_message = *(message.as_ptr() as *const BinaryMessage);
            binary_message
        };

        Ok(BatteryMessage { timestamp: binary_message.timestamp, percentage: binary_message.percentage, voltage: binary_message.voltage, charging_status: binary_message.charging_status })
    }

    fn get_csv_file_name(&self) -> &'static str {
        "Battery.csv"
    }

    fn get_csv_headings(&self) -> &'static str {
        "Timestamp (us),Percentage (%),Voltage (V),Charging Status\n"
    }

    fn to_csv_row(&self) -> String {
        format!("{},{:.6},{:.6},{:.6}\n", self.timestamp, self.percentage, self.voltage, self.charging_status)
    }

    fn to_ascii(&self) -> String {
        format!("{},{},{:.4},{:.4},{:.4}\r\n", Self::get_ascii_id() as char, self.timestamp, self.percentage, self.voltage, self.charging_status)
    }
}

impl fmt::Display for BatteryMessage {
    fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
        write!(formatter, "{:>8} us {:>8.3} % {:>8.3} V {:>8.3}", self.timestamp, self.percentage, self.voltage, self.charging_status)
    }
}
