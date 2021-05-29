#include <iostream>
using namespace std;
int nivele(int &n)
{
	cout << "Introduceti un numar:";
	cin >> n;
	if (n % 2 == 0)
		return n / 2;
	else
		return n / 2 + 1;
}
void construirespirala(int n, int**& matrice, int nivel)
{
	matrice = new int* [n];
	matrice[0] = new int[n * n];
	for (int index = 1; index < n; index++)
		matrice[index] = matrice[index - 1] + n;
	int contor, index1 = 0;
	if (n % 2 == 0)
	{
		contor = 1;
		while (index1 != nivel)
		{
			for (int index = index1; index < n - index1; index++)
			{
				matrice[index1][index] = contor;
				contor++;
			}
			for (int index = index1 + 1; index < n - index1; index++)
			{
				matrice[index][n - index1 - 1] = contor;
				contor++;
			}
			for (int index = n - index1 - 2; index >= index1; index--)
			{
				matrice[n - index1 - 1][index] = contor;
				contor++;
			}
			for (int index = n - index1 - 2; index > index1; index--)
			{
				matrice[index][index1] = contor;
				contor++;
			}
			index1++;

		}
	}
	else
	{
		contor = n * n;
		while (index1 != nivel)
		{
			for (int index = index1; index < n - index1; index++)
			{
				matrice[index1][index] = contor;
				contor--;
			}
			for (int index = index1 + 1; index < n - index1; index++)
			{
				matrice[index][n - index1 - 1] = contor;
				contor--;
			}
			for (int index = n - index1 - 2; index >= index1; index--)
			{
				matrice[n - index1 - 1][index] = contor;
				contor--;
			}
			for (int index = n - index1 - 2; index > index1; index--)
			{
				matrice[index][index1] = contor;
				contor--;
			}
			index1++;

		}
	}
}
	void afisarematrice(int n, int** matrice)
	{
		for (int index = 0; index < n; index++)
		{
			cout << endl;
			for (int index1 = 0; index1 < n; index1++)
				cout << matrice[index][index1] << " ";
		}
		delete[]matrice[0];
		delete matrice;
	}

	int main()
	{
		int n, ** matrice, nivel;
		nivel = nivele(n);
		construirespirala(n, matrice, nivel);
		afisarematrice(n, matrice);
		return 0;
	}