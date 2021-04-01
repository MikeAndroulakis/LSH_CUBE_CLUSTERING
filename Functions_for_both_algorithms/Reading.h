#include <vector>
#include <string>

#ifndef READING_H
#define READING_H

using namespace std;

void Read_Arguements_of_Main(int argc,char **argv,string* input_file,string* query_file,string* output_file,int *k,int *M,int *probes,int *L,int *N,int *R);

void ReadMNIST(string input_file,vector<vector <int> >* all_images,int *rows,int *columns);

int ReverseInt(int i);

#endif
