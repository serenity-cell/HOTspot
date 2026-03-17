#include "src/PortScanner.hpp"
#include <iostream>
#include <ostream>

void userOptions(int &arg_count, char **&arg_vector, std::string &ip_input, int &port_input) {
  for (int i = 1; i < arg_count; i++) {

    // grabs the ip address
    if (strcmp(arg_vector[i], "-ip") == 0) {
      ip_input = arg_vector[i + 1];
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


  std::cout << "scanning host: " << ip_input << "\n";
  std::cout << "PORT      STATE     SERVICE\n";
  std::cout << "------------------------------ \n";
  scanner.startScan(ip_input, 1, 65535);

  // once don scanning it also shows the total closed ports
  std::cout <<  " \n" << "NOT SHOWN: " << scanner.closed_count << " closed ports" << std::endl;
}