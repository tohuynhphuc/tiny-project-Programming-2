#include "LinearSystem.cpp"
#include "Matrix.cpp"
#include "Vector.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <limits>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
	// testing Vector
	Vector v1 = Vector(3);
	double arr[] = {1, 2, 3, 4, 5, 6};
	Vector v2 = Vector(arr, 6);
	double *arr2 = (double*)calloc(6, sizeof(double));
	for (int i = 0; i < 6; i++) {
		arr2[i] = 6 - i; // [6, 5, 4, 3, 2, 1]
	}
	Vector v3 = Vector(arr2, 6);
	cout << "v1: " << v1.toString() << endl;
	cout << "v2: " << v2.toString() << endl;
	cout << "v3: " << v3.toString() << endl;

	return 0;
}