#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <unordered_map>

#include "Cube.h"
#include "h_Function_Cube.h"
#include "Cube_Struct.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "../Functions_for_both_algorithms/Modulos.h"

#include "../Functions_for_both_algorithms/Calculate_Distances.h"

#define MULTIPLIER 1

int main(int argc,char** argv){
	string input_file;
	string query_file;  
    string output_file;
	vector<vector <int> > input_vector;
	vector<vector <int> > query_vector;
	int rows=0;
	int columns=0;
    int k=14;
	int M=10;
	int L;
	int probes=2;
	int N=1;
	int R=40000;
	
	Read_Arguements_of_Main(argc,argv,&input_file,&query_file,&output_file,&k,&M,&probes,&L,&N,&R);
	if (input_file.empty()){
        cout << "Give the path of the dataset file:";
        cin >> input_file;
    }
	ReadMNIST(input_file,&input_vector,&rows,&columns);
	cout<<"k="<<k<<"  M="<<M<<" probes="<<probes<<"  N="<<N<<"  R="<<R<<"\n";
	long int MM=pow(2,(int) (32/k));
	long int m;
	if(MM==2){
		m=MM-1;
	}
	else{
		m=MM/2-1;
	}
	int size=rows*columns;
	int number_of_images=input_vector.size();
	int d=int( log2(number_of_images) ) -1 ;	
	int W=MULTIPLIER*Compute_W(input_vector,size);
	cout<<"d="<<d<<" m="<<m<<" and M="<<MM<<" and W="<<W<<"\n";
	int i;
	
	srand((unsigned)time(0));
	vector <int> modulo_Exponents_of_m;
	Calculate_the_Modulo_Exponents(&modulo_Exponents_of_m,m,MM,size);

	int max_integer_bucket_num=pow(2,d)-1;
	//cout<<"MAX="<<max_integer_bucket_num<<endl;
	vector <Corner> cube;
	for(i=0;i<=max_integer_bucket_num;i++){
		Corner corner(i);
		cube.push_back(corner);
	}

	vector <vector <int> > h_function;
	random_numbers_generating(&h_function,d,W,size);//apothikeyoume sto vector h_function toys tyxaioys arithmoys s gia tis d h
	unordered_map <int,int> map_f;
	vector < unordered_map <int,int> > values_of_f;
	for(int i=0;i<d;i++){
		values_of_f.push_back(map_f);
	}

	hash_The_Train_Images_to_The_Corners(cube,values_of_f,input_vector,h_function,d,MM,modulo_Exponents_of_m,W);
	cout<<"The train finished"<<endl;
	if (query_file.empty()){
		cout << "Give the path of query file:";
		cin >> query_file;
		cout<<"\n";
	}
	if(output_file.empty()){
		cout <<"Give the path of output file:";
		cin >> output_file;
	}

querysearch:
	ReadMNIST(query_file,&query_vector,&rows,&columns);
	hash_The_Queries_And_Calculate_Neighbors(cube,values_of_f,query_vector,input_vector,h_function,d,M,N,probes,R,output_file,MM,modulo_Exponents_of_m,W);
	cout<<"Wanna run the Search again or do you want to terminate the program?Press yes if you want to Search again,otherwise press no"<<endl;
	string answer;
	cin>>answer;
	if(answer=="yes" || answer=="y" ){
		cout << "Give the path of the new query file:";
		cin >> query_file;
		cout<<"\n";
		cout <<"Give the path of the new output file:";
		cin >> output_file;
		goto querysearch;
	}
	else{
		return 1;
	}
}
