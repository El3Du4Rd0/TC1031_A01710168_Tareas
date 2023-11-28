#ifndef SORTS_H_
#define SORTS_H_

// Se incluye la libreria vector para crear un arreglo dinamico
#include <vector>

// Se crea la clase tipo Sorts
template <class T>
class Sorts {
    // Se definen todas las funciones que integran la clase Sorts
public:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
    int  bs_aux(std::vector<T> &v, int min, int max, int val);
	void ordenaBurbuja(std::vector<T>&);
	void ordenaSeleccion(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);
    T busqSecuencial(const std::vector<T>&, int val);
    T busqBinaria(const std::vector<T>&, int val);
};

// Funcion Swap que sirve para intercambiar valores
template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

// Funcion que ejecuta el Bubble sort
template <class T>
void Sorts <T>::ordenaBurbuja(std::vector<T> &vec) {
	for (int i = vec.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (vec[j] > vec[j + 1]) {
				swap(vec, j, j + 1);
		    }
	    }
    }
}

// Funcion que ejecuta el selection sort
template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &vec) {
	int pos;
	for (int i = vec.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (vec[j] > vec[pos]) {
				pos = j;
		    }
	    }
		if (pos != i) {
			swap(vec, i, pos);
		}
	}
}

// Funcion auxiliar que copia un arreglo
template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

// Funcion auxiliar que fusiona un arreglo con otro
template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {

	int i = low;
	int j = mid + 1;
	int k = low;

	while (i <= mid &&j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}

	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

// Funcion que divide un arreglo
template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	if ( (high - low) < 1 ) return;
	int mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

// Funcion que ejecuta el Merge sort
template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &vec) {
	 std::vector<T> tmp(vec.size());

	mergeSplit(vec, tmp, 0, vec.size() - 1);
}

// Funcion que busca un elemento en un arreglo de forma lineal
template <class T>
T Sorts<T>:: busqSecuencial(const std::vector<T>&vec, int val){
    int mid;
	int low = 0;
	int high = vec.size()-1;

	while (low < high) {
		mid = (high + low) / 2;
		if (val == vec[mid]) {
			return mid;
		} else if (val < vec[mid]) {
			high = mid - 1;
		} else if (val > vec[mid]) {
			low = mid + 1;
		}
    }
    if (vec[low]==val) return low;
	else return -1;
}

// Funcion auxiliar que sirve para ejecutar la busqueda binaria
template <class T>
int Sorts<T>:: bs_aux(std::vector<T> &v, int min, int max, int val) {
	if (min <= max) {
		int mid = (min + max) / 2;
		if (val == v[mid]) {
			return mid;
		} else if (val < v[mid]) {
			return bs_aux(v, min, mid - 1, val);
		} else if (val > v[mid]) {
			return bs_aux(v, mid + 1, max, val);
		}
	}

	if (v[min]==val) return min;
	else return -1;
}

// Funcion que busca un elemento en un arreglo de forma binaria
template <class T>
T Sorts<T>::busqBinaria(const std::vector<T> &vec, int val) {
	std::vector<T> v(vec);
	return bs_aux(v, 0, v.size() - 1, val);
}

#endif