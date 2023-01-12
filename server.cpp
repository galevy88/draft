#include "header.h"

std::string csv;
int port;

bool is_port(int p) {
  if (p < 0 || p > 65535) return false;
  if (p < 1024) return false;

  return true;
}

void check_csv_arg(std::string csv_type) {
    if(csv_type != "beans_classified.csv" && csv_type != "iris_classified.csv" && csv_type != "wine_classified.csv" && csv_type != "beans/beans_classified.csv" && csv_type != "iris/iris_classified.csv" && csv_type != "wine/wine_classified.csv") { 
        std::cout << "Invalid Input - Please Refer To README.md File And Try Again :)"; exit(0); }
}

std::string normalize_csv_input(std::string csv) {
  std::string s = "";
  if (csv == "iris_classified.csv") { s = "iris_classified.csv"; return s;}
  if (csv == "wine_classified.csv") { s = "wine_classified.csv"; return s;}
  if (csv == "beans_classified.csv") { s = "beans_classified.csv"; return s;}
  if (csv == "iris/iris_classified.csv") { s = "iris_classified.csv"; return s;}
  if (csv == "wine/wine_classified.csv") { s = "wine_classified.csv"; return s;}
  if (csv == "beans/beans_classified.csv") { s = "beans_classified.csv"; return s;}
  return s;
}


bool extract_regions(const std::string& str, std::string& numbers, std::string& distance_function, int& integer) {

  std::stringstream stream(str);
  double number;

  while (stream >> number) { numbers += std::to_string(number) + " "; }
  stream.clear(); stream.seekg(0);

  std::string region;
  while (stream >> region) 
  {
    if (!std::isdigit(region[0]) && region[0] != '-') { distance_function = region; break; }
  }

  if (!(stream >> integer)) { return false; }
  if (numbers.empty() || distance_function.empty()) { return false; }

  numbers.pop_back();
  return true;
}

int server_response() {
// Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Bind the socket to a port
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);
  if (bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Error binding socket to port" << std::endl;
    return 1;
  }
  
  // Listen for incoming connections
  listen(sockfd, 5);
  while (true) {
    
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(sockfd, (sockaddr*)&client_addr, &client_addr_len);
    if (client_fd < 0) { std::cerr << "Error accepting connection" << std::endl; return 1; }
    
    
    char message[1024];
    int bytes_received = recv(client_fd, message, 1024, 0);
    if (bytes_received < 0) { std::cerr << "Error receiving message" << std::endl; return 1; }
    if (strcmp(message, "-1") == 0) { close(client_fd); }

    
    std::string vec; std::string distance_function; int k;
    if(!extract_regions(message, vec, distance_function, k)) {
      std::string classification_message = "Invalid Input";
      send(client_fd, classification_message.c_str(), classification_message.length(), 0);
      close(client_fd);
      memset(message, 0, sizeof(message));
    }
    
    else {
    std::string classification_message = handle_process(k, csv, distance_function, vec);
    send(client_fd, classification_message.c_str(), classification_message.length(), 0);
    close(client_fd);
    memset(message, 0, sizeof(message));
    }
  }

  // Close the server socket
  close(sockfd);
  return 0;
}

int main(int argc, char* argv[]) {
  std::string csv_input = argv[1];
  check_csv_arg(csv_input);
  csv = normalize_csv_input(csv_input);
  port = atoi(argv[2]);
  server_response();

}