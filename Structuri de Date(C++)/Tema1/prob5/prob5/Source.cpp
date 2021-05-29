#include <iostream>
using namespace std;
void Citirematrice(int &n, int**& matrice)
{
	cout << "Introduceti numarul de elevi:";
	cin >> n;
	matrice = new int* [n];
	matrice[0] = new int[n * n];
	for (int index = 1; index < n; index++)
		matrice[index] = matrice[index - 1] + n;
	cout << "Introduceti elementele matricei de prietenie:" << endl;
	for (int index = 0; index < n; index++)
		for (int index1 = 0; index1 < n; index1++)
			cin >> matrice[index][index1];

}

void Reciproc(int n, int** matrice)
{
	for (int index = 0; index < n - 1; index++)
		for (int index1 = index + 1; index1 < n; index1++)
			if (matrice[index][index1] == 1 && matrice[index1][index] == 1)
				cout << "Elevii " << index + 1 << " si " << index1 + 1 << " se agreeaza reciporc" << endl;
}
void Nuagreeaza(int n, int** matrice)
{
	int ok = 2;
	for (int index1 = 0; index1 < n; index1++)
	{
		if (ok == 1)
			cout << "Elevul " << index1 << " nu agreeaza pe nimeni" << endl;
		ok = 1;

		for (int index2 = 0; index2 < n; index2++)
			if (matrice[index2][index1] == 1 && index2 != index1)
				ok = 0;
	}

	if (ok == 1)
		cout << "Elevul " << n << " nu agreeaza pe nimeni" << endl;
	ok = 1;
}

void Neagreat(int n, int** matrice)
{
	int ok = 2;
	for (int index1 = 0; index1 < n; index1++)
	{
		if (ok == 1)
			cout << "Elevul " << index1 << " nu este agreat de nimeni" << endl;
		ok = 1;

		for (int index2 = 0; index2 < n; index2++)
			if (matrice[index1][index2] == 1 && index2 != index1)
				ok = 0;
	}

	if (ok == 1)
		cout << "Elevul " << n << " nu este agreat de nimeni" << endl;
	ok = 1;

}

int main()
{
	int n, ** matrice;
	Citirematrice(n, matrice);
	Reciproc(n, matrice);
	cout << endl;
	Nuagreeaza(n, matrice);
	cout << endl;
	Neagreat(n, matrice);
	delete[]matrice[0];
	delete matrice;
	return 0;
}