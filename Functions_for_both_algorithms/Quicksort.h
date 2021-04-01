#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <vector>

using namespace std;

int partition(vector<int> &best_distances,vector <int> &nearest_neighbors, int left, int right);

void quicksort(vector<int> &best_distances,vector<int> &nearest_neighbors, int left, int right);

#endif
