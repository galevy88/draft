#include "header.h"

const int PORT = 12345;
const int BACKLOG = 10;
std::mutex client_threads_mutex;

//A function that calculate the distance between two vectors by using the euclidean distance algorithm:
double euclidian_distance_function(std::vector<double> vec1, std::vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        sum += pow(vec1[i]-vec2[i], 2);
    }
    return sqrt(sum);
}

//A function that calculate the distance between two vectors by using the manheten distance algorithm:
double manheten_distance_function(std::vector<double> vec1, std::vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        sum += abs(vec1[i]-vec2[i]);
    }
    return sum ;
}

//A function that calculate the distance between two vectors by using the chebyshev distance algorithm:
double chebyshev_distance_function(std::vector<double> vec1, std::vector<double> vec2) {
    double max = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double z = abs(vec1[i]-vec2[i]);
        if(z > max){ max = z;}
    }
    return max;
}

//A function that calculate the distance between two vectors by using the canberra distance algorithm:
double canberra_distance_function(std::vector<double> vec1, std::vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double nome = abs(vec1[i]-vec2[i]);
        double denome = abs(vec1[i]) + abs(vec2[i]);
        sum += nome / denome;
    }
    return sum;
}
//A function that calculate the distance between two vectors by using the minkowski distance algorithm:
double minkowski_distance_function(std::vector<double> vec1, std::vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double z = abs(vec1[i]-vec2[i]);
        sum += pow(z, 2);
    }
    return pow(sum, 0.5);
}


// bubble sort
std::vector< std::pair<double, int> > bubbleSort(std::vector< std::pair<double, int> > v, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1 - i; j++) {
      if (v[j].first > v[j + 1].first) {    
        std::swap(v[j], v[j + 1]); }
    }
  }
  return v;
}

// Find k nearest neighbors of point sample
int KNN(std::vector< std::vector<double> > x_train, std::vector<int> y_train, std::vector<double> sample, int k, std::string func, int labels_number) {

    std::vector< std::pair<double, int> > distances;
    int vec_size = x_train.size();
  
    // Calculate distances between point sample and all x_train in x_train
    for (int i = 0; i < x_train.size(); i++) {
        double distance = 0;
        if(func == "AUC") { distance = euclidian_distance_function(sample, x_train[i]); }
        if(func == "MAN") { distance = manheten_distance_function(sample, x_train[i]); }
        if(func == "CHB") { distance = chebyshev_distance_function(sample, x_train[i]); }
        if(func == "CAN") { distance = canberra_distance_function(sample, x_train[i]); }
        if(func == "MIN") { distance = minkowski_distance_function(sample, x_train[i]); }
        distances.push_back(std::make_pair(distance, i));
    }
    
    int size = x_train.size();
    std::vector< std::pair<double, int> > sorted = {};
    sorted = bubbleSort(distances, size);

    int monim[labels_number];
    std::vector<int> neighbors = {};

    for (int i = 0; i < k; i++) { neighbors.push_back(sorted[i].second); }
    for(int i = 0; i < labels_number; i++) { monim[i] = 0; }
    for (int i = 0; i < neighbors.size(); i++) {
        monim[y_train[neighbors[i]]]++; 
    }

    int imax = 0; int max = 0;
    for (int i = 0; i < labels_number; i++) {
        if (monim[i] > max) { max = monim[i]; imax = i; }
    }
      
    return imax;
}


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

// parser data
std::vector<double> parser(std::string string_Vector, int stop_idx) {
    std::vector<double> Vector;
    std::string current;

    for(int i = 0; i <= stop_idx; i++)
    {
        if(string_Vector[i] == ',' || string_Vector[i] == '\0') 
        {
            try { Vector.push_back(stod(current)); current = ""; } 
            catch (...) { std::cout << "Invalid Input - Please Refer To README.md File And Try Again :)"; exit(0); }
        }
        else { current += string_Vector[i]; }
    }
    return Vector;
}



