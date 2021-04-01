#ifndef CUBE_H
#define CUBE_H
#include "Cube_Struct.h"
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

void hash_The_Train_Images_to_The_Corners( vector <Corner> &cube , vector < unordered_map <int,int> > &values_of_f , vector <vector <int> > input_vector , vector <vector <int> > h_function , int d , int MM , vector <int> modulo_Exponents_of_m , int W );

void hash_The_Queries_And_Calculate_Neighbors( vector <Corner> cube , vector < unordered_map <int,int> > values_of_f , vector <vector <int> > query_vector , vector <vector <int> > input_vector , vector <vector <int> > h_function , int d , int M , int N , int probes , int R , string output_file , int MM , vector <int> modulo_Exponents_of_m , int W );

int Scan_The_Bucket_of_The_Query( vector <int> pictures_of_bucket , vector <int> &nearest_neighbors , vector <int> &distances , vector< vector <int> > input_vector , vector <int> query , int M );

void Scan_Hamming_Buckets( int counter_of_checked_images , vector <int> query , vector <vector <int> > input_vector , vector <Corner> cube , vector <int> &nearest_neighbors , vector <int> &distances ,int M,int d,int probes,string f_string_value);

void hash_The_Queries_And_Calculate_Neighbors_Clustering(vector <Corner> cube, vector < unordered_map <int, int> > values_of_f, vector <int> query_vector, vector <vector <int> > input_vector, vector <vector <int> > h_function, int d, int M, int N, int probes, int R, string output_file, int MM, vector <int> modulo_Exponents_of_m, int W,vector <int> & R_neighbors) ;
#endif
