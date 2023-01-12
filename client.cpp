#include "header.h"

bool is_ip(const char* str, char *& parsed_ip) {
  parsed_ip = new char[32];

  std::string octets[4];
  int octet_index = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '.') {
      octet_index++;
      continue;
    }
    octets[octet_index] += str[i];
  }

  for (int i = 0; i < 4; i++) {
    int octet;
    try { octet = std::stoi(octets[i]); }
    catch (...) { return false; }
    if (octet < 0 || octet > 255) return false;
  }

  char buffer1[32];
  std::sprintf(buffer1, "%d", std::stoi(octets[0]));
  char buffer2[32];
  std::sprintf(buffer2, "%d", std::stoi(octets[1]));
  char buffer3[32];
  std::sprintf(buffer3, "%d", std::stoi(octets[2]));
  char buffer4[32];
  std::sprintf(buffer4, "%d", std::stoi(octets[3]));
  std::strcpy(parsed_ip, buffer1);
  std::strcat(parsed_ip, ".");
  std::strcat(parsed_ip, buffer2);
  std::strcat(parsed_ip, ".");
  std::strcat(parsed_ip, buffer3);
  std::strcat(parsed_ip, ".");
  std::strcat(parsed_ip, buffer4);

  return true;
}



bool is_port(int p) {
  if (p < 0 || p > 65535) return false;
  if (p < 1024) return false;

  return true;
}


int client_request(char * ip, int port) {
while (true) {
    char buffer[1024];

    std::string message;
    std::getline(std::cin, message);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { std::cerr << "Error creating socket" << std::endl; return 1; }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);
    if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) { std::cerr << "Error connecting to server" << std::endl; return 1; }

    send(sockfd, message.c_str(), message.length(), 0);
    
    int bytes_received = recv(sockfd, buffer, 1024, 0);
    if (bytes_received < 0) { std::cerr << "Error receiving message" << std::endl; return 1; }

    // Print the received message
    std::cout << buffer << std::endl;
    if (message == "-1") { return -1; }
    // Close the socket
    close(sockfd);
    memset(buffer, 0, sizeof(buffer));
    
  }
  return 0;
}
int main(int argc, char* argv[]) {
  char * ip = argv[1];
  int port = atoi(argv[2]);
  char * parsed_ip;
  if(!is_ip(ip, parsed_ip)) { std::cout << "Invalid Input"; exit(0); }
  if(!is_port(port)) { std::cout << "Invalid Input"; exit(0); }

  client_request(parsed_ip, port);
  return 0;
}