
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>


#include "Clustering.h"
#include "ClassicClustering.h"
#include "LshClustering.h"
#include "HypercubeClustering.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "ClusteringReading.h"
#include "ImageCollection.h"

using namespace std;

// $./cluster  -i  <input  file>  -c  <configuration  file>  -o  <output  file>  -complete  <optional> -m <method: Classic OR LSH or Hypercube>
// i c o complete m



int main(int argc, char * argv[]) {
    string input_file = "", output = "", config = "", method = "";
    bool complete = false;
    bool error = false;
    
    // classic:
    int K;

    // LSH:
    int L = 3, k_lsh = 4;

    // Hypercube
    int M_cube = 10, k_cube = 3, probes = 2;
    
    // LSH+Hypercube
    int W = 1000;

    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == "-i") {
            input_file = argv[i + 1];
        }
        if (string(argv[i]) == "-c") {
            config = argv[i + 1];
        }
        if (string(argv[i]) == "-o") {
            output = argv[i + 1];
        }
        if (string(argv[i]) == "-complete") {
            complete = true;
        }
        if (string(argv[i]) == "-m") {
            method = argv[i + 1];
        }
    }

    if (input_file == "") {
        printf("input is missing \n");
        error = true;
    }

    if (output == "") {
        printf("output is missing \n");
        error = true;
    }

    if (config == "") {
        printf("config is missing \n");
        error = true;
    }

    if (method == "") {
        printf("method is missing \n");
        error = true;
    }

    if (error) {
        printf("lathos parametroi \n");
        printf("prepei na einai: -i  <input  file>  -c  <configuration  file>  -o  <output  file>  -complete  <optional> -m <method: Classic OR LSH or Hypercube>");
        return 0;
    }
   
    ifstream configfile(config); //anoigei to arxeio 
    if (configfile.is_open() && configfile.good()) {
        string line = "";
        while (getline(configfile, line)) {
            stringstream command(line);
            string data[2] = {"", ""};
            command >> data[0] >> data[1];

            if (data[0] == "number_of_clusters:") {
                K = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_vector_hash_tables:") {
                L = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_vector_hash_functions:") {
                k_lsh = atoi(data[1].c_str());
            }
            if (data[0] == "max_number_M_hypercube:") {
                M_cube = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_hypercube_dimensions:") {
                k_cube = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_probes:") {
                probes = atoi(data[1].c_str());
            }

        }

        cout << "number_of_clusters              : " << K << endl;
        cout << "number_of_vector_hash_tables    : " << L << endl;
        cout << "number_of_vector_hash_functions : " << k_lsh << endl;
        cout << "max_number_M_hypercube          : " << M_cube << endl;
        cout << "number_of_hypercube_dimensions  : " << k_cube << endl;
        cout << "number_of_probes                : " << probes << endl;
        cout << "complete                        : " << complete << endl;

        ImageCollection collection;

        int numberOfImages = ReadMNIST_NumberOfImages(input_file.c_str(), &collection);
        
        cout << "Number of images in input file is: " << numberOfImages << endl;
        
        ReadMNIST(input_file.c_str(), &collection,&collection.rows, &collection.columns);

        cout << "The rows are " << collection.rows << " and the columns are " << collection.columns << "\n";

        int dimensions = collection.rows * collection.columns;
        
        cout << "Collection Size=" << collection.size() << endl;
        cout << "Collection dimensions=" << dimensions << endl;

        Clustering * clustering;
        
        // trim because of speed
        //collection.resize(200);

	clock_t tStart = clock(); //metraw to xrono poy pairnei to clustering kai ton ektypwnw sto arxeio

        if (method == "Classic") { //analogws ti methodo kalei tin antisoixi clustering
            clustering = new ClassicClustering(&collection, K);
        } else if (method == "LSH") {
           clustering = new LshClustering(&collection, K, L, k_lsh, W);
        } else if (method == "Hypercube") {
            clustering = new HypercubeClustering(&collection, K, k_cube, W, M_cube, probes, dimensions);
        } else {
            cout << "Unsupported method: " << method << "  \n";
            return -1;
        }

		cout<<"test"<<endl;
        int limit = (int) log(W); //to limit gia na stamataei - xrisimo sto debugging mou

        AssignmentDefinition * result = clustering->execute(limit);
	double clustertime=(clock() - tStart)/CLOCKS_PER_SEC; //metraw to xrono poy pairnei to clustering kai ton ektypwnw sto arxeio
        vector<float> sil; //epistrefw ta apotelesmata tou silhouette se vector etsi wste na ta ektypwsw se arxeio
        sil=clustering->silhouette(result);
        
        cout << "***************************************************\n";
        cout << "                   Results \n" ;
        cout << "***************************************************\n";
        clustering->printResults(result);
        
        //write output file
        string s = string(output);
        ofstream fp(s.c_str()); 
        if(method=="Classic")
            fp << "Algorithm: Lloyds"  << endl;
        else if(method=="LSH")
            fp << "Algorithm: Range Search LSH"  << endl;
        else if(method=="Hypercube")
            fp<<"Algorithm:  Range Search Hypercube"<<endl;
        else
            fp<<"Algorithm: Unsupported method"<<endl;
       
        for(int i=0;i<K;i++){
            fp << "CLUSTER-" <<i<<" "<<"{size: "<<result->cluster_to_points[i].size()<<", centroid: " ;

                vector<int> & temp = (*(result->centers))[i]; //pairnw tis syntetagmenes gia to kentro i
                unsigned int s = temp.size();
                for (unsigned l=0;l<s-1;l++) {
                    fp << temp[l] << ",";                    
                }
                fp<<temp[s-1]; //to ksexwrisa apla gia na min vazei , sto teleytaio stoixeio
          
            fp<<"}"<<endl;
        }
        
        
        fp<<"clustering_time: "<<clustertime<<" sec"<<endl;
        
        fp<<"Silhouette: ["<<sil[0];
        for(unsigned int i=1;i<sil.size();i++){
            fp<< ","<<sil[i];
        }
        fp<<"]"<<endl;
        set<int> points;
        int temporary,tem;
        
        if(complete==true){//an dothei complete ektypwnw kathe cluster me to centroid k me ta simeia tou
            fp<<endl;
            fp<<endl;
            for(int i=0;i<K;i++){
                fp<<"CLUSTER-"<<i<<" {";
                temporary=result->cluster_to_points[i].size();
                points=result->cluster_to_points[i];
                tem=0;
                for (auto it = points.begin(); it != points.end(); ++it)
                {  fp<< *it;
                    if(tem<temporary-1){ //ayto to kanw mono gia na min mpainei , sto teleytaio
                        fp<<",";
                    }tem++;
                    
                }fp<<"}"<<endl;
            }
        }
        
        if (result != nullptr) {
            delete result;
        }

        delete clustering;
    } else {
        cout << "Failed to open file.." << config;
    }

    return 0;
}
