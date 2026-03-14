#include "PortScanner.hpp"
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/udp.hpp>
#include <iostream>
 // TODO: add all scanner logic here [DO NOT add user arguements here (cli responses)]

void PortScanner::scan(std::string ip, int port) {
    // the main engine
    boost::asio::io_context io;

    // variables to connect to tcp socket 
    boost::asio::ip::tcp::endpoint end_point (boost::asio::ip::make_address(ip), port);
    boost::asio::ip::tcp::socket tcpSocket (io);

    // variables to connect to a udp socket
    boost::asio::ip::udp::endpoint end_point_udp (boost::asio::ip::make_address(ip), port);
    boost::asio::ip::udp::socket udpSocket (io);

    try {
        tcpSocket.connect(end_point);
        std::cout << "Port " << port << " OPEN\n";
    }
    catch (boost::system::system_error& e) {
        closed_count ++;
        // std::cout << "Port " << port << " CLOSED — " << e.what() << "\n";
    }
    tcpSocket.close();
}