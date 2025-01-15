#pragma once
#include <boost/asio.hpp>
#include <boost/
class server
{
public:
    // we need an io_context and a port where we listen to
    server(boost::asio::io_context& io_context, short port)
    : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)) {
        // now we call do_accept() where we wait for clients
        do_accept();
    }
private:
    void do_accept() {
        // this is an async accept which means the lambda function is
        // executed, when a client connects
        m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                // let's see where we created our session
                std::cout << "creating session on: "
                    << socket.remote_endpoint().address().to_string()
                    << ":" << socket.remote_endpoint().port() << '\n';
                // create a session where we immediately call the run function
                // note: the socket is passed to the lambda here
                std::make_shared<session>(std::move(socket))->run();
            } else {
                std::cout << "error: " << ec.message() << std::endl;
            }
            // since we want multiple clients to connnect, wait for the next one by calling do_accept()
            do_accept();
        });
    }
private:
    tcp::acceptor m_acceptor;
};