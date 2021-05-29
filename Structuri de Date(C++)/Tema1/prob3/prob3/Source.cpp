#include <iostream>
using namespace std;
void citire(int &nr_elemente, int*& vector)
{
	cout << "Introduceti numarul de elemente ale vectorului:";
	cin >> nr_elemente;
	vector = new int[nr_elemente];
	cout << "Introduceti elementele vectorului:";
	for (int index = 0; index < nr_elemente; index++)
		cin >> vector[index];

}
bool verificarecrescator(int nr_elemente, int* vector)
{
	for (int index = 0; index < nr_elemente - 1; index++)
		if (vector[index] > vector[index + 1])
			return false;
			return true;

}
bool verificaredescrescator(int nr_elemente, int* vector)
{
	for (int index = 0; index < nr_elemente - 1; index++)
		if (vector[index] < vector[index + 1])
			return false;
	return true;

}
bool verificareconstant(int nr_elemente, int* vector)
{
	for (int index = 0; index < nr_elemente - 1; index++)
		if (vector[index] != vector[index + 1])
			return false;
	return true;


}

int main()
{
	int nr_elemente, * vector;
	citire(nr_elemente, vector);
	if (verificareconstant(nr_elemente, vector) == true)
		cout << "Vectorul poate fi considerat atat sortat crescator cat si descrescator(constant)";
	else
	{
		if (verificarecrescator(nr_elemente, vector) == true)
			cout << "Vectorul este sortat crescator";
		if (verificaredescrescator(nr_elemente, vector) == true)
			cout << "Vectorul este sortat descrescator";
		if (verificarecrescator(nr_elemente, vector) == false && verificaredescrescator(nr_elemente, vector) == false)
			cout << "Vectorul nu este sortat";
	}
	delete[]vector;
	return 0;

}