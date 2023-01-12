#include "SocketIO.h"
#include <sys/socket.h>
#include <unistd.h>

SocketIO::SocketIO(int socket) : socket_(socket) {}

std::string SocketIO::Read() {
    char buffer[1024] = { 0 };
    int bytes_received = recv(socket_, buffer, 1024, 0);
    if (bytes_received <= 0) { close(socket_); return ""; }
    return std::string(buffer, bytes_received);
}

void SocketIO::Write(const std::string &message) {
    std::cout << "HERE555";
    send(socket_, message.c_str(), message.size(), 0);
}
