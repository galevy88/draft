#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Data {
    private:
    string path;
    vector< vector<double> > x_train;
    vector<int> y_train;
    vector<double> parser(string string_Vector, int stop_idx);
    string reverse(string str);
    int get_label_number(string label);
    void create_split(string line, vector<double>& vec, int& label_num);
    
    public:
    Data(const string path);
    void generate_data(const std::string& data);
    vector<vector<double> > get_x_train();
    vector<int> get_y_train();
};