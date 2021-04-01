#ifndef CALCULATE_DISTANCES_H
#define CALCULATE_DISTANCES_H
#include <vector>
using namespace std;

int Manhattan_Distance(vector <int> x,vector <int> y);

void Calculate_The_R_Neighbors(vector <int> nearest_neighbors,vector <int> distances,vector <int>* R_neighbors,int R);

void find_the_true_distances(vector <vector <int> > input_vector,vector <int> query,vector <int>* true_best_distances,vector <int>* true_nearest_neighbors,int N);

int Compute_W(vector<vector <int> > input_vector,int dimensions);


#endif
