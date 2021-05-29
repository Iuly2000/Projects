#include <iostream>
#include <fstream>
using namespace std;
void Citirematricefisier(string filepath, int &n, int**& matrice)
{
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		myfile >> n;
		matrice = new int* [n];
		matrice[0] = new int[n * n];
		for (int index = 1; index < n; index++)
			matrice[index] = matrice[index - 1] + n;
		for (int index1 = 0; index1 < n; index1++)
			for (int index2 = 0; index2 < n; index2++)
				myfile >> matrice[index1][index2];
		myfile.close();
	}
	else
		cout << "Nu se poate deschide fisierul!";


}
int nivele(int n)
{
	if (n % 2 == 0)
		return n / 2;
	else
		return n / 2 + 1;
}
int calcularesuma(int index1, int n, int** matrice)
{
	int suma = 0;
	for (int index = index1; index < n - index1; index++)
		suma += matrice[index1][index];
	for (int index = index1 + 1; index < n - index1; index++)
		suma += matrice[index][n - index1 - 1];
	for (int index = n - index1 - 2; index >= index1; index--)
		suma += matrice[n - index1 - 1][index];
	for (int index = n - index1 - 2; index > index1; index--)
		suma += matrice[index][index1];
	return suma;
}
void sume(int nivel, int n, int** matrice)
{
	int index1 = 0;
	while (nivel != 0)
	{
		cout << "Suma" << index1 + 1 << " este " << calcularesuma(index1, n, matrice) << endl;
		index1++;
		nivel--;
	}

}
int main()
{
	int n, ** matrice, nivel;
	string filepath = "Matrice.txt";
	Citirematricefisier(filepath, n, matrice);
	nivel = nivele(n);
	sume(nivel, n, matrice);
	delete matrice[0];
	delete matrice;
	return 0;
}
