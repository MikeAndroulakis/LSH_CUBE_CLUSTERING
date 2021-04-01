#include <limits>
#include <algorithm>
#include "Calculate_Distances.h"
#include "Quicksort.h"


using namespace std;

int Manhattan_Distance(vector <int> x, vector <int> y) {
    int dimensions = x.size();
    int distance = 0;
    for (int i = 0; i < dimensions; i++) {
        if (x[i] - y[i] >= 0) {
            distance += x[i] - y[i];
        } else {
            distance += y[i] - x[i];
        }
    }
    return distance;
}

void Calculate_The_R_Neighbors(vector <int> nearest_neighbors, vector <int> distances, vector <int>* R_neighbors, int R) {
    for (unsigned i = 0; i < nearest_neighbors.size(); i++) {
        if (distances[i] < R) {
            (*R_neighbors).push_back(nearest_neighbors[i]);
        }
    }
}

void find_the_true_distances(vector <vector <int> > input_vector, vector <int> query, vector <int>* true_best_distances, vector <int>* true_nearest_neighbors, int N) {
    for (unsigned pic = 0; pic < input_vector.size(); pic++) {
        int distance = Manhattan_Distance(query, input_vector[pic]);
        if (!count((*true_nearest_neighbors).begin(), (*true_nearest_neighbors).end(), pic)) {
            (*true_best_distances).push_back(distance);
            (*true_nearest_neighbors).push_back(pic);
        }
    }
    quicksort((*true_best_distances), (*true_nearest_neighbors), 0, (*true_best_distances).size() - 1);
}

int Compute_W(vector<vector <int> > input_vector, int dimensions) {
    int num_of_images = input_vector.size() / 100;
    int average_distance_of_nearest_neighbor = 0;
    int sample = num_of_images - 1;
    for (int i = 0; i < sample; i++) {
        int distance_from_best_neighbor = numeric_limits<int>::max();
        for (int j = (i + 1); j < num_of_images; j++) {
            int distance = Manhattan_Distance(input_vector[i], input_vector[j]);
            //cout<<"DISTANCE="<<distance<<"  ";
            //cout<<"DISTANCE="<<distance_from_best_neighbor<<"  ";
            if (distance < distance_from_best_neighbor) {
                distance_from_best_neighbor = distance;
            }

        }
        average_distance_of_nearest_neighbor += distance_from_best_neighbor;
    }
    return average_distance_of_nearest_neighbor / sample;
}



