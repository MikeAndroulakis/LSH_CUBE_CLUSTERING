#include "f_Function_Cube.h"
#include "h_Function_Cube.h"
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <sys/time.h>

using namespace std;

int Calculate_The_Total_f_value(vector < unordered_map <int,int> > &values_of_f,vector <vector <int> > h_function,vector <int> picture_vector,int MM,vector <int> modulo_Exponents_of_m,int d,int W,string &f_string_value,unsigned seed){
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0,1);
	for(int f=0;f<d;f++){
		int h=Compute_the_h_value(h_function[f],picture_vector,MM,modulo_Exponents_of_m,W);
		//cout<<"h="<<h<<endl;
		if(values_of_f[f][h]==0){//ama den yparxei sto unordered map
			//cout<<"f="<<f<<" and h="<<h<<endl;
			int random_number=distribution(generator);
			if(random_number==1){
				values_of_f[f][h]=2;
			}
			else if(random_number==0){
				values_of_f[f][h]=1;
			}
		}
		//cout<<"H="<<h<<endl;
		f_string_value+=to_string(values_of_f[f][h]-1);
			
	}
	//cout<<"STRING="<<f_string_value<<endl;
	return stoull(f_string_value,0,2);
}
