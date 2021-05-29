#include<iostream>
using namespace std;
void citire(int& numar, int& n, int& p, int*& vector)
{
	cout << "Introduceti numarul de cifre ale numarului:";
	cin >> n;
	vector = new int[n];
	cout << "Introduceti numarul pe cifre:";
	for (int index = 0; index < n; index++)
	{
		cin >> numar;
		vector[index] = numar;
	}
	cout << "Introduceti numarul de cifre care vor fi sterse:";
	cin >> p;
	if (p >= n || p < 0)
		while (p >= n || p < 0)
		{
			cout << "Numarul introdus nu este corect,introduceti alt numar:";
			cin >> p;
		}
}
void numarmaxim(int n, int p, int* vector)
{
	for (int index = 0; index < n; index++)
	{
		if (p == 0)
			break;
		if (vector[index] < vector[index + 1])
		{
			vector[index] = -1;
			p--;
			int copie = index + 1;
			int copie2 = index - 1;
			if (p > 0)
				while (p > 0&&copie2>=0)
				{
					if (vector[copie2] < vector[copie] && vector[copie2] != -1)
					{
						vector[copie2] = -1;
						p--;
					}
					copie2--;
				}
		}
	}
	if (p != 0)
		while (p != 0)
		{
			vector[n - 1] = -1;
			p--;
			n--;
		}

}

void  afisarenumar(int n, int* vector)
{

	for (int index = 0; index < n; index++)
		if (vector[index] != -1)
			cout << vector[index];
}

int main()
{
	int numar, n = 0, p, * vector;
	citire(numar, n, p, vector);
	numarmaxim(n, p, vector);
	afisarenumar(n, vector);
	delete[]vector;
	return 0;
}