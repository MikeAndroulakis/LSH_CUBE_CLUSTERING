#include "ClassicClustering.h"
#include <cmath>
#include <iostream>
#include <climits>

#include "../Functions_for_both_algorithms/Calculate_Distances.h"

using namespace std;

ClassicClustering::ClassicClustering(ImageCollection * imagecol, int C) : Clustering(imagecol, C) {
   
}

ClassicClustering::~ClassicClustering() {
    // destroy hashtables
}

AssignmentDefinition * ClassicClustering::assignment(ImageCollection * centers) {
    AssignmentDefinition * def = new AssignmentDefinition();
    int minj,secondminj;
    int C = centers->size();
    
    def->centers = centers;

    int images_count = collection->size();

    for (int i = 0; i < images_count; i++) { //gia kathe simeio vriskw apostasi apo to kathe kentro
        int min = INT_MAX;
        int secondMin= INT_MAX; 
        
        for (int j = 0; j < C; j++) {
            int dist = Manhattan_Distance((*centers)[j], (*collection)[i]);
          
            if (dist < min) {
                secondMin=min;
                secondminj=minj;
                min = dist;
                minj = j;

            }else if(dist<secondMin && dist!=min){//second_best -> to krataw gia to silhouette 
                secondMin=dist;
                secondminj=j;
            }
        }
        if(secondminj==INT_MAX){
            cout<<"ERROR: could not find second best"<<endl;
            exit(2);
        }//krataw kai ta second best giati ta xreiazomai sto silhouette
        def->point_to_nearest_cluster[i] = minj;
        def->point_to_second_best[i]=secondminj;
        def->cluster_to_points[minj].insert(i);
       
    }
    
    return def;

}
