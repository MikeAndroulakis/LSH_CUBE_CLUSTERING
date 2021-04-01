#include "Clustering.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

Clustering::Clustering(ImageCollection * collection, int C) : collection(collection), C(C) {

}

ImageCollection * Clustering::initialize() {
    int used = -1; //oi theseis pou exw kentro
    ImageCollection * centers = new ImageCollection();

    int images_count = collection->size();

    cout << "Initialization started for " << images_count << " images " << endl;

    int idc = static_cast<int> (images_count * (rand() / (RAND_MAX + 1.0)));

    vector<int> firstcenter = (*collection)[idc]; //to tyxaio prwto kentro

    centers->push_back(firstcenter);

    float * Pr = new float [images_count];

    int l=0,mid=0;
    int ri=images_count-1;
    
    for (int i = 0; i < images_count; i++) { //arxikopoiisi
        Pr[i] = 0;
    }
    Pr[idc] = used; //i thesi tou prwtou kentrou

    float current_sum = 0;

    cout << "idc = " << idc << endl;

    for (int i = 1; i < C; i++) { //gia kathe kentro
        // fill Pr
        for (int j = 0; j < images_count; j++) { //gia kathe image/dianysma
            if (Pr[j] != -1) { //an den einai idi epilegmeno ws kentro
                int min = INT_MAX;

                for (int k = 0; k < i; k++) {
                    int dist = Manhattan_Distance((*centers)[k], (*collection)[i]);
                    if (dist < min) {
                        min = dist;
                    }
                }

                current_sum += min * (float) min;

                Pr[j] = current_sum;//Pr o pinalas me ta merika athroismata opws stis diafaneies
            }
        }
      // pick a random value r from [0, Pr(??)]
        float r = static_cast<float> (rand()) / static_cast<float> (RAND_MAX / (0.0f + current_sum));

        
        // simple search -  not binary   
//        for (int j = 0; j < images_count; j++) {
//            if (Pr[j] == -1) {
//                continue;
//            }
//
//            if (r < Pr[j] || Pr[j] == current_sum) {
//                Pr[j] = -1;
//
//                vector<int> nextcenter = (*collection)[j];
//                centers->push_back(nextcenter);
//
//                cout << "id next center = " << j << endl;
//                break;
//            }
//        }
//       
      
  //optimized with binary search
        
        l=0,mid=0;
        ri=images_count-1;
        while (l <= ri || Pr[l]==-1 || Pr[ri]==-1) { 
            
            while(Pr[l]==-1){
                 l++;
             }
            while(Pr[ri]==-1){
                ri--;
            }
            mid= l + (ri - l) / 2; 
            
            
            if (Pr[mid] > r && Pr[mid]!=-1 && Pr[mid-1]<r) {
               Pr[mid] = -1;

                vector<int> nextcenter = (*collection)[mid]; //otan einai sto swsto pedio, epilegei to mid ayto gia thesi tou neou kentroy
                centers->push_back(nextcenter);

                cout << "id next center = " << mid << endl;
                break;
            }else if(Pr[mid] < r && Pr[mid]!=-1){
                l = mid + 1;    
            }
            else if(Pr[mid]!=-1){
                ri = mid - 1;} 
        }


            }

    delete [] Pr;



    return centers;
}

ImageCollection * Clustering::update(ImageCollection * centers, AssignmentDefinition * assignments) {
    unsigned int C = centers->size(); // 4
    unsigned int D = (*collection)[0].size(); // 784

    ImageCollection * newcenters = new ImageCollection();

    for (unsigned int i = 0; i < C; i++) { //gia kathe cluster/kentro
        set<int> & s = assignments->cluster_to_points[i]; //ta simeia tou cluster autou

        vector<int> newcenter;

        for (unsigned d = 0; d < D; d++) {
            set<int> values;

            if (s.size() == 0) { // empty cluster
                newcenter.push_back(0);
            } else {
                for (auto id : s) {
                    values.insert((*collection)[id][d]);
                }

                unsigned len = values.size();
                unsigned mid = len / 2;

                newcenter.push_back(mid);
            }
        }

        newcenters->push_back(newcenter);
    }

    return newcenters;
}

