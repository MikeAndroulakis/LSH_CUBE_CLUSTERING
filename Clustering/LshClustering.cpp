#include "LshClustering.h"
#include <cmath>
#include <set>
#include <iostream>
#include <algorithm>   
#include <vector>
#include <climits>
#include "../Lsh/LSH.h"
#include "../Functions_for_both_algorithms/Modulos.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"

#define LSH_CLUSTERING_BUCKET_PARAMETER 8

using namespace std;

LshClustering::LshClustering(ImageCollection * imagecol, int C, int L, int k, int W) :
Clustering(imagecol, C), Num_of_Buckets(imagecol->size() / LSH_CLUSTERING_BUCKET_PARAMETER), M(pow(2, (int) (32 / k))), m(M / 4 - 5), L(L), k(k), W(W), dimensions(imagecol->rows * imagecol->columns) {
    // create hashtables
    cout << "Initializing LSH clustering ... " << endl;

    cout << "Calculate_the_Modulo_Exponents()" << endl;
    Calculate_the_Modulo_Exponents(&modulo_Exponents_of_m, m, M, dimensions);

    cout << "Hash_The_Train_File()" << endl;
    Hash_The_Train_File(&all_h_values_of_all_g, &g_hash, *imagecol, Num_of_Buckets, L, k, M, modulo_Exponents_of_m, W);

    cout << "Training finished \n";
}

LshClustering::~LshClustering() {
    // destroy hashtables
}

AssignmentDefinition * LshClustering::assignment(ImageCollection * centers) {
    AssignmentDefinition * def = new AssignmentDefinition();
    int C = centers->size();

    bool flagLeftovers = false;
    double R = 20000;
    vector<int> already_found;
    vector<int> already_found_points_centers; //ta kentra oswn exoun ksanavrethei
    vector<int> all_that_were_found;
    bool flag = false;
    bool newNeighbors = false;
    int images_count = collection->size();
    int minj, dist, dist2, dist3, cen,cen2;
    int min = INT_MAX;
    

    def->centers = centers;

    while (true) {
        newNeighbors = false;
        //arxikopoiw ton already_found
        already_found.clear(); //gia kathe loop tis R
        already_found_points_centers.clear();

        for (int j = 0; j < C; j++) { //gia kathe kentro vres geitonika
            set<int> R_neighbors;
            //vriskw tous neighbors se R
            Hash_The_Queries_And_Calculate_Neighbors_For_Clustering(*collection, (*centers)[j], all_h_values_of_all_g, g_hash, k, L, M, modulo_Exponents_of_m, 0, W, R, &R_neighbors);


            cout << "R=" << R << ", C= " << j << ":";

            for (auto i : R_neighbors) {
                flag = false;
               for (unsigned int x = 0; x < already_found.size(); x++) {
                    if (i == already_found[x]) { //an exei ksanavrethei ayto to simeio ws geitoniko allou kentrou gia tin idia R
                        newNeighbors = true;
                        flag = true; //an yparxei idi na min ksanaprostethei sto already_found

                        //Lloyd
                        cen = already_found_points_centers[x];
                        dist = Manhattan_Distance((*centers)[cen], (*collection)[i]);
                        dist2 = Manhattan_Distance((*centers)[j], (*collection)[i]);
                        if (cen != j && dist2 <dist) {
                            def->point_to_second_best[i] = cen; //def->point_to_nearest_cluster[i];
                            // assign to cluster j:
                            def->point_to_nearest_cluster[i] = j; 
                            def->cluster_to_points[j].insert(i);
                            
                            already_found_points_centers[x]=j;
                            int x = def->cluster_to_points[cen].size();
                            // remove from cluster cen:
                            cout << "Before: " << def->cluster_to_points[cen].size() << endl;

                            for (auto s : def->cluster_to_points[cen]) {
                                cout << s << " ";
                            }
                            cout << endl;

                            def->cluster_to_points[cen].erase(i);

                            int y = def->cluster_to_points[cen].size();

                            if (x - y != 1) {
                                cout << " x = " << x << endl;
                                cout << " y = " << y << endl;
                                cout << "after: " << def->cluster_to_points[cen].size() << endl;
                                for (auto s : def->cluster_to_points[cen]) {
                                    cout << s << " ";
                                }
                                cout << endl;

                                cout << "erase failed for: " << i << "  \n";
                                exit(3);
                            }
                        }else if(cen != j )
                        {
                            cen2=def->point_to_second_best[i];
                            dist3=Manhattan_Distance((*centers)[cen2], (*collection)[i]);
                            
                            if ( dist2 < dist3) {
                            def->point_to_second_best[i] = j;
                            
                            }}
                      break;
                    }
                }
                if (flag == false) {//an den exei ksanavrethei
                    newNeighbors = true;

                    if (find(all_that_were_found.begin(), all_that_were_found.end(), i) == all_that_were_found.end()) { //an den exei vrethei pote
                        def->cluster_to_points[j].insert(i);
                        
                        def->point_to_nearest_cluster[i] = j;
                        min = INT_MAX;
                         for (int x = 0; x < C; x++) {//vriskw me lloyd to second_best
                             if(x!=j){
                                 
                                dist = Manhattan_Distance((*centers)[x], (*collection)[i]);

                                if (dist < min) {
                                    min = dist;
                                    minj = x;

                                } 
                                 }
                         }
                        def->point_to_second_best[i] = minj;
                        
                        
                        
                        //vazw sto already_found tous R_neighbors
                        already_found.push_back(i);
                        already_found_points_centers.push_back(j);
                        all_that_were_found.push_back(i);
                        cout << "i = " << i << endl;
                    }

                    
                }

            }

        }

        R = R * 2;
        
        if (newNeighbors == false) {
            break;
        }
        // break: after a specific threshold i.e R > 200000
        if (R > 200000) {
            break;
        }


    }
    int secondminj;
    //an kapoia de vrethikan katholou kanw Lloyd
    images_count = collection->size();
    for (int i = 0; i < images_count; i++) {
        flagLeftovers = true;
        for (unsigned j = 0; j < all_that_were_found.size(); j++) {
            if (i == all_that_were_found[j]) {
                flagLeftovers = false; //den einai s ayta pou perissepsan
            }
        }

        if (flagLeftovers == true) {
            //Lloyd
            min = INT_MAX;
            int secondMin = INT_MAX;

            for (int j = 0; j < C; j++) {
                int dist = Manhattan_Distance((*centers)[j], (*collection)[i]);

                if (dist < min) {
                    secondMin = min;
                    secondminj = minj;
                    min = dist;
                    minj = j;

                } else if (dist < secondMin && dist != min) {
                    secondMin = dist;
                    secondminj = j;
                }
            }
            if (secondminj == INT_MAX) {
                cout << "ERROR: could not find second best" << endl;
                exit(2);
            }

            def->point_to_nearest_cluster[i] = minj;
            def->point_to_second_best[i] = secondminj;
            def->cluster_to_points[minj].insert(i);
        }
    }




    return def;
}
