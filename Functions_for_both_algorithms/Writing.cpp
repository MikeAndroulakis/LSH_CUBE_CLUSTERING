#include "Writing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void Writing_to_the_output_file(string output_file, int query, vector <int> nearest_neighbors, vector <int> best_distances, vector <int> true_best_distances, vector <int> R_neighbors, double time_of_Algorithm, double timeTRUE, int N, string algorithm) {
    if (nearest_neighbors.size() < (unsigned) N) {
        N = nearest_neighbors.size();
    }
    ofstream ofile;
    ofile.open(output_file, fstream::app);
    ofile << "Query: " << query + 1 << "\n";
    for (int i = 0; i < N; i++) {
        ofile << "Nearest neighbor-" << i + 1 << ": " << nearest_neighbors[i] + 1 << "\n";
        if (algorithm == "lsh") {
            ofile << "distanceLSH: " << best_distances[i] << "\n";
        } else if (algorithm == "cube") {
            ofile << "distanceCUBE: " << best_distances[i] << "\n";
        }
        ofile << "distanceTrue: " << true_best_distances[i] << "\n";
    }
    if (algorithm == "lsh") {
        ofile << "tLSH: ";
    } else if (algorithm == "cube") {
        ofile << "tCUBE: ";
    }
    ofile << fixed << time_of_Algorithm << setprecision(6) << " seconds\n";
    ofile << "tTrue: " << fixed << timeTRUE << setprecision(6) << " seconds\n";
    ofile << "R-near neighbors:\n";
    for (unsigned i = 0; i < R_neighbors.size(); i++) {
        ofile << R_neighbors[i] + 1 << "\n";
    }
    ofile << "\n";

    ofile.close();

}