bool Clustering::shouldStop(ImageCollection * oldcenters, ImageCollection * newcenters) { //synartisi wste na krinei an prepei na stamatisei 
    bool result = true;
    int newCent = 0, old = 0;
    if (newcenters != nullptr) {
        old = oldcenters->size();
    }

    if (newcenters != nullptr) {
        newCent = newcenters->size();
    }

    if (old < newCent) {
        cout << "ERROR" << endl;
        exit(100);
        return false; //it should not stop
    } else if (old > newCent) {
        cout << "ERROR" << endl;
        cout << "old: " << old << endl;
        cout << "new: " << newCent << endl;
        exit(111);
        return true; //stop
    } else { //an vrethikan nea simeia diladi
        for (int i = 0; i < old; i++) {
            if (Manhattan_Distance((*oldcenters)[i], (*newcenters)[i]) != 0) {
                result = false;
            }
        }
    }
    return result;
}

AssignmentDefinition * Clustering::execute(int limit) {
    ImageCollection * centers = initialize();
    AssignmentDefinition * def = nullptr;

    while (limit > 0 || limit == -1) {
       // cout << "Loop: " << ++counter << " (limit: " << limit << ")" << endl;
       // centers->printCompressed();

        def = assignment(centers);

        //        def->print();
	
        ImageCollection * newcenters = update(centers, def);

        if (shouldStop(centers, newcenters)) {
            cout << "should stop returned true \n";
            break;
        } else {
            centers = newcenters;

            if (centers == NULL) {
                cout << "centers null " << endl;
                break;
            }
        }

        if (limit > 0) {
            limit--;
        }
    }

    return def;
}

void Clustering::printResults(AssignmentDefinition * def) {
    def->print();
}

void AssignmentDefinition::print() {
    unsigned int C = centers->size();

    for (unsigned int i = 0; i < C; i++) {
        cout << "[Center " << i << "]: size=" << this->cluster_to_points[i].size() << " : ";

        set<int> & s = this->cluster_to_points[i];

        for (auto x : s) {
            cout << x << " ";
        }
        cout << endl;
        cout << "----------------------------\n";
    }
}

float Clustering::avg_distance_from_objects_of_cluster(AssignmentDefinition * def,int center,int j){//gia ti silhouette
    //gia ola ta stoixeia tou kentrou autou
    set<int> points=def->cluster_to_points[center];
    ImageCollection * cent=def->centers;
    set<int> ::iterator itr;
    float dist=0,total=0;
    float count=0.0;
    for(itr=points.begin();itr!=points.end();++itr){ //gia kathe stoixeio pou anikei sto cluster tou center, ektos tou kentrou
       if(*itr!=j){
            dist = Manhattan_Distance((*collection)[j],(*collection)[*itr]);
            total+=dist;
            count++;   
       }
    }
    dist= Manhattan_Distance((*collection)[j],(*cent)[center]); //i apostasi apo to kentro
    total+=dist;
    count++;
    return total/count;
}

vector<float> Clustering::silhouette(AssignmentDefinition * def){
    float result = 0;
    int nearest_center,second_best,count=0;
    float a,b,max,s,totalS=0.0;
    int images_count = collection->size();
    vector<float> sil;
    //gia kathe image i
    for(int i=0;i<images_count;i++){
        //vriskw a(i)
        nearest_center=def->point_to_nearest_cluster[i];
        a=avg_distance_from_objects_of_cluster(def,nearest_center,i);
        
        //vriskw b(i)
        second_best=def->point_to_second_best[i];
        b=avg_distance_from_objects_of_cluster(def,second_best,i);
        
        //vriskw s(i)
        max=b;
        if(a>b){
            max=a;
        }
        s=(b-a)/max;
        sil.push_back(s);
        //cout<<"s is "<<s<<endl;
        totalS+=s;
        count++;
    }
    //vriskw to synoliko silhouette
    result=totalS/count;
    sil.push_back(result);
    cout<<"total S: "<<totalS<<" Count: "<<count<<" silhouette: "<<result<<endl;
   
    return sil;
}
