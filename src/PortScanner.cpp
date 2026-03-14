#include "PortScanner.hpp"
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>
#include <ostream>
 // TODO: add all scanner logic here [DO NOT add user arguements here (cli responses)]

void PortScanner::scan(std::string ip, int port) {
    // the main engine
    boost::asio::io_context io;

    // variables to connect to tcp socket 
    boost::asio::ip::tcp::endpoint endPointTcp (boost::asio::ip::make_address(ip), port);
    boost::asio::ip::tcp::socket tcpSocket (io);

    // variables to connect to a udp socket
    boost::asio::ip::udp::endpoint endPointUdp (boost::asio::ip::make_address(ip), port);
    boost::asio::ip::udp::socket udpSocket (io);

    try {
        tcpSocket.connect(endPointTcp);
        // In your scan output:
        std::cout << std::left
          << std::setw(10) << port        // port column, 10 chars wide
          << std::setw(10) << "OPEN"      // state column, 10 chars wide
          << std::endl;
    }
    catch (boost::system::system_error& e) {
        closed_count ++;
        //std::cout << "Port " << port << " CLOSED — " << e.what() << "\n";
    }
    tcpSocket.close();
}