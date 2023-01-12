
#include "header.h"


const int PORT = 12345;

class SocketIO
{
    int socket_;

    public:
        SocketIO(int socket) : socket_(socket) {}
    std::string Read() {
        std::string message;
        int bytes_received = 0;
        int buffer_size = 4096;
        char * buffer = new char[buffer_size];
        while ((bytes_received = recv(socket_, buffer, buffer_size, 0)) > 0) {
            if(bytes_received == buffer_size) {
                buffer_size *= 2;
                char * new_buffer = new char[buffer_size];
                memcpy(new_buffer, buffer, buffer_size / 2);
                delete[] buffer;
                buffer = new_buffer;
            }else {
                break;
            }
        }
        message.append(buffer, bytes_received);
        delete[] buffer;
        if (bytes_received <= 0) { close(socket_); return ""; }
        return message;
    }

        void Write(const std::string &message) {
            send(socket_, message.c_str(), message.size(), 0);
        }
};


int analysis_message(const std::string& message) {
  if (message.find("Welcome to the KNN Classifier Server. Please choose an option:\n 1. Upload an unclassified csv data file\n 2. Algorithm settings\n 3. Classify data\n 4. Display results\n 5. Download results\n 8. Exit") != std::string::npos) { return 1; }
  if (message.find("Please upload your local train CSV file.") != std::string::npos) { return 2; }
  if (message.find("Please upload your local test CSV file.") != std::string::npos) { return 3; }
  if (message.find("The current KNN parameters") != std::string::npos) { return 4; }
  if (message.find("Download") != std::string::npos) { return 5; }
  return -1;
}


std::string upload_csv_file() {
    std::string path;
    std::getline(std::cin, path);

    std::ifstream file(path);

    if(file.good()) {     
    std::string line, file_contents;
    while (std::getline(file, line)) { file_contents += line + '\n'; }
    file.close(); return file_contents; }
    else { return  "None"; }
    
}

bool is_string_numeric(const std::string& str) {
    for (const char& c : str) {
        if (!std::isdigit(c)) { return false; } }
    return true;
}


int check_if_valid_input(const std::string& input) {

        if(input.empty()){ return 1;}
        
        std::istringstream iss(input);
        std::string first, second;
        if (iss >> first && iss >> second) {
        
            if (is_string_numeric(first)) {
        
                if (second == "AUC" || second == "MAN" || second == "CHB" || second == "MIN" || second == "KAN") {
                    std::string temp;
                    if (iss >> temp) { std::cout << "Invalid value for K and Invalid value for metric" << std::endl; }
                    return 1; // valid input, return the tuple
                } 
                else { std::cout << "Invalid value for K" << std::endl; return 0;} } 
                else { std::cout << "Invalid value for metric" << std::endl; return 0;} }
                else { std::cout << "Invalid value for K and Invalid value for metric" << std::endl; return 0; }
}

std::string get_params_input() {
    std::string input;
    std::getline(std::cin, input);
    int result = check_if_valid_input(input);
    while(result != 1) { int result = check_if_valid_input(input); std::getline(std::cin, input); }
    return input;
}

bool check_for_final_results(std::string& message, std::string& final_results) {
  if (message.find("Done.") != std::string::npos) { final_results = message; return true; }
  return false;
}

void download_results(std::string& final_results) {
  std::cout << "Please enter your download path" << std::endl;
  std::string path;
  std::getline(std::cin, path);
  std::ofstream file(path);
  file << final_results;
  file.close();
}

int main() {
  // Create a socket
  int socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ < 0) {
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
  if (connect(socket_, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }
  
SocketIO socket(socket_);
std::string final_results;
bool has_results = false;
std::string response;
while (true) {
    std::string message = socket.Read();
    std::cout << message << std::endl;

    int analysis = analysis_message(message);
    if (analysis == 1) { std::getline(std::cin, response); socket.Write(response); }
    if (analysis == 2) { std::string csv_train = upload_csv_file(); socket.Write(csv_train); }
    if (analysis == 3) { std::string csv_test = upload_csv_file(); socket.Write(csv_test); }
    if (analysis == 4) { std::string params = get_params_input(); socket.Write(params); }
    if (analysis == 5) { download_results(message); }
    
    if (response == "-1") { break; }
}


  // Close the socket
  close(socket_);
  return 0;
}
