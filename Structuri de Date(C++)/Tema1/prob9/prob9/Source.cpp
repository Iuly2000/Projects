#include <iostream>
using namespace std;
void Citirevector(int &n, int*& vector)
{
	cout << "Introduceti numarul de elemente ale vectorului:";
	cin >> n;
	vector = new int[n];
	cout << "Introduceti elementele vectorului:";
		for (int index = 0; index < n; index++)
			cin >> vector[index];

}
void Permutarecirculara(int n, int* vector)
{
	int var = vector[0];
	for (int index = 0; index < n - 1; index++)
		vector[index] = vector[index + 1];
	vector[n - 1] = var;
}
void CreareMatrice(int n, int**& matrice, int* vector)
{
	matrice = new int* [n];
	matrice[0] = new int[n * n];
	for (int index = 1; index < n; index++)
		matrice[index] = matrice[index - 1] + n;
	for (int index = 0; index < n; index++)
		matrice[0][index] = vector[index];
	for (int index = 1; index < n; index++)
	{
		Permutarecirculara(n, vector);
		for (int index1 = 0; index1 < n; index1++)
			matrice[index][index1] = vector[index1];
	}


}
void Afisarematrice(int n, int** matrice)
{
	for (int index = 0; index < n; index++)
	{
		cout << endl;
		for (int index1 = 0; index1 < n; index1++)
			cout << matrice[index][index1] << " ";
	}
}

int main()
{
	int n, * vector, ** matrice;
	Citirevector(n, vector);
	CreareMatrice(n, matrice, vector);
	Afisarematrice(n, matrice);
	return 0;
}