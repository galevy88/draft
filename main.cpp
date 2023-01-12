#include "header.h"
#include "Data.h"

using namespace std;

// Check either the vectors are with the sae ssize or not
bool check_size(int size, string csv_type) {
    if(csv_type == "iris_classified.csv") { if( size != 4) { return false; } }
    if(csv_type == "wine_classified.csv") { if( size != 13) { return false; } }
    if(csv_type == "beans_classified.csv") { if( size != 16) { return false; } }
    return true;
}

bool check_args(int size, string csv_type, string dist_func) {
    if(size < 1 || size > 100) { return false; }
    if(csv_type != "beans_classified.csv" && csv_type != "iris_classified.csv" && csv_type != "wine_classified.csv") { return false; }
    if(dist_func != "AUC" && dist_func != "MAN" && dist_func != "CHB" && dist_func != "CAN" && dist_func != "MIN") { return false; }
    return true;
}

string fetch_path(string input) {
    string iris_str; string beans_str; string wine_str; string chosen;
    if(input == "iris_classified.csv") { iris_str = "iris/" + input; chosen = iris_str; }
    if(input == "wine_classified.csv") { wine_str = "wine/" + input; chosen = wine_str; }
    if(input == "beans_classified.csv") { beans_str = "beans/" + input; chosen = beans_str; }
    
    return chosen;
}

// Parsing the input which got as string into a vector with double type variabls
vector<double> parser(string string_Vector) {
    vector<double> Vector;
    string current;

    for(int i = 0; i <= string_Vector.length(); i++)
    {
        if(string_Vector[i] == ' ' || string_Vector[i] == '\0') 
        {
            try { Vector.push_back(stod(current)); current = ""; } 
            catch (...) { cout << "Invalid Input - Please Refer To README.md File And Try Again :)\nWe closed the program for you until you will read the read me file.\nPlease read the README.md file and run this program another time\n"; exit(0); }
        }
        else { current += string_Vector[i]; }
    }
    return Vector;
}
// get lbl str by lbl int
string get_label_classify(string csv_type, int label) {
    string s = "";
    if (csv_type == "iris_classified.csv") {
        if(label == 0) { s = "Iris-setosa"; return s; }
        if(label == 1) { s = "Iris-versicolor"; return s; }
        if(label == 2) { s = "Iris-virginica"; return s; }
    }

    if (csv_type == "wine_classified.csv") {
        if(label == 0) { s = "red wine"; return s; }
        if(label == 1) { s = "white wine"; return s; }
        if(label == 2) { s = "Sparkling wine"; return s; }
    }

    if (csv_type == "beans_classified.csv") {
        if(label == 0) { s = "SEKER"; return s; }
        if(label == 1) { s = "BARBUNYA"; return s; }
        if(label == 2) { s = "BOMBAY"; return s; }
        if(label == 3) { s = "CALI"; return s; }
        if(label == 4) { s = "HOROZ"; return s; }
        if(label == 5) { s = "SIRA"; return s; }
        if(label == 6) { s = "DERMASON"; return s; }
    }
    
    s = "Couldn't get an answer - 500 code";
    return s;
}

// print vector - depricated
void print_vec(vector<vector<double> > x_train) {
    for(int i =0; i < x_train.size(); i++) {
        for(int j =0; j < x_train[i].size(); j++) {
            cout << x_train[i][j] << " ";
        }
        cout << "\n";
    }
}

// get how much label exist for each dataset
int get_labels_number(string csv_type) {
    if(csv_type == "iris_classified.csv")  { return 3; }
    if(csv_type == "wine_classified.csv") { return 3; }
    if(csv_type == "beans_classified.csv") { return 6; }
    return -1;
}


string handle_process(int k, string csv_type, string distance_function, string vec_input) {

    string ret_str = "";
    if(!check_args(k, csv_type, distance_function)) { ret_str = "Invalid Input"; return ret_str;}

    if(vec_input == "-1") { exit(0); }
    vector<double> vec = parser(vec_input);    
    int vec_size = vec.size();
    if(!check_size(vec_size, csv_type)) { ret_str = "Invalid Input"; return ret_str;}
    


    string chosen = fetch_path(csv_type);
    Data d(chosen);
    d.generate_data();
    vector<vector<double> > x_train = d.get_x_train();
    vector<int> y_train = d.get_y_train();
    int labels_number = get_labels_number(csv_type);


    int imax = KNN(x_train, y_train, vec, k, distance_function, labels_number);
    string classification = get_label_classify(csv_type, imax);
    ret_str = "The classification is: " + classification;

    vec_input = "";
    return ret_str;
}
