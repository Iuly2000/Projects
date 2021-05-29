#include <iostream>
#include<fstream>
#include <queue>
using namespace std;
#include <iostream>
using namespace std;
void citire_vector_fisier(string filepath, int& nr_linii, int& nr_coloane, int**& matrice)
{
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		myfile >> nr_linii >> nr_coloane;

		matrice = new int* [nr_linii];
		matrice[0] = new int[nr_linii * nr_coloane];
		for (int index = 1; index < nr_linii; index++)
			matrice[index] = matrice[index - 1] + nr_coloane;
		for (int index1 = 0; index1 < nr_linii; index1++)
			for (int index2 = 0; index2 < nr_coloane; index2++)
				myfile >> matrice[index1][index2];
		myfile.close();
	}
	else
		cout << "Unable to open the file";

}
void parcurgereetaj(int** matrice, queue <pair<int, int>> Pozitii, int nr_linii, int nr_coloane)
{
	int nr2 = 0;
	pair<int, int>max;
	max.first = 0;
	max.second = 0;
	for (int index1 = 0; index1 < nr_linii; index1++)
		for (int index2 = 0; index2 < nr_coloane; index2++)
			if (matrice[index1][index2] == 0)
			{
				nr2++;
				int nr = 1;
				pair<int, int>temp;
				temp.first = index1;
				temp.second = index2;
				Pozitii.push(temp);
				matrice[index1][index2] = nr;
				while (Pozitii.empty() == 0)
				{
					if (matrice[Pozitii.front().first + 1][Pozitii.front().second] == 0)
					{
						matrice[Pozitii.front().first + 1][Pozitii.front().second] = ++nr;
						pair<int, int> temp;
						temp.first = Pozitii.front().first + 1;
						temp.second = Pozitii.front().second;
						Pozitii.push(temp);
					}
					if (matrice[Pozitii.front().first][Pozitii.front().second + 1] == 0)
					{
						matrice[Pozitii.front().first][Pozitii.front().second + 1] = ++nr;
						pair<int, int> temp;
						temp.first = Pozitii.front().first;
						temp.second = Pozitii.front().second + 1;
						Pozitii.push(temp);
					}
					if (matrice[Pozitii.front().first - 1][Pozitii.front().second] == 0)
					{
						matrice[Pozitii.front().first - 1][Pozitii.front().second] = ++nr;
						pair<int, int> temp;
						temp.first = Pozitii.front().first - 1;
						temp.second = Pozitii.front().second;
						Pozitii.push(temp);
					}
					if (matrice[Pozitii.front().first][Pozitii.front().second - 1] == 0)
					{
						matrice[Pozitii.front().first][Pozitii.front().second - 1] = ++nr;
						pair<int, int> temp;
						temp.first = Pozitii.front().first;
						temp.second = Pozitii.front().second - 1;
						Pozitii.push(temp);
					}
					Pozitii.pop();
				}
				if (max.first < nr)
				{
					max.first = nr;
					max.second = nr2;
				}
			
			}
	cout << "Numarul de camere este de:" << nr2 << endl;
	cout << "Camera cu suprafata maxima este camera " << max.second << " cu " << max.first << " spatii" << endl;
}
	void afisarelabirint(int nr_linii, int nr_coloane, int** matrice)
	{
		for (int index1 = 0; index1 < nr_linii; index1++)
		{
			cout << endl;
			for (int index2 = 0; index2 < nr_coloane; index2++)
			{
				if (matrice[index1][index2] != -1 && matrice[index1][index2] < 10)
					cout << " ";
				cout << matrice[index1][index2] << " ";
			}

		}
		delete[] matrice[0];
		delete[]matrice;
	}
	int main()
	{
		int** matrice, nr_linii, nr_coloane;
		queue <pair<int, int>> Pozitii;
		string filepath = "Etaj.txt";
		citire_vector_fisier(filepath, nr_linii, nr_coloane, matrice);
		parcurgereetaj(matrice, Pozitii, nr_linii, nr_coloane);
		afisarelabirint(nr_linii, nr_coloane, matrice);
		return 0;
	}