#ifndef PORTSCANNER_HPP
#define PORTSCANNER_HPP

// libraries 
#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>
class PortScanner { 
    public:
    void scan(std::string ip, int port);
    int closed_count = 0;
    
};
#endif