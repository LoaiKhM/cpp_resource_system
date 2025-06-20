#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>
#include <array>
#include <memory>
#include <unordered_map>
#include <vector>

unordered_map<vector<vector<int>>> timeline;
using asio::ip::tcp;

void handle_client(std::shared_ptr<tcp::socket> socket){
    auto buf = std::make_shared<std::array<char, 1024>>();
    socket->async_read_some(asio::buffer(*buf),
            [socket, buffer](std::error_code ec, std::size_t _read){
        if(!ec){

        }
    });
}

int main(){

    return 0;
}
