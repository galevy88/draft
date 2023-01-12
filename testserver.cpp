#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//#include "CLI.cpp"

const int PORT = 9000;
const int BACKLOG = 10;
//std::mutex g_data_mutex;

void handle_client(int client_fd) {
  // CLI cli(client_fd);
  // cli.start(client_fd);
  std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    SocketIO socketio(client_fd);
    while (true) {
        std::string menu = generate_welcome_msg(commands);
        socketio.Write(menu);

        std::string choice = socketio.Read();
        analysis_choice(commands, choice, socketio);
        std::lock_guard<std::mutex> lock(g_data_mutex);
        }
        close(client_fd);
}


int main() {

    // Create a socket
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address and port
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address and port
  if (bind(server_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error binding socket" << std::endl;
    return 1;
  }

  // Listen for incoming connections
  if (listen(server_fd, BACKLOG) < 0) {
    std::cerr << "Error listening for connections" << std::endl;
    return 1;
  }

  std::vector<std::thread> client_threads;

  while (true) {  
  sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_address_len);
  if (client_fd < 0) { std::cerr << "Error accepting connection" << std::endl; }
  std::cout << "Accepted connection from " << inet_ntoa(client_address.sin_addr) << std::endl;
  client_threads.emplace_back(handle_client, client_fd);
  }

//   for (auto& thread : client_threads) {
//     std::cout << "\nThread ID: " << thread.get_id() << std::endl;
//     thread.join();
//   }

  close(server_fd);
  return 0;
}
