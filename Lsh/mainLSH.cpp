#include "LSH.h"
#include "Hash.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "../Functions_for_both_algorithms/Modulos.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
 
#define MULTIPLIER 2
#define BUCKET_PARAMETER 8

using namespace std;


int main(int argc,char **argv){
	string input_file;
	string query_file;   
    string output_file;

	vector<vector <int> > input_vector;
	vector<vector <int> > query_vector;
	int rows=0;
	int columns=0;
    int k=4;
	int L=5;
	int N=1;
	int R=10000;
	int Num_of_Buckets;
	int M;
	int probes;//gia to cube einai de mas apasxolei
	Read_Arguements_of_Main(argc,argv,&input_file,&query_file,&output_file,&k,&M,&probes,&L,&N,&R);
	if (input_file.empty()){
        cout << "Give the path of the dataset file:";
        cin >> input_file;
    }
	ReadMNIST(input_file,&input_vector,&rows,&columns);
	Num_of_Buckets=( input_vector.size() )/BUCKET_PARAMETER;
	M=pow(2,(int) (32/k));
	long int m=M/4-5;
	int size=rows*columns;
	cout<<"k="<<k<<" L="<<L<<" N="<<N<<" R="<<R<<endl;
	int W=MULTIPLIER*Compute_W(input_vector,size);
	cout<<"m="<<m<<" and M="<<M<<" and W="<<W<<"\n";
	srand((unsigned)time(0));

	
	
	vector <int> modulo_Exponents_of_m;
	Calculate_the_Modulo_Exponents(&modulo_Exponents_of_m,m,M,size);//modulo_Exponents einai enas vector pou apothikeyoume tis m^x mod M times wste na mh tis ksanaypologizoyme
	/*for(int i=0;i<modulo_Exponents_of_m.size();i++){
		cout<<"m^"<<i<<" mod "<<M<<" = "<<modulo_Exponents_of_m[i]<<endl;
	}*/
	vector <Hash> g_hash;
	vector <vector <vector <int> > > all_h_values_of_all_g;
	Hash_The_Train_File(&all_h_values_of_all_g,&g_hash,input_vector,Num_of_Buckets,L,k,M,modulo_Exponents_of_m,W);
	cout<<"Train finished"<<endl;
	if (query_file.empty()){
		cout << "Give the path of query file:";
		cin >> query_file;
		cout<<"\n";
	}
	if (output_file.empty()){
		cout <<"Give the path of output file:";
		cin >> output_file;
	}

querysearch:
	ReadMNIST(query_file,&query_vector,&rows,&columns);
	Hash_The_Queries_And_Calculate_Neighbors(input_vector,query_vector,all_h_values_of_all_g,g_hash,k,L,M,modulo_Exponents_of_m,N,W,R,output_file);
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






