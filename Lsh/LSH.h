#ifndef LSH_H
#define LSH_H

#include <vector>
#include <set>
#include <string>
#include "Hash.h"

using namespace std;

void Hash_The_Train_File( vector <vector <vector <int> > > *all_h_values_of_all_g , vector <Hash> *g_hash , vector<vector <int> > input_vector , int Num_of_Buckets , int L , int k , int M , vector <int> modulo_Exponents_of_m , int W );

void Compute_the_values_of_h(vector <int>* h_values,vector <int> p,vector <vector<int> > h_function,int k,int M,vector <int> modulo_Exponents_of_m,int W);

unsigned int Compute_the_value_of_g(vector <int> h_values,int k);

void Hash_The_Queries_And_Calculate_Neighbors( vector<vector <int> > input_vector , vector<vector <int> > query_vector , vector <vector <vector <int> > > all_h_values_of_all_g , vector <Hash> g_hash , int k , int L , int M , vector <int> modulo_Exponents_of_m , int N , int W , int R , string output_file );

void Hash_The_Queries_And_Calculate_Neighbors_For_Clustering(vector<vector <int> > input_vector, vector <int> query_vector, vector <vector <vector <int> > > all_h_values_of_all_g, vector <Hash> g_hash, int k, int L, int M, vector <int> modulo_Exponents_of_m, int N, int W, int R, set <int> * R_neighbors);

void Calculate_The_LSH_Neighbors(vector <int> pictures_of_bucket,int query,vector <int> query_vector,vector <vector <int> > input_vector,int N,int R,vector <int>* nearest_neighbors,vector <int>* best_distances);

void Calculate_The_R_Neighbors_For_Clustering(vector <int> pictures_of_bucket, vector <int> query_vector, vector <vector <int> > input_vector, set <int>* R_neighbors, int R);



#endif
