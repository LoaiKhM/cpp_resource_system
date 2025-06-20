#include <asio.hpp>
#include <iostream>
#include <array>
using asio::ip::tcp;

int main() {
    asio::io_context io;
    tcp::socket socket(io);

    try {
        socket.connect(tcp::endpoint(asio::ip::make_address("127.0.0.1"), 1234));
        std::cout << "Connected!\n";

        std::string msg = "Hello server!\n";
        socket.write_some(asio::buffer(msg));

        std::array<char, 1024> buf;
        size_t len = socket.read_some(asio::buffer(buf));
        std::cout << "Server: " << std::string(buf.data(), len);

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
