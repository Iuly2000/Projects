#include <iostream>
using namespace std;
void citirematrice(int &m, int &n, int**& matrice)
{
	cout << "Introduceti numarul de linii si de coloane:";
	cin >> m >> n;
	matrice = new int* [m];
	matrice[0] = new int[m * n];
	for (int index = 1; index < m; index++)
		matrice[index] = matrice[index - 1] + n;
	cout << "Introduceti elementele matricii:";
	cout << endl;
	for (int index = 0; index < m; index++)
		for (int index2 = 0; index2 < n; index2++)
			cin >> matrice[index][index2];
}
void Afisbaza10(int m, int n, int** matrice)
{
	int numar;
	cout << "Numerele in baza 10 sunt:";
	for (int index1 = 0; index1 < m; index1++)
	{
		if (index1 > 0)
			cout << numar << " ";
		numar = 0;
		for (int index2 = 0; index2 < n; index2++)
			if (matrice[index1][index2] == 1)
				numar = numar + pow(2, n - index2 - 1);
	}
	cout << numar;
}
int main()
{
	int m, n, ** matrice;
	citirematrice(m, n, matrice);
	Afisbaza10(m, n, matrice);
	delete[]matrice[0];
	delete[]matrice;
	return 0;
}