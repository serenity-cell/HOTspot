#include "PortScanner.hpp"
#include <boost/asio/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/udp.hpp>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <unordered_map>
#include <ostream>
#include <thread>

void PortScanner::extracted(int &aggressive, int &batch_quantity, int &batch_timer) {

    switch (aggressive) {
        case 0: 
        batch_quantity = 4;
        batch_timer = 2000;
        break;

        case 1: 
        batch_quantity = 6;
        batch_timer = 1500;
        break;

        case 2:
        batch_quantity = 20;
        batch_timer = 1000;
        break;

        case 3: 
        batch_quantity = 50;
        batch_timer = 700;
        break;

        case 4:
        batch_quantity = 80;
        batch_timer = 400;
        break;

        case 5:
        batch_quantity = 150;
        batch_timer = 100;
        break;

        default:
        // defaults to the middle ground
        batch_quantity = 50;
        batch_timer =  700;
        break;
      
    }
}

void PortScanner::startScan(std::string ip, int start_port, int end_port, int aggressive) {

    // the engine
    boost::asio::io_context io;

    // variables for the async scan; timer limit and currrent amount of
    int in_flight = 0;

    // checks the aggressivity
    int batch_quantity;
    int batch_sleep;

    extracted(aggressive, batch_quantity, batch_sleep);

    for (; start_port <= end_port; start_port++) {
        portScan(ip, start_port, io);
        in_flight++;

        if (in_flight == batch_quantity) {
            // runs the engine in batches
            io.run();
            io.restart();
            std::this_thread::sleep_for(std::chrono::milliseconds(batch_sleep));
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
        {631,   "CUPS"},
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

    // the timer to check for filtered ports
    auto pTimer = std::make_shared<boost::asio::steady_timer> (io);
    pTimer->expires_after(std::chrono::seconds(2));

    // timer callback function for filtered port checking
    std::function<void (const boost::system::error_code& error)> TimerCallback = [this, port, service, pTimer, pTcpSocket] 
    (const boost::system::error_code& error) {

        if (error.value() == 0) { 
            pTcpSocket->cancel();
            // In your scan output:
            std::cout << std::left
            << std::setw(10) << port       
            << std::setw(19) << "\033[33mFILTERED\033[0m"
            << std::setw(10) << service 
            << std::endl;
        }
        else if (error == boost::asio::error::operation_aborted) {
            return;
        }
        else {
            return;
        }

    };

    // connection callback
    std::function<void(const boost::system::error_code& error)> callback = [this, port, service, pTcpSocket, pTimer] 
    (const boost::system::error_code& error) {
         pTimer->cancel();
        
        // checks the ports
        if (error.value() == 0) {
            
            // In your scan output:
            std::cout << std::left
            << std::setw(10) << port       
            << std::setw(19) << "\033[32mOPEN\033[0m"
            << std::setw(10) << service 
            << std::endl;
        }
        else if (error == boost::asio::error::operation_aborted) {
            return;
        }
        else {
            this->closed_count ++;
            // std::cout << "Port " << port << " CLOSED — " << "\n";
        }
    };

    pTcpSocket->async_connect( endPointTcp, callback);
    pTimer->async_wait(TimerCallback);

}