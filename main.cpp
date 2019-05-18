#include <iostream>
#include "boost/asio.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/asio/io_service.hpp"

int main(int argc, char* argv[]) {
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4());
    return 0;
}