#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <sys/time.h>

#include "LSH.h"
#include "Hash.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include "../Functions_for_both_algorithms/Quicksort.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include "../Functions_for_both_algorithms/Writing.h"

using namespace std;

void Hash_The_Train_File(vector <vector <vector <int> > > *all_h_values_of_all_g, vector <Hash> *g_hash, vector<vector <int> > input_vector, int Num_of_Buckets, int L, int k, int M, vector <int> modulo_Exponents_of_m, int W) {
    int size = input_vector[0].size();
    int TRAIN_IMAGES = input_vector.size();
    Hash g_h(Num_of_Buckets);
    for (int g = 0; g < L; g++) {//kataskeyh twn g hashtables gia ta train images
        (*g_hash).push_back(g_h); //h domh einai ena vector apo antikeimena hash(dld ena vector poy sth kathe thesi exei deikth poy deixnei se lista)
        vector <vector <int> > h_function;
        random_numbers_generating(&h_function, k, W, size); //apothikeyoume sto vector h_function toys tyxaioys arithmoys s gia tis k h
        (*all_h_values_of_all_g).push_back(h_function); //prosthetoume ola ta si twn k h wste na xrhsimopoihthoun kai apo ta query
        for (int picture = 0; picture < TRAIN_IMAGES; picture++) {//gia oles tis eikones
            vector <int> h_values;
            Compute_the_values_of_h(&h_values, input_vector[picture], h_function, k, M, modulo_Exponents_of_m, W);
            unsigned int value_of_g = Compute_the_value_of_g(h_values, k);
            //cout<<"Value="<<value_of_g<<endl;
            (*g_hash)[g].InsertItem(picture, value_of_g);
        }
        //cout << "teleiwse h g = " << g << endl;
    }
}

void Compute_the_values_of_h(vector <int>* h_values, vector <int> p, vector <vector<int> > h_function, int k, int M, vector <int> modulo_Exponents_of_m, int W) {
    int size = p.size();
    for (int h = 0; h < k; h++) {//gia kathe h
        vector <int> a;
        //cout<<"h="<<h<<endl;
        for (int dimension = 0; dimension < size; dimension++) {//gia oles tis diastaseis
            int sub = p[dimension] - h_function[h][dimension]; //ypologismos toy pi-si
            float result = sub / W;
            //cout<<"Result="<<result<<"\n";
            if (sub >= 0) {//ypologismos tou floor
                a.push_back((int) result);
            } else {//ypologismos tou floor an exoyme arnhtiko
                a.push_back(((int) result) - 1);
            }
            //cout<<"a="<<a[dimension]<<endl;
        }
        int value_of_h = Compute_the_value_of_h(a, modulo_Exponents_of_m, M, size); //kalesma ths synarthshs gia ton ypologismo ths eksiswshs sth selida 20
		//cout<<"h="<<value_of_h<<endl;
        (*h_values).push_back(value_of_h);
    }
}

unsigned int Compute_the_value_of_g(vector <int> h_values, int k) {
    int metatopisi = (int) 32 / k; //xrhsimopoeitai gia to concatenation
    unsigned int num_of_bucket;
    for (int h = 0; h < k; h++) {
        if (h == 0) {
            num_of_bucket = h_values[0];
        } else {
            num_of_bucket = (num_of_bucket) | (h_values[h] << (metatopisi * h)); //analogws poses h exoume tha metakinountai metatopish*h bits kathe fora
        }
    }
    return num_of_bucket;
}

