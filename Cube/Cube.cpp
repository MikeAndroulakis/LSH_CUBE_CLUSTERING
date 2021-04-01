#include "Cube.h"
#include "Cube_Struct.h"
#include "h_Function_Cube.h"
#include "f_Function_Cube.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include "../Functions_for_both_algorithms/Writing.h"
#include "../Functions_for_both_algorithms/Quicksort.h"
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <sys/time.h>
#include <bitset>
#include <chrono>
#include <random>


using namespace std;

void hash_The_Train_Images_to_The_Corners(vector <Corner> &cube,vector < unordered_map <int,int> > &values_of_f,vector <vector <int> > input_vector,vector <vector <int> > h_function,int d,int MM,vector <int> modulo_Exponents_of_m,int W){
	int num_of_pics=input_vector.size();
	unsigned seed=chrono::system_clock::now().time_since_epoch().count();
	for(int picture=0;picture<num_of_pics;picture++){//gia oles tis eikones
		string f_string_value;
		int f_integer_value=Calculate_The_Total_f_value(values_of_f,h_function,input_vector[picture],MM,modulo_Exponents_of_m,d,W,f_string_value,seed);
		
		cube[f_integer_value].InsertItem(picture);
		//cout<<"Picture : "<<picture<<" F="<<f_integer_value<<endl;
	}
}

void hash_The_Queries_And_Calculate_Neighbors( vector <Corner> cube , vector < unordered_map <int,int> > values_of_f , vector <vector <int> > query_vector , vector <vector <int> > input_vector , vector <vector <int> > h_function , int d , int M , int N , int probes , int R , string output_file , int MM , vector <int> modulo_Exponents_of_m , int W ){
	struct timeval startCUBE,endCUBE,startTRUE,endTRUE;
	unsigned seed=chrono::system_clock::now().time_since_epoch().count();
	for(int query=0;query<(int) query_vector.size();query++){
		cout<<"Query"<<query<<endl;
		string f_string_value;
		int query_bucket=Calculate_The_Total_f_value(values_of_f,h_function,query_vector[query],MM,modulo_Exponents_of_m,d,W,f_string_value,seed);
		//cout<<"INDEX="<<query_bucket<<endl;
		vector <int> pictures_of_bucket;
		cube[query_bucket].Loadhash(&pictures_of_bucket);

		vector <int> nearest_neighbors;
		vector <int> distances;
		vector <int> R_neighbors;

		gettimeofday(&startCUBE,NULL);
		int counter_of_checked_images=Scan_The_Bucket_of_The_Query(pictures_of_bucket,nearest_neighbors,distances,input_vector,query_vector[query],M);	
		Scan_Hamming_Buckets(counter_of_checked_images,query_vector[query],input_vector,cube,nearest_neighbors,distances,M,d,probes,f_string_value);
		quicksort(distances,nearest_neighbors, 0, distances.size() - 1);
		gettimeofday(&endCUBE,NULL);

		double timeCUBE=(endCUBE.tv_sec - startCUBE.tv_sec)*1e6;
		timeCUBE=(timeCUBE + (endCUBE.tv_usec - startCUBE.tv_usec))*1e-6;

		Calculate_The_R_Neighbors(nearest_neighbors,distances,&R_neighbors,R);

		vector <int> true_best_distances;
		vector <int> true_nearest_neighbors;
		gettimeofday(&startTRUE,NULL);
		find_the_true_distances(input_vector,query_vector[query],&true_best_distances,&true_nearest_neighbors,nearest_neighbors.size() );
		gettimeofday(&endTRUE,NULL);
		double timeTRUE=(endTRUE.tv_sec - startTRUE.tv_sec)*1e6;
		timeTRUE=(timeTRUE + (endTRUE.tv_usec - startTRUE.tv_usec))*1e-6;
		Writing_to_the_output_file(output_file,query,nearest_neighbors,distances, true_best_distances,R_neighbors,timeCUBE,timeTRUE,N,"cube");


	}

}


void hash_The_Queries_And_Calculate_Neighbors_Clustering(vector <Corner> cube, vector < unordered_map <int, int> > values_of_f, vector <int> query_vector, vector <vector <int> > input_vector, vector <vector <int> > h_function, int d, int M, int N, int probes, int R, string output_file, int MM, vector <int> modulo_Exponents_of_m, int W,vector <int> & R_neighbors) {
    string f_string_value = "";
    unsigned seed=chrono::system_clock::now().time_since_epoch().count();
    int query_bucket = Calculate_The_Total_f_value(values_of_f, h_function, query_vector, M, modulo_Exponents_of_m, d, W, f_string_value,seed);
    vector <int> pictures_of_bucket;
    cube[query_bucket].Loadhash(&pictures_of_bucket);
    vector <int> nearest_neighbors;
    vector <int> distances;

    int counter_of_checked_images = Scan_The_Bucket_of_The_Query(pictures_of_bucket, nearest_neighbors, distances, input_vector, query_vector, M);
    Scan_Hamming_Buckets(counter_of_checked_images, query_vector, input_vector, cube, nearest_neighbors, distances, MM, d, probes, f_string_value);

    Calculate_The_R_Neighbors(nearest_neighbors, distances, &R_neighbors, R);
}


int Scan_The_Bucket_of_The_Query( vector <int> pictures_of_bucket , vector <int> &nearest_neighbors , vector <int> &distances , vector< vector <int> > input_vector , vector <int> query , int M ){
	int counter_of_checked_images=0;
	for(int i=0;i<(int) pictures_of_bucket.size(); i++){//tha elegxthoun M to polu shmeia
		nearest_neighbors.push_back( pictures_of_bucket[i] );
		int distance=Manhattan_Distance(query,input_vector[ pictures_of_bucket[i] ]);
		distances.push_back(distance);
		//cout<<" Nearest="<<pictures_of_bucket[i]<<" and distance="<<distance<<endl;
		counter_of_checked_images++;
		if(counter_of_checked_images==M){
			break;
		}
	}
	return counter_of_checked_images;
}

void Scan_Hamming_Buckets(int counter_of_checked_images,vector <int> query,vector <vector <int> > input_vector, vector <Corner> cube , vector <int> &nearest_neighbors , vector <int> &distances ,int M,int d , int probes , string f_string_value){
	if(counter_of_checked_images<M){
		//cout<<"M so far="<<counter_of_checked_images<<endl;
		int counter_for_probes=0;
		for(int j=0;j<d;j++){
			string temp_f=f_string_value;
			if(f_string_value[j]=='0'){
				temp_f[j]='1';
			}
			else if(f_string_value[j]=='1'){
				temp_f[j]='0';
			}
			//cout<<"The TRUE BUCKET IS:"<<f_string_value<<"and this BUCKET is"<<temp_f<<endl;
			int neighbor_bucket=stoull(temp_f,0,2);
			vector <int> neighbor_bucket_pictures;
			cube[neighbor_bucket].Loadhash(&neighbor_bucket_pictures);
			counter_of_checked_images+=Scan_The_Bucket_of_The_Query(neighbor_bucket_pictures,nearest_neighbors,distances,input_vector,query,M-counter_of_checked_images);
			counter_for_probes++;
			if(counter_for_probes==probes || counter_of_checked_images==M){
				break;
			}
		}
	}
}
