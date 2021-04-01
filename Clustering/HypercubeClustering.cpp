#include <cmath>
#include "HypercubeClustering.h"
#include "../Cube/Cube.h"
#include "../Cube/h_Function_Cube.h"
#include "../Cube/Cube_Struct.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "../Functions_for_both_algorithms/Modulos.h"
#include "../Clustering/HypercubeClustering.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"

using namespace std;

HypercubeClustering::HypercubeClustering(ImageCollection * imagecol, int C, int k, int W, int MM, int probes, int dimensions)
: Clustering(imagecol, C), Num_of_Buckets(pow(2, k)), k(k), W(W), MM(MM), max_integer_bucket_num(pow(2, k) - 1), probes(probes),
M(pow(2, (int) (32 / k))), m(M - 1), dimensions(dimensions) {
	int d=(log2(imagecol->size()))-1; //cout<<"d= "<<d<<endl;
    cout << "Dimensions: " << dimensions << endl;
    Calculate_the_Modulo_Exponents(&modulo_Exponents_of_m, m, M, dimensions);

	int max_integer_bucket_num=pow(2,d)-1;
    for (int i = 0; i < max_integer_bucket_num; i++) {
        Corner corner(i);
        cube.push_back(corner);
    }
	
    random_numbers_generating(&h_function, d, W, dimensions); //apothikeyoume sto vector h_function toys tyxaioys arithmoys s gia tis d h
	
	unordered_map <int,int> map_f;
	for(int i=0;i<d;i++){
	     values_of_f.push_back(map_f);
	}
	cout<<"size="<<cube.size()<<endl;
    hash_The_Train_Images_to_The_Corners(cube, values_of_f, *imagecol, h_function, d, M, modulo_Exponents_of_m, W);
	cout<<"edw"<<endl;
}

HypercubeClustering::~HypercubeClustering() {

}

AssignmentDefinition * HypercubeClustering::assignment(ImageCollection * centers) {
    AssignmentDefinition * def = new AssignmentDefinition();
    int C = centers->size();

    bool flagLeftovers = false;
    double R = 50000;
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
        already_found.clear();
        already_found_points_centers.clear();
        for (int j = 0; j < C; j++) {
            vector <int> R_neighbors;
            //vriskw tous neighbors se R
			//cout<<"edwwwwww"<<endl;
			int d=log2(images_count) - 1;
            hash_The_Queries_And_Calculate_Neighbors_Clustering(cube, values_of_f, (*centers)[j], *collection, h_function, d, MM, 0, probes, R, "output_file", M, modulo_Exponents_of_m, W, R_neighbors);

            for (auto i : R_neighbors) {
                cout << i << "  ";
            }
            
            cout << "R=" << R << ", C= " << j << ":" << " R neighbors size: " << R_neighbors.size() << endl;

            for (auto i : R_neighbors) {
                flag = false;
                for (unsigned int x = 0; x < already_found.size(); x++) {
                    if (i == already_found[x]) {
                        newNeighbors = true;
                        flag = true; //an yparxei idi na min ksanaprostethei sto already_found

                        //Lloyd
                        cen = already_found_points_centers[x];
                        dist = Manhattan_Distance((*centers)[cen], (*collection)[i]);
                        dist2 = Manhattan_Distance((*centers)[j], (*collection)[i]);
                        if (cen != j && dist > dist2) {
                            def->point_to_second_best[i] = cen;//def->point_to_nearest_cluster[i];
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
                if (flag == false) {
                    newNeighbors = true;

                    if (find(all_that_were_found.begin(), all_that_were_found.end(), i) == all_that_were_found.end()) {
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


