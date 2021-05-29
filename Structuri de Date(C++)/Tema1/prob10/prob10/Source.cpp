#include <iostream>
using namespace std;
void CitireMatrice(int& n, int**& matrice)
{
	cout << "Introduceti valoarea lui n=";
	cin >> n;
	matrice = new int* [n];
	matrice[0] = new int[n * n];
	for (int index = 1; index < n; index++)
		matrice[index] = matrice[index - 1] + n;
	cout << "Introduceti valorile matricei:" << endl;
	for (int index = 0; index < n; index++)
		for (int index1 = 0; index1 < n; index1++)
			cin >> matrice[index][index1];
	cout << endl;
}
void CreareVector(int n, int*& vector, int** matrice)
{
	vector = new int[n * (n + 1) / 2];
	int contor = 0;
	for (int index = 0; index < n; index++)
		for (int index1 = 0; index1 < index + 1; index1++)
			vector[contor++] = matrice[index][index1];

}

void dealocare(int** matrice1, int* vector1)
{
	delete[]matrice1[0];
	delete[]matrice1;
	delete[]vector1;
}
void afisare(int n, int* vector)
{
	for (int i = 0; i < n * (n + 1) / 2; i++)
		cout << vector[i] << " ";

}
int main()
{
	int n, ** matrice1, * vector1;
	CitireMatrice(n, matrice1);
	CreareVector(n, vector1, matrice1);
	afisare(n, vector1);
	dealocare(matrice1, vector1);
	return 0;
}