std::vector<double> parse_test(const std::string &s) {
    
    std::vector<double> numbers;
    std::stringstream ss(s);
    std::string number;
    while (std::getline(ss, number, ',')) {
        numbers.push_back(std::stod(number));
    }
    return numbers;
}


std::vector<std::string> parse_sampels(const std::string &data) {
    std::vector<std::string> lines;
    std::stringstream ss(data);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    return lines;
}

std::string get_classification(int type, int subtype) {
    std::cout << type << " " << subtype << std::endl;
    if (type == 1) {
      if(subtype == 0) { return "Iris-setosa"; }
      if(subtype == 1) { return "Iris-versicolor"; }
      if(subtype == 2) { return "Iris-virginica"; }
    }

    if (type == 2) {
      if(subtype == 0) { return "red wine"; }
      if(subtype == 1) { return "white wine"; }
      if(subtype == 2) { return "Sparkling wine"; }
    }

    if (type == 3) {
      if(subtype == 0) { return "SEKER"; }
      if(subtype == 1) { return "BARBUNYA"; }
      if(subtype == 2) { return "BOMBAY"; }
      if(subtype == 3) { return "CALI"; }
      if(subtype == 4) { return "HOROZ"; }
      if(subtype == 5) { return "SIRA"; }
      if(subtype == 6) { return "DERMASON"; }
    }
    
    return "500";
}

class Command {
 public:
  virtual ~Command() = default;
  virtual void execute(SocketIO& socketIO) = 0;
  virtual std::string getDescription() const = 0;
};

class UploadFileCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {}

  void execute_csv(SocketIO& socketIO, std::tuple<std::string, std::string>& tuple_CLI) {
    std::string upload_train_msg = "Please upload your local train CSV file.";
    socketIO.Write(upload_train_msg);
    std::string csv_train = socketIO.Read();
    std::string upload_test_msg = "Please upload your local test CSV file.";
    socketIO.Write(upload_test_msg);
    std::string csv_test = socketIO.Read();
    //std::cout << csv_train << std::endl;
    tuple_CLI = std::tuple<std::string, std::string>(csv_train, csv_test);
  }
  std::string getDescription() const override {
    return "Upload an unclassified csv data file";
  }
};

class AlgorithmSettingsCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {}

 void execute_params(SocketIO& socketIO, std::tuple<std::string, std::string>& tuple_CLI) {
    std::string K = std::get<0>(tuple_CLI);
    std::string Mat = std::get<1>(tuple_CLI);
    std::string params_msg = "The current KNN parameters are: K = " + K + ", distance metric = " + Mat;
    socketIO.Write(params_msg);
    std::string params = socketIO.Read();
    std::string first, second;
    if(!params.empty()) { 
        std::istringstream iss(params);
        iss >> std::get<0>(tuple_CLI) >> std::get<1>(tuple_CLI);
        std::cout << "Pre" << params << "Suf" << std::endl;
        }
    else if (params == "") {std::cout << "Pre" << params << "Suf" << std::endl;}
    }
  

  std::string getDescription() const override {
    return "Algorithm settings";
  }
};

class ClassifyDataCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {
    std::cout << "Classifying data..." << std::endl;
  }
    
    void execute_classify(SocketIO& socketIO, std::vector<std::vector<double> >& x_train, std::vector<int>& y_train, std::string& sampels_str, std::string& K, std::string& metric, int number, int type, std::string& final_results, bool& has_final_results) {
        std::vector<std::string> sampels = parse_sampels(sampels_str);
        int k;
        std::string result;
        int i = 1;
        if (K != "None" && sampels_str != "None") { 
          k = std::stoi(K);
          for(const auto &s: sampels) {
            std::cout << "HERE" << std::endl;
            std::cout << s << std::endl;
            std::cout << "number" << number << std::endl;
            std::cout << "type" << type << std::endl;
            std::vector<double> vec = parse_test(s);
            int imax = KNN(x_train, y_train, vec, k, metric, number);
            result +=std::to_string(i) + " " + get_classification(type, imax) + "\n";
            i++;
          }
          has_final_results = true;
        }
        else {socketIO.Write("\nK or data Invalid\n");}
        result += "Done.\n";
        std::cout << result << std::endl;
        final_results = result;
    }

  std::string getDescription() const override {
    return "Classify data";
  }
};

class DisplayResultsCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {
    std::cout << "Displaying results..." << std::endl;
  }

    void execute_display(SocketIO& socketIO, std::string& final_results) {
      socketIO.Write(final_results);
    }

  std::string getDescription() const override {
    return "Display results";
  }
};

class DownloadResultsCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {
    std::cout << "Downloading results..." << std::endl;
  }

  void execute_download(SocketIO& socketIO, const std::string final_results, bool& has_final_results) {
      std::string packet = "Download" + final_results;
      if(has_final_results) { socketIO.Write(packet); }
      else  {socketIO.Write("No final results yet."); }
  }
  std::string getDescription() const override {
    return "Download results";
  }
};

class ExitCommand : public Command {
 public:
  void execute(SocketIO& socketIO) override {
    std::cout << "Exiting..." << std::endl;
  }
  std::string getDescription() const override {
    return "Exit";
  }
};

std::mutex g_data_mutex;


int check_valid_string(const std::string& str) {
  int num;
  try { num = std::stoi(str); }
  catch (...) { return false; }

  if (num >= 1 && num <= 5) { return num; }
  else if (num == 8) { return 8; }
  else { return -1; }
}

int get_labels_number(std::string csv_type) {
    if(csv_type == "iris_classified.csv")  { return 3; }
    if(csv_type == "wine_classified.csv") { return 3; }
    if(csv_type == "beans_classified.csv") { return 6; }
    return -1;
}



//given label string return int
int get_label_number(std::string label) {
    
    if(label == "Iris-setosa") { return 0; }
    if(label == "Iris-versicolor") { return 1; }
    if(label == "Iris-virginica") { return 2; }

    if(label == "red wine") { return 0; }
    if(label == "white wine") { return 1; }
    if(label == "Sparkling wine") { return 2; }

    if(label == "SEKER") { return 0; }
    if(label == "BARBUNYA") { return 1; }
    if(label == "BOMBAY") { return 2; }
    if(label == "CALI") { return 3; }
    if(label == "HOROZ") { return 4; }
    if(label == "SIRA") { return 5; }
    if(label == "DERMASON") { return 6; }
    
    return -1;
}

std::string reverse(std::string str) {
    int i = str.size() - 1;
    std::string true_label;
    for(i; i > 0; i--) { true_label += str[i]; }
    return true_label;
    }



void create_split(std::string line, std::vector<double>& vec, int& label_num) {
    if(line != "") {
        int line_length = line.size(); 
        int i = line_length;
        std::string label = "";
        int idx_of_split;
        for(i; i > 0; i--) {
            if(line[i] == ',') { idx_of_split = i; break; }
            else{ label += line[i]; }
        }
        std::string r = reverse(label);
        label_num = get_label_number(r);
        vec = parser(line, idx_of_split);
    }
}
std::string generate_welcome_msg(std::vector<std::unique_ptr<Command>>& commands) {
std::string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n 1. Upload an unclassified csv data file\n 2. Algorithm settings\n 3. Classify data\n 4. Display results\n 5. Download results\n 8. Exit";
return menu;
}


class CLI {

private:
  std::vector<std::unique_ptr <Command> > commands;
  std::tuple<std::string, std::string> tuple_csv_CLI = {"None", "None"};
  std::tuple<std::string, std::string> tuple_params_CLI = {"None", "None"};;
  std::vector<std::vector<double> > x_train;
  std::vector<int> y_train;
  int type;
  std::string final_results;
  bool has_final_results = false;

public:
   CLI() {
    commands.push_back(std::make_unique<UploadFileCommand>());
    commands.push_back(std::make_unique<AlgorithmSettingsCommand>());
    commands.push_back(std::make_unique<ClassifyDataCommand>());
    commands.push_back(std::make_unique<DisplayResultsCommand>());
    commands.push_back(std::make_unique<DownloadResultsCommand>());
    commands.push_back(std::make_unique<ExitCommand>());
  }

