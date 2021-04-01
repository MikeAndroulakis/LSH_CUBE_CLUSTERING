#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef WRITING_H
#define WRITING_H

void Writing_to_the_output_file(string output_file,int query,vector <int> nearest_neighbors,vector <int> best_distances,vector <int> true_best_distances,vector <int>  R_neighbors,double time_of_Algorithm,double timeTRUE,int N,string algorithm);

#endif
