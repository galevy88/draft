
#include "header.h"
#include "Command.cpp"
#include "SocketIO.cpp"
std::mutex g_data_mutex;


int check_valid_string(const std::string& str) {
  int num;
  try { num = std::stoi(str); }
  catch (...) { return false; }

  if (num >= 1 && num <= 5 || num==8) { return num; }
  else { return -1; }
}

void analysis_choice(std::vector<std::unique_ptr<Command>>& commands, std::string choice, SocketIO socketio) {
    int i = check_valid_string(choice); 
    if(i != -1){
    if (i == 1 ) { commands[i-1]->execute(socketio); }
    if (i == 2 ) { commands[i-1]->execute(socketio); }
    if (i == 3 ) { commands[i-1]->execute(socketio); }
    if (i == 4 ) { commands[i-1]->execute(socketio); }
    if (i == 5 ) { commands[i-1]->execute(socketio); }
    if (i == 8 ) { commands[i-1]->execute(socketio); }
    }
}

std::string generate_welcome_msg(std::vector<std::unique_ptr<Command>>& commands) {
std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
for (int i = 0; i < commands.size(); i++) { std::string option = std::to_string(i + 1) + ". " + commands[i]->getDescription() + "\n"; menu += option; }
return menu;
}

class CLI {

private:
  std::vector<std::unique_ptr<Command>> commands;
  

public:
   CLI(int socket_num) {
    commands.push_back(std::make_unique<UploadFileCommand>());
    commands.push_back(std::make_unique<AlgorithmSettingsCommand>());
    commands.push_back(std::make_unique<ClassifyDataCommand>());
    commands.push_back(std::make_unique<DisplayResultsCommand>());
    commands.push_back(std::make_unique<DownloadResultsCommand>());
    commands.push_back(std::make_unique<ExitCommand>());
  }


  // Start function
  void start(int client_fd) {
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
  };