    void generate_data(const std::string& data) {
    std::stringstream inputStream(data);
    std::string line;
    std::vector<double> current_vec;
    int label;
    while(std::getline(inputStream, line)) {
        create_split(line , current_vec, label);
        line = ""; 
        this->x_train.push_back(current_vec);
        this->y_train.push_back(label);
    } 
}

int get_type(const std::string &s) {
  std::cout << "string string: " << s << std::endl; 
    if (s.find("Iris-setosa") != std::string::npos) {
        return 1;
    } else if (s.find("white wine") != std::string::npos) {
        return 2;
    } else if (s.find("SEKER") != std::string::npos) {
        return 3;
    } else {
        return -1;
    }
}

int get_type_amount(int type) {
  if (this->type == 1) {return 3;}
  if (this->type == 2) {return 3;}
  if (this->type == 3) {return 6;}
  return -1;
}

std::vector<std::vector<double>> get_x_train() { return this->x_train; }
std::vector<int> get_y_train() { return this->y_train; }

  void analysis_choice(std::vector<std::unique_ptr<Command>>& commands, std::string choice, SocketIO& socketIO) {
    int i = check_valid_string(choice); 
    if(i != -1 && i != 8){
    if (i == 1 ) { 
        UploadFileCommand* upload_command = static_cast<UploadFileCommand*>(commands[i-1].get());
        upload_command->execute_csv(socketIO, this->tuple_csv_CLI);
         if (std::get<0>(this->tuple_csv_CLI) != "None" && std::get<1>(this->tuple_csv_CLI) != "None") { 
          this->generate_data(std::get<0>(this->tuple_csv_CLI));
          this->x_train = this->get_x_train();
          this->y_train = this->get_y_train();
          this->type = this->get_type(std::get<0>(this->tuple_csv_CLI));
          std::cout << this->type << " " << this->get_type_amount(this->type) << std::endl;
         }
         else {socketIO.Write("One of the files is not good\n");}
        }

    if (i == 2 ) { 
        AlgorithmSettingsCommand* algorithm_settings_command = static_cast<AlgorithmSettingsCommand*>(commands[i-1].get());
        algorithm_settings_command->execute_params(socketIO, this->tuple_params_CLI);
        }

    if (i == 3 ) { 
        ClassifyDataCommand* classify_command = static_cast<ClassifyDataCommand*>(commands[i-1].get());
        if (std::get<0>(this->tuple_csv_CLI) != "None" && std::get<1>(this->tuple_csv_CLI) != "None") {
          classify_command->execute_classify(socketIO, this->x_train, this->y_train, std::get<1>(this->tuple_csv_CLI), std::get<0>(this->tuple_params_CLI), std::get<1>(this->tuple_params_CLI), this->get_type_amount(this->type), this->type ,this->final_results, this->has_final_results); 
        }
        else {socketIO.Write("DataSets Not Good\n");}
        }

    if (i == 4 ) { 
        DisplayResultsCommand* display_command = static_cast<DisplayResultsCommand*>(commands[i-1].get());
        display_command->execute_display(socketIO, this->final_results);
     }
    if (i == 5 ) {
        DownloadResultsCommand* download_command = static_cast<DownloadResultsCommand*>(commands[i-1].get());
        download_command->execute_download(socketIO, this->final_results, this->has_final_results); 
        }
    }
    if (i == 8 ) { commands[5]->execute(socketIO); }
}

  // Start function
  void start(int client_socket) {
    
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
        SocketIO socketIO(client_socket);
        while (true) {
            std::string message = generate_welcome_msg(commands);
            socketIO.Write(message);
            std::string response = socketIO.Read();
            this->analysis_choice(commands, response, socketIO);
            // if (response == "") { close(client_socket); }
        }
        close(client_socket); 
    }
  };







void handle_client(int client_socket) {
    CLI cli;
    cli.start(client_socket);
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

  close(server_fd);
  return 0;
}
