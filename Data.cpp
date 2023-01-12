#include "header.h"
#include "Data.h"

using namespace std;
// parser data
vector<double> Data::parser(string string_Vector, int stop_idx) {
    vector<double> Vector;
    string current;

    for(int i = 0; i <= stop_idx; i++)
    {
        if(string_Vector[i] == ',' || string_Vector[i] == '\0') 
        {
            try { Vector.push_back(stod(current)); current = ""; } 
            catch (...) { cout << "Invalid Input - Please Refer To README.md File And Try Again :)"; exit(0); }
        }
        else { current += string_Vector[i]; }
    }
    return Vector;
}

// rvrs string
string Data::reverse(string str) {
    int i = str.size() - 1;
    string true_label;
    for(i; i > 0; i--) { true_label += str[i]; }
    return true_label;
    }

//given label string return int
int Data::get_label_number(string label) {
    
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

// create split of str by ","
void Data::create_split(string line, vector<double>& vec, int& label_num) {
    if(line != "") {
        int line_length = line.size(); 
        int i = line_length;
        string label = "";
        int idx_of_split;
        for(i; i > 0; i--) {
            if(line[i] == ',') { idx_of_split = i; break; }
            else{ label += line[i]; }
        }
        string r = reverse(label);
        label_num = get_label_number(r);
        vec = parser(line, idx_of_split);
    }
}

// getters
vector<vector<double>> Data::get_x_train() { return this->x_train; }
vector<int> Data::get_y_train() { return this->y_train; }


// generate data from csv file
// void Data::generate_data() {
//     ifstream inputFile; inputFile.open("datasets/" + this->path);
//     if (!inputFile.good()) { std::cerr << "Error: unable to open file " << this->path << std::endl << " Probably check if you are using Win or Linux"; return; }
//     string line = "";
//     vector<double> current_vec;
//     int label;
//     while(getline(inputFile, line)) {
//         create_split(line , current_vec, label);
//         line = ""; 
//         this->x_train.push_back(current_vec);
//         this->y_train.push_back(label);
//     } 
// }

void Data::generate_data(const std::string& data) {
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


// Ctor
Data::Data(const string path) {
    this->path = path;
    this->x_train;
    this->y_train;
}

