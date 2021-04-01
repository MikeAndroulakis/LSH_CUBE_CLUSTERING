#include "Modulos.h"
#include <vector>

using namespace std;

int Modular_exponentiation(int base,int exponent,int M){
	
	int result=1;
	for(int power=1;power<=exponent;power++){
		
		result=(result*base)&(M-1);
	}
	//cout<<"EIMASTE EXPONENTIATION KAI BASE="<<base<<" kai exponent="<<exponent<<" kai M="<<M<<"KAI RESULT="<<result<<"\n";
	return result;
}


void Calculate_the_Modulo_Exponents(vector <int>* modulo_Exponents_of_m,int m,int M,int size){//vector gia modulo exponents wste na mhn ksanaypologizontai
	for(int i=0;i<size;i++){
		(*modulo_Exponents_of_m).push_back(Modular_exponentiation(m,i,M));
		//cout<<"test"<<i<<endl;
	}

}
