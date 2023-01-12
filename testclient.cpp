// #include <iostream>
// #include <unistd.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <string.h>
#include "header.h"
#include "SocketIO.cpp"
#include "CLI.cpp"


const int PORT = 9000;

int main() {
  // Create a socket
  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Set up the server address and port
  sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
  server_address.sin_port = htons(PORT);

  // Connect to the server
  if (connect(client_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }
  
  SocketIO socketio(client_fd);
  // Send data to the server and receive it back
  while(true) {

  std::string read = socketio.Read();
  std::cout << read << std::endl;
  std::string response;
  std::getline(std::cin, response);
  socketio.Write(response);
  if (response == "-1") { close(client_fd); return -1; }


  }
  // Close the socket

  return 0;
}
