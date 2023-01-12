#include "header.h"


using namespace std;

// bubble sort
vector< pair<double, int> > bubbleSort(vector< pair<double, int> > v, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1 - i; j++) {
      if (v[j].first > v[j + 1].first) {    
        std::swap(v[j], v[j + 1]); }
    }
  }
  return v;
}

// Find k nearest neighbors of point sample
int KNN(vector< vector<double> > x_train, vector<int> y_train, vector<double> sample, int k, string func, int labels_number) {

    vector< pair<double, int> > distances;
    int vec_size = x_train.size();
  
    // Calculate distances between point sample and all x_train in x_train
    for (int i = 0; i < x_train.size(); i++) {
        double distance = 0;
        if(func == "AUC") { distance = euclidian_distance_function(sample, x_train[i]); }
        if(func == "MAN") { distance = manheten_distance_function(sample, x_train[i]); }
        if(func == "CHB") { distance = chebyshev_distance_function(sample, x_train[i]); }
        if(func == "CAN") { distance = canberra_distance_function(sample, x_train[i]); }
        if(func == "MIN") { distance = minkowski_distance_function(sample, x_train[i]); }
        distances.push_back(make_pair(distance, i));
    }
    
    int size = x_train.size();
    vector< pair<double, int> > sorted = {};
    sorted = bubbleSort(distances, size);

    int monim[labels_number];
    vector<int> neighbors = {};

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
