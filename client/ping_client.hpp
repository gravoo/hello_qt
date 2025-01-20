#pragma once
#include <memory>
#include <array>
#include <boost/asio.hpp>

class Ping : public std::enable_shared_from_this<Ping>
{
public:
    Ping(boost::asio::io_service *ios);
    ~Ping();
    void ping_start();
    bool is_timer_expired();
private:
    void start_timer();
    void reset_timer();
    void do_read();
    void do_write();
    std::array<char, 4> data = {'p', 'i', 'n', 'g'};
    std::array<char, 4> buffer;
    boost::asio::io_service *ios;
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::ip::tcp::socket socket;
    boost::asio::steady_timer timer;
    bool timer_expired;
};