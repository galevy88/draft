#include "header.h"
using namespace std;


//A function that calculate the distance between two vectors by using the euclidean distance algorithm:
double euclidian_distance_function(vector<double> vec1, vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        sum += pow(vec1[i]-vec2[i], 2);
    }
    return sqrt(sum);
}

//A function that calculate the distance between two vectors by using the manheten distance algorithm:
double manheten_distance_function(vector<double> vec1, vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        sum += abs(vec1[i]-vec2[i]);
    }
    return sum ;
}

//A function that calculate the distance between two vectors by using the chebyshev distance algorithm:
double chebyshev_distance_function(vector<double> vec1, vector<double> vec2) {
    double max = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double z = abs(vec1[i]-vec2[i]);
        if(z > max){ max = z;}
    }
    return max;
}

//A function that calculate the distance between two vectors by using the canberra distance algorithm:
double canberra_distance_function(vector<double> vec1, vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double nome = abs(vec1[i]-vec2[i]);
        double denome = abs(vec1[i]) + abs(vec2[i]);
        sum += nome / denome;
    }
    return sum;
}
//A function that calculate the distance between two vectors by using the minkowski distance algorithm:
double minkowski_distance_function(vector<double> vec1, vector<double> vec2) {
    double sum = 0.0;
    for(int i = 0; i < vec1.size(); i++) {
        double z = abs(vec1[i]-vec2[i]);
        sum += pow(z, 2);
    }
    return pow(sum, 0.5);
}
