#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

const int PORT = 8000;
const int BACKLOG = 10;

std::mutex g_data_mutex;
int g_data = 0;

void handle_client(int client_fd) {
  // Read data from client and increment a global variable

  std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n 1. upload an unclassified csv data file\n 2. algorithm settings\n 3. classify data\n 4. display results\n 5. download results\n 8. exit\n";
  send(client_fd, menu.c_str(), menu.length(), 0);
  std::string temp = "I'm the server, you sent me: ";
  char buffer[1024];
  int bytes_received = recv(client_fd, buffer, 1024, 0);
  if (bytes_received <= 0) { std::cerr << "Error receiving data from client" << std::endl; }
  else if (bytes_received > 0) { std::lock_guard<std::mutex> lock(g_data_mutex); g_data += 1; }
  std::string final_msg = temp + buffer;
  send(client_fd, final_msg.c_str(), final_msg.length(), 0);
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

  std::cout << "Listening for connections on port " << PORT << "..." << std::endl;

  sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_address_len);
  if (client_fd < 0) { std::cerr << "Error accepting connection" << std::endl; }
  std::cout << "Accepted connection from " << inet_ntoa(client_address.sin_addr) << std::endl;
  std::thread client_thread(handle_client, client_fd);
  // Accept incoming connections and spawn a new thread for each client
  std::cout << "\nThread ID: " << client_thread.get_id() << std::endl;
  if (client_thread.joinable()) { std::cout << "Successfully created thread for client " << inet_ntoa(client_address.sin_addr) << std::endl;}
  else { std::cerr << "Error creating thread for client " << inet_ntoa(client_address.sin_addr) << std::endl; }
  while (true) {

    
  std::thread client_thread(handle_client, client_fd);

  
//     //client_thread.detach();
  }
  client_thread.detach();
  return 0;
}
