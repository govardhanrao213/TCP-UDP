#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

int main() {
  try {
    io_service io;
    serial_port serial(io,
                       "/dev/ttyUSB1"); // Update based on your STM32 port

    serial.set_option(serial_port_base::baud_rate(9600));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

    std::string line;
    char c;

    std::cout << "Listening to UART..." << std::endl;

    while (true) {
      read(serial, boost::asio::buffer(&c, 1)); // Fixed here
      if (c == '\n') {
        std::cout << "UART: " << line << std::endl;
        line.clear();
      } else {
        line += c;
      }
    }
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
