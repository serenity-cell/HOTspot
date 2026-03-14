#include "PortScanner.hpp"
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <ostream>
 // TODO: add all scanner logic here [DO NOT add user arguements here (cli responses)]

void PortScanner::scan(std::string ip, int port) {

    
    const std::unordered_map<int, std::string> portServices = {
        {21,    "FTP"},
        {22,    "SSH"},
        {23,    "Telnet"},
        {25,    "SMTP"},
        {53,    "DNS"},
        {67,    "DHCP"},
        {68,    "DHCP"},
        {80,    "HTTP"},
        {110,   "POP3"},
        {143,   "IMAP"},
        {443,   "HTTPS"},
        {445,   "SMB"},
        {3306,  "MySQL"},
        {3389,  "RDP"},
        {5900,  "VNC"},
        {8080,  "HTTP-Alt"},
        {8443,  "HTTPS-Alt"},
        {49152, "Dynamic"},
        {62078, "iPhone-Sync"}
    };

    auto it = portServices.find(port);
    std::string service = (it != portServices.end()) ? it->second : "Unknown";

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
          << std::setw(10) << port       
          << std::setw(10) << "OPEN"  
          << std::setw(10) << service 
          << std::endl;
    }
    catch (boost::system::system_error& e) {
        closed_count ++;
        //std::cout << "Port " << port << " CLOSED — " << e.what() << "\n";
    }
    tcpSocket.close();
}