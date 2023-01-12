#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <list>
#include <functional>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <cstring>
#include <thread>
#include <mutex>
#include <tuple>
#include <queue>
#include <condition_variable>

// KNN moudle functions
std::vector< std::pair<double, int> > bubbleSort(std::vector< std::pair<double, int> > v, int size);
int KNN(std::vector< std::vector<double> > x_train, std::vector<int> y_train, std::vector<double> sample, int k, std::string func, int labels_number);

// Calculator moudle functions
double euclidian_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double manheten_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double chebyshev_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double canberra_distance_function(std::vector<double> vec1, std::vector<double> vec2);
double minkowski_distance_function(std::vector<double> vec1, std::vector<double> vec2);

// main moudle functions
bool check_size(int size, std::string csv_type);
bool check_args(int size, std::string csv_type, std::string dist_func);
std::string fetch_path(std::string input);
//std::vector<double> parser(std::string string_Vector);
std::string get_label_classify(int label);
void print_vec(std::vector<std::vector<double> > x_train);
int get_labels_number(std::string csv_type);
std::string handle_process(int k, std::string csv_type, std::string distance_function, std::string vec);

// client moudle functions
bool is_ip(const char* str);
bool is_port(int p);
int client_request(char* ip, int port);

// server moudle functions
bool is_port(int p);
void check_csv_arg(std::string csv_type);
std::string normalize_csv_input(std::string csv);
bool extract_regions(const std::string& str, std::string& numbers, std::string& distance_function, int& integer);
int server_response();
