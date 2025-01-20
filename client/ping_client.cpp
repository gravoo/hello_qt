#include "ping_client.hpp"
#include <iostream>
#include <thread>

Ping::Ping(boost::asio::io_service *ios) : ios(ios),
    endpoint(boost::asio::ip::tcp::v4(), 1990),
    socket(*ios),
    timer(*ios, std::chrono::seconds(5)),
    timer_expired(false)
{}
Ping::~Ping()
{
    timer_expired = false;
    timer.cancel();
    socket.close();
}
bool Ping::is_timer_expired()
{
    return timer_expired;
}
void Ping::start_timer()
{
    timer.cancel();
    timer.expires_after(std::chrono::seconds(5));
    auto self(shared_from_this());
    timer.async_wait([this, self](const boost::system::error_code& ec) {
    if (!ec) {
        timer_expired = true;
        std::cout << "Timer expired!" << std::endl;
    }
    });
}
void Ping::reset_timer()
{
    start_timer();
}
void Ping::ping_start()
{
    socket.connect(endpoint);
    start_timer();
    do_write();
}
void Ping::do_read()
{
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(buffer, data.size()),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                for(auto i:buffer)
                {
                    std::cout<<i<< " ";
                }
                std::cout<<"\n";
                reset_timer();
                do_write();
            }
        });
}

void Ping::do_write()
{
    auto self(shared_from_this());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boost::asio::async_write(socket, boost::asio::buffer(data, data.size()),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                do_read();
            }
        });
}