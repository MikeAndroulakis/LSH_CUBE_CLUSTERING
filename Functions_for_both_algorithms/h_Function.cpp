#include "h_Function.h"
#include <vector>
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

void random_numbers_generating(vector<vector <int> >* h_function,int k,int W,int size){//random numbers twn h
	for(int h=0;h<k;h++){
		vector <int> s;
		for(int dimension=0;dimension<size;dimension++){
			s.push_back(static_cast <int> (rand())/static_cast <int> (RAND_MAX/W));
			//cout<<"The vector is  "<<s[dimension]<<"\n";
		}
		(*h_function).push_back(s);
	}
	
}


int Compute_the_value_of_h(vector <int> a,vector <int> modulo_Exponents_of_m,int M,int dimensions){//methodos recursion gia ypologismo ths timhs ths h
	int value=0;
	for(int i=0;i<dimensions;i++){
		int modulo_of_a=a[dimensions-(i+1)]%M;
		if(modulo_of_a<0){//an to ai mod M einai arnhtiko tote to kanoume thetiko
			modulo_of_a+=M;
		}
		int paragontas=modulo_of_a*modulo_Exponents_of_m[i];
		value+=paragontas & (M-1);
	}
	return value & (M-1);
}
