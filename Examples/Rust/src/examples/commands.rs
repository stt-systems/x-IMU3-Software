use ximu3::connection::*;
use ximu3::connection_type::*;
use ximu3::port_scanner::*;
use crate::helpers;

pub fn run() {

    // Search for connection
    println!("Searching for connections");

    let devices = PortScanner::scan_filter(ConnectionType::Usb);

    if devices.is_empty() {
        println!("No USB connections available");
        return;
    }

    let device = devices.first().unwrap();

    println!("Found {} {}", device.device_name, device.serial_number);

    // Open connection
    let connection = Connection::new(&device.connection_info);

    if connection.open().is_err() {
        println!("Unable to open connection");
        return;
    }
    println!("Connection successful");

    // Define read/write setting commands
    let commands = vec![
        "{\"device_name\":null}", /* change null to a value to write setting */
        "{\"serial_number\":null}",
        "{\"firmware_version\":null}",
        "{\"bootloader_version\":null}",
        "{\"hardware_version\":null}",
        "{\"invalid_setting_key\":null}"];/* this command is deliberately invalid to demonstrate a failed command */

    // Send commands
    if helpers::ask_question("Use async implementation?") {
        connection.send_commands_async(commands, 2, 500, Box::new(|responses| {
            print_responses(responses);
        }));

        std::thread::sleep(std::time::Duration::from_secs(3));
    } else {
        print_responses(connection.send_commands(commands, 2, 500));
    }

    // Close connection
    connection.close();
}

fn print_responses(responses: Vec<String>) {
    println!("{} commands confirmed", responses.len());

    for response in responses {
        println!("{}", response);
    }
}
