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

void aparitii(int nr_elemente, int* vector)
{
	int* vapar = new int[101];
	for (int index = 0; index < 101; index++)
		vapar[index] = 0;
	for (int index = 0; index < nr_elemente; index++)
		vapar[vector[index]]++;
	for (int index = 0; index < 101; index++)
		if (vapar[index] > 1)
			cout << index << " apare de " << vapar[index] << " ori" << endl;
}
int main()
{
	int nr_elemente, * vector;
	citire(nr_elemente, vector);
	aparitii(nr_elemente, vector);
	delete[]vector;
}