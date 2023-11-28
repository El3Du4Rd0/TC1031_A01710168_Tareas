#include <iostream>
using namespace std;

class Funciones{
    public:
    long sumaIterativa (int n);
	long sumaRecursiva (int n);
    long sumaDirecta (int n);
};

long Funciones::sumaIterativa (int n){
    int acum = 0;
    for (int i = 0; n >= i; i++){
        acum += i;
    }
    return acum;
}

long Funciones::sumaRecursiva(int n) {
	if(n == 0) return 0; 
	return n + sumaRecursiva(n-1);
}

long Funciones::sumaDirecta(int n) {
	return n*(n+1) / 2;
}