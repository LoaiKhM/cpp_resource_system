#include <asio.hpp>
#include <json.hpp>
#include <iostream>
#include <array>
using asio::ip::tcp;
using json = nlohmann::json;
int ID = 1;
int main() {
    asio::io_context io;
    tcp::socket socket(io);
    try {
        socket.connect(tcp::endpoint(asio::ip::make_address("127.0.0.1"), 1234));
        json DATA;
        DATA["ID"] = ID;
        DATA["SEC"] = 40;
        DATA["RES"] = {1,4,12,16,2000,100}; 
        std::cout << "Connected!\n";
        socket.write_some(asio::buffer(DATA.dump()));
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
