#include "Quicksort.h"
#include <vector>

using namespace std;

int partition(vector<int> &best_distances,vector <int> &nearest_neighbors, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = best_distances[pivotIndex];
    int i = left, j = right;
    int temp,temp2;
    while(i <= j) {
        while(best_distances[i] < pivotValue) {
            i++;
        }
        while(best_distances[j] > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = best_distances[i];
            best_distances[i] = best_distances[j];
			best_distances[j] = temp;
			temp2=nearest_neighbors[i];
			nearest_neighbors[i]=nearest_neighbors[j];
			nearest_neighbors[j]=temp2;
            i++;
            j--;
        }
    }
    return i;
}


void quicksort(vector<int> &best_distances,vector<int> &nearest_neighbors, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(best_distances, nearest_neighbors,left, right);
        quicksort(best_distances, nearest_neighbors,left, pivotIndex - 1);
        quicksort(best_distances, nearest_neighbors,pivotIndex, right);
    }
}
