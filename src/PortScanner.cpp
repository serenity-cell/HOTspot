#include "PortScanner.hpp"
#include <boost/asio/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/udp.hpp>
#include <iostream>
#include <iomanip>
#include <memory>
#include <unordered_map>
#include <ostream>

 void PortScanner::startScan(std::string ip, int start_port, int end_port) {
    // the engine
    boost::asio::io_context io;

    // variables for the async scan; timer limit and currrent amount of 
    int in_flight = 0;
    
    for (; start_port < end_port; start_port++) {
        portScan(ip, start_port, io);
        in_flight++;

        if (in_flight == 100){ 
            io.run();
            io.restart();

            in_flight = 0;
        }
    }
    io.run();

 }

void PortScanner::portScan(std::string ip, int port, boost::asio::io_context &io) {

    static const std::unordered_map<int, std::string> portServices = {
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

    // variables to connect to tcp socket 
    boost::asio::ip::tcp::endpoint endPointTcp (boost::asio::ip::make_address(ip), port);
    auto pTcpSocket = std::make_shared<boost::asio::ip::tcp::socket>(io);

    auto pTimer = std::make_shared<boost::asio::steady_timer> (io, std::chrono::seconds(2));

    // callback
    std::function<void(const boost::system::error_code& error)> callback = [this, port, service, pTcpSocket, endPointTcp, pTimer] 
    (const boost::system::error_code& error) {
        
        // checks the ports
        if (error.value() == 0) {
            
            // In your scan output:
            std::cout << std::left
            << std::setw(10) << port       
            << std::setw(10) << "OPEN"  
            << std::setw(10) << service 
            << std::endl;
        }
        else if (error == boost::asio::error::operation_aborted) {
            // In your scan output:
            std::cout << std::left
            << std::setw(10) << port       
            << std::setw(10) << "FILTERED"  
            << std::setw(10) << service 
            << std::endl;

        }
        else {
            this->closed_count ++;
            //std::cout << "Port " << port << " CLOSED — " << "\n";
        }
    };

    pTcpSocket->async_connect( endPointTcp, callback);

}