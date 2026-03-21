#ifndef PORTSCANNER_HPP
#define PORTSCANNER_HPP

// libraries 
#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/address_v4.hpp>

class PortScanner { 
    public:
      void intensity(int &aggressive, int &batch_quanity, int &batch_timer);
      void startScan(std::string ip, int start_port, int end_port, int agressive);
      void portScan(std::string ip, int port, boost::asio::io_context &io);
      int closed_count = 0;
    
};
#endif