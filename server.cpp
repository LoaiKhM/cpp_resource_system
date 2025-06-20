#define ASIO_STANDALONE
#define DAY 86399
#include <asio.hpp>
#include <json.hpp>
#include <iostream>
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>
std::unordered_map<int, int> indexes;

std::vector<std::vector<std::vector<int>>> timeline(1, std::vector<std::vector<int>>(DAY,std::vector<int>{}));
using asio::ip::tcp;
using json = nlohmann::json;
void handle_client(std::shared_ptr<tcp::socket> socket){
    auto buf = std::make_shared<std::array<char, 1024>>();
    socket->async_read_some(asio::buffer(*buf),
            [socket, buf](std::error_code ec, std::size_t _read){
        if(!ec){
            std::string query(buf->data(), _read);
            json DATA = json::parse(query);
            int DEV_ID = DATA["ID"];
            int TIMESEC = DATA["SEC"];
            int INDEX = indexes[DEV_ID];
            std::vector<int> RES = DATA["RES"];
            timeline[INDEX][TIMESEC] = RES;
            std::cout << timeline[INDEX][TIMESEC][2];
        }
    });
}

int main(){
    indexes[1] = 0;
    asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1234));
    std::function<void()> do_accept;
    do_accept = [&](){
        auto socket = std::make_shared<tcp::socket>(io);
        acceptor.async_accept(*socket, [&, socket](std::error_code ec){
            if(!ec){
                std::cout << "New Connection:\n";
                handle_client(socket);
            }
            do_accept();
        });
    };
    do_accept();
    io.run();
    return 0;
}
