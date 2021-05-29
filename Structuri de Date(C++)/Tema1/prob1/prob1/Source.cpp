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
void triplete(int nr_elemente, int* vector)
{
	for (int index = 0; index < nr_elemente - 2; index++)
		if (vector[index] < vector[index + 1]&&vector[index+1] < vector[index + 2])
			cout << vector[index] << "," << vector[index + 1] << "," << vector[index + 2] << endl;
}

int main()
{
	int nr_elemente, * vector;
	citire(nr_elemente, vector);
	triplete(nr_elemente, vector);
	delete[] vector;

	return 0;


}