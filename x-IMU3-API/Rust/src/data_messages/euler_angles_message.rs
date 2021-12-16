// This file was generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

use std::fmt;
use std::mem::size_of;
use crate::data_messages::*;
use crate::decode_error::*;

#[repr(C)]
#[derive(Copy, Clone)]
pub struct EulerAnglesMessage {
    pub timestamp: u64,
    pub roll: f32,
    pub pitch: f32,
    pub yaw: f32,
}

impl DataMessage for EulerAnglesMessage {
    fn get_ascii_id() -> u8 {
        'A' as u8
    }

    fn parse_ascii(message: &str) -> Result<Self, DecodeError> {
        match scan_fmt!( message, "{},{d},{f},{f},{f}\r\n",  char, u64, f32, f32, f32) {
            Ok((_, timestamp, roll, pitch, yaw)) => Ok(EulerAnglesMessage { timestamp, roll, pitch, yaw }),
            Err(_) => Err(DecodeError::UnableToParseAsciiMessage),
        }
    }

    fn parse_binary(message: &[u8]) -> Result<Self, DecodeError> {
        #[repr(C, packed)]
        struct BinaryMessage {
            id: u8,
            timestamp: u64,
            roll: f32,
            pitch: f32,
            yaw: f32,
            termination: u8,
        }

        if message.len() != size_of::<BinaryMessage>() {
            return Err(DecodeError::InvalidBinaryMessageLength);
        }

        let binary_message = unsafe {
            let ref binary_message = *(message.as_ptr() as *const BinaryMessage);
            binary_message
        };

        Ok(EulerAnglesMessage { timestamp: binary_message.timestamp, roll: binary_message.roll, pitch: binary_message.pitch, yaw: binary_message.yaw })
    }

    fn get_csv_file_name(&self) -> &'static str {
        "EulerAngles.csv"
    }

    fn get_csv_headings(&self) -> &'static str {
        "Timestamp (us),Roll (deg),Pitch (deg),Yaw (deg)\n"
    }

    fn to_csv_row(&self) -> String {
        format!("{},{:.6},{:.6},{:.6}\n", self.timestamp, self.roll, self.pitch, self.yaw)
    }

    fn to_ascii(&self) -> String {
        format!("{},{},{:.4},{:.4},{:.4}\r\n", Self::get_ascii_id() as char, self.timestamp, self.roll, self.pitch, self.yaw)
    }
}

impl fmt::Display for EulerAnglesMessage {
    fn fmt(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
        write!(formatter, "{:>8} us {:>8.3} deg {:>8.3} deg {:>8.3} deg", self.timestamp, self.roll, self.pitch, self.yaw)
    }
}
