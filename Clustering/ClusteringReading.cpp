#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


#include "ClusteringReading.h"
#include "../Functions_for_both_algorithms/Reading.h"

int ReadMNIST_NumberOfImages(string input_file, vector<vector <int> >* all_images) {
    ifstream file(input_file, ios::binary);
    if (file.is_open()) {
        int magic_number = 0;
        int num_of_images = 0;
        file.read((char*) &magic_number, sizeof (magic_number));
        magic_number = ReverseInt(magic_number);
        file.read((char*) &num_of_images, sizeof (num_of_images));
        num_of_images = ReverseInt(num_of_images);
        return num_of_images;
    } else {
        cout << "File " << input_file << " can't be opened\n";
        exit(1);
    }
}
