#include "src/PortScanner.hpp"
#include <iostream>

void userOptions(int &arg_count, char **&arg_vector, std::string &ip_input,
               int &port_input) {
  for (int i = 1; i < arg_count; i++) {

    // grabs the ip address
    if (strcmp(arg_vector[i], "-ip") == 0) {
      ip_input = arg_vector[i + 1];
      // std::cout << ip_input << " \n";
    }

    // grabs the port input
    if (strcmp(arg_vector[i], "-port") == 0) {
      port_input = std::stoi(arg_vector[i + 1]);
      // std::cout << port_input << " \n";
    }
  }
}

int main(int arg_count, char *arg_vector[]) {
  PortScanner scanner;
  std::string ip_input = " ";
  int port_input = 0 ;

  // the cli commands and available arguments
  userOptions(arg_count, arg_vector, ip_input, port_input);

  // outputs the necessary format when not inputting any ip address arguement
  if (ip_input.empty()) {
        std::cerr << "Usage: ./HOTspot -ip <address> -port <port>\n";
        return 1;
  } 
  else if (port_input == 0) {
    // runs both ip and port through the scanner
    for (int port = 1; port <= 4040; port++) {
      scanner.scan(ip_input, port);
    }
    // once don scanning it also shows the total closed ports
    std::cout <<  " \n" << "scan done " << scanner.closed_count << " total closed ports \n";
  }
  else if (port_input != 0 ) {
    // for when you want to check a specific port
    scanner.scan(ip_input, port_input);
  }
}