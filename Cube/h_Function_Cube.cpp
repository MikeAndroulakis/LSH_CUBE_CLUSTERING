#include "h_Function_Cube.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include <vector>

using namespace std;


int Compute_the_h_value(vector <int>  s,vector <int> p,int MM,vector <int> modulo_Exponents,int W){
	vector <int> a;
	for(int dimension=0;dimension<(int) p.size();dimension++){//gia oles tis diastaseis
		//cout<<p[dimension]<<"  "<<s[dimension]<<endl;
		int sub=p[dimension]-s[dimension];//ypologismos toy pi-si
		//cout<<"Sub="<<sub<<"\n";
		int result=sub/W;
		if(sub>=0){//ypologismos tou floor
			a.push_back((int) result);
		}
		else{//ypologismos tou floor an exoyme arnhtiko
			a.push_back(((int) result)-1);
		}
		//cout<<"  nai  "<<a[dimension]<<endl;
	}
	return Compute_the_value_of_h(a,modulo_Exponents,MM,p.size());

}
