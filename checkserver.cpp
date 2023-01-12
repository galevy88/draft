class SocketIO
{
    int socket_;

    public:
        SocketIO(int socket) : socket_(socket) {}

        std::string Read() {
            char buffer[1024] = { 0 };
            int bytes_received = recv(socket_, buffer, 1024, 0);
            if (bytes_received <= 0) { close(socket_); return ""; }
            return std::string(buffer, bytes_received);
        }
        
        void Write(const std::string &message) {
            send(socket_, message.c_str(), message.size(), 0);
        }
};
