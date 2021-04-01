#include "Reading.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

void Read_Arguements_of_Main(int argc, char **argv, string* input_file, string* query_file, string* output_file, int *k, int *M, int *probes, int *L, int *N, int *R) {
    for (int ar = 0; ar < argc - 1; ar++) {
        if (strcmp(argv[ar], "-d") == 0) {
            *input_file = argv[ar + 1];
        } else if (strcmp(argv[ar], "-q") == 0) {
            *query_file = argv[ar + 1];
        } else if (strcmp(argv[ar], "-o") == 0) {
            *output_file = argv[ar + 1];
        } else if (strcmp(argv[ar], "-k") == 0) {
            *k = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-M") == 0) {
            *M = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-probes") == 0) {
            *probes = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-L") == 0) {
            *L = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-N") == 0) {
            *N = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-R") == 0) {
            *R = atoi(argv[ar + 1]);
        }
    }
}

void ReadMNIST(string input_file, vector<vector <int> >* all_images , int *rows, int *columns) {
    ifstream file(input_file, ios::binary);
    if (file.is_open()) {
		//cout<<"Mpike"<<endl;
        int magic_number = 0;
        int num_of_images = 0;
        file.read((char*) &magic_number, sizeof (magic_number));
        magic_number = ReverseInt(magic_number);
        //cout<<"The magic number is:"<<magic_number<<"\n";
        file.read((char*) &num_of_images, sizeof (num_of_images));
        num_of_images = ReverseInt(num_of_images);
        //cout<<"Number of images are:"<<num_of_images<<"\n";
        file.read((char*) rows, sizeof (int));
        *rows = ReverseInt(*rows);
        file.read((char*) columns, sizeof (int));
        *columns = ReverseInt(*columns);
        //cout<<"The Rows are "<<*rows<<" and the Columns are "<<*columns<<"\n";
        int flag = 0;
        while (1) {
            vector<int> image;
            for (int j = 0; j<*columns; j++) {
                for (int k = 0; k<*rows; k++) {
                    unsigned char pixel = 0;
                    file.read((char*) &pixel, sizeof (pixel));
                    if (file.eof()) {
                        flag = 1;
                        break;
                    }
                    image.push_back((int) pixel);
                }
                if (flag == 1) {
                    break;
                }
            }
            if (flag == 1) {
                break;
            }
            (*all_images).push_back(image);
        }
    } else {
        cout << "File " << input_file << " can't be opened\n";

    }
}

int ReverseInt(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8)&255;
    ch3 = (i >> 16)&255;
    ch4 = (i >> 24)&255;
    return ((int) ch1 << 24)+((int) ch2 << 16)+((int) ch3 << 8) + ch4;
}