void Hash_The_Queries_And_Calculate_Neighbors(vector<vector <int> > input_vector, vector<vector <int> > query_vector, vector <vector <vector <int> > > all_h_values_of_all_g, vector <Hash> g_hash, int k, int L, int M, vector <int> modulo_Exponents_of_m, int N, int W, int R, string output_file) {
    struct timeval startLSH, endLSH, startTRUE, endTRUE;
    int QUERY_IMAGES = query_vector.size();
    for (int query = 0; query < QUERY_IMAGES; query++) {
        vector <int> best_distances;
        vector <int> nearest_neighbors;
        vector <int> R_neighbors;
        double timeLSH = 0.0;
        for (int g = 0; g < L; g++) {
            vector <int> h_values;
            Compute_the_values_of_h(&h_values, query_vector[query], all_h_values_of_all_g[g], k, M, modulo_Exponents_of_m, W);
            /*for (int i = 0; i < k; i++) {
                cout << "h" << i << "=" << h_values[i] << endl;
            }*/
            unsigned int value_of_g = Compute_the_value_of_g(h_values, k);
            cout << "query=" << query << "  g=" << g << " value_of_g=" << value_of_g << endl;
            int index = g_hash[g].hashFunction(value_of_g);
            vector <int> pictures_of_bucket;
            //cout<<"Indexofhashing="<<index<<endl;
            gettimeofday(&startLSH, NULL);
            g_hash[g].Loadhash(&pictures_of_bucket, index);
            Calculate_The_LSH_Neighbors(pictures_of_bucket, query, query_vector[query], input_vector, N, R, &nearest_neighbors, &best_distances);
            gettimeofday(&endLSH, NULL);
            double timetaken = (endLSH.tv_sec - startLSH.tv_sec)*1e6;
            timeLSH += (timetaken + (endLSH.tv_usec - startLSH.tv_usec))*1e-6;
        }
        gettimeofday(&startLSH, NULL);
        quicksort(best_distances, nearest_neighbors, 0, best_distances.size() - 1);
        gettimeofday(&endLSH, NULL);
        double timetaken = (endLSH.tv_sec - startLSH.tv_sec)*1e6;
        timeLSH += (timetaken + (endLSH.tv_usec - startLSH.tv_usec))*1e-6;
        Calculate_The_R_Neighbors(nearest_neighbors, best_distances, &R_neighbors, R);
        gettimeofday(&startTRUE, NULL);
        vector <int> true_best_distances;
        vector <int> true_nearest_neighbors;
        find_the_true_distances(input_vector, query_vector[query], &true_best_distances, &true_nearest_neighbors, N);
        gettimeofday(&endTRUE, NULL);
        double timeTRUE = (endTRUE.tv_sec - startTRUE.tv_sec)*1e6;
        timeTRUE = (timeTRUE + (endTRUE.tv_usec - startTRUE.tv_usec))*1e-6;

        Writing_to_the_output_file(output_file, query, nearest_neighbors, best_distances, true_best_distances, R_neighbors, timeLSH, timeTRUE, N, "lsh");
    }

}

void Hash_The_Queries_And_Calculate_Neighbors_For_Clustering(vector<vector <int> > input_vector, vector <int> query_vector, vector <vector <vector <int> > > all_h_values_of_all_g, vector <Hash> g_hash, int k, int L, int M, vector <int> modulo_Exponents_of_m, int N, int W, int R, set <int> * R_neighbors) {
    for (int g = 0; g < L; g++) {
        vector <int> h_values;
        Compute_the_values_of_h(&h_values, query_vector, all_h_values_of_all_g[g], k, M, modulo_Exponents_of_m, W);
        
        unsigned int value_of_g = Compute_the_value_of_g(h_values, k);
        int index = g_hash[g].hashFunction(value_of_g);
        vector <int> pictures_of_bucket;
        //cout<<"Indexofhashing="<<index<<endl;
        g_hash[g].Loadhash(&pictures_of_bucket, index);

        Calculate_The_R_Neighbors_For_Clustering(pictures_of_bucket, query_vector, input_vector, R_neighbors, R);
                
    }
}

void Calculate_The_R_Neighbors_For_Clustering(vector <int> pictures_of_bucket, vector <int> query_vector, vector <vector <int> > input_vector, set <int>* R_neighbors, int R) {
    int num_of_pics = pictures_of_bucket.size();
    for (int i = 0; i < num_of_pics; i++) {
        int distance = Manhattan_Distance(query_vector, input_vector[pictures_of_bucket[i]]);
         if (distance < R) {
            (*R_neighbors).insert(pictures_of_bucket[i]);
        }
    }
}


void Calculate_The_LSH_Neighbors(vector <int> pictures_of_bucket, int query, vector <int> query_vector, vector <vector <int> > input_vector, int N, int R, vector <int>* nearest_neighbors, vector <int>* best_distances) {
    int num_of_pics = pictures_of_bucket.size();
    for (int i = 0; i < num_of_pics; i++) {
        if (!count((*nearest_neighbors).begin(), (*nearest_neighbors).end(), pictures_of_bucket[i])) {
			int distance = Manhattan_Distance(query_vector, input_vector[pictures_of_bucket[i]]);
            //cout << "EXOUME:" << " eikona " << pictures_of_bucket[i] << " apostash " << distance << endl;
            (*nearest_neighbors).push_back(pictures_of_bucket[i]);
            (*best_distances).push_back(distance);
        }
    }

}



