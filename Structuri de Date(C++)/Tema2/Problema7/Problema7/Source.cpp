#include <iostream>
#include<fstream>
#include <queue>
#include <stack>
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
void bordarelabirint(int nr_linii, int nr_coloane, int** matrice1, int**& matrice2)
{
	matrice2 = new int* [nr_linii + 2];
	matrice2[0] = new int[(nr_linii + 2) * (nr_coloane + 2)];
	for (int index = 1; index < nr_linii + 2; index++)
		matrice2[index] = matrice2[index - 1] + nr_coloane + 2;
	for (int index1 = 1; index1 < nr_linii + 1; index1++)
		for (int index2 = 1; index2 < nr_coloane + 1; index2++)
			matrice2[index1][index2] = matrice1[index1 - 1][index2 - 1];
	for (int index = 0; index < nr_coloane + 2; index++)
		matrice2[0][index] = -1;
	for (int index = 1; index < nr_linii + 2; index++)
		matrice2[index][nr_coloane + 1] = -1;
	for (int index = nr_coloane; index >= 0; index--)
		matrice2[nr_linii + 1][index] = -1;
	for (int index = nr_linii; index > 0; index--)
		matrice2[index][0] = -1;
	delete[]matrice1[0];
	delete[]matrice1;

}
void parcurgerelabirint(int** matrice, queue <pair<int, int>>& Pozitii, pair<int, int> Branza)
{
	bool var = true;
	matrice[Pozitii.front().first][Pozitii.front().second] = 1;
	while (var != false && Pozitii.empty() == 0)
	{
		if (matrice[Pozitii.front().first + 1][Pozitii.front().second] == 0)
		{
			if (Pozitii.front().first + 1 == Branza.first && Pozitii.front().second == Branza.second)
			{
				matrice[Branza.first][Branza.second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
				var = false;
				break;
			}
			matrice[Pozitii.front().first + 1][Pozitii.front().second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
			pair<int, int> temp;
			temp.first = Pozitii.front().first + 1;
			temp.second = Pozitii.front().second;
			Pozitii.push(temp);
		}
		if (matrice[Pozitii.front().first][Pozitii.front().second + 1] == 0)
		{
			if (Pozitii.front().first == Branza.first && Pozitii.front().second + 1 == Branza.second)
			{
				matrice[Branza.first][Branza.second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
				var = false;
				break;
			}
			matrice[Pozitii.front().first][Pozitii.front().second + 1] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
			pair<int, int> temp;
			temp.first = Pozitii.front().first;
			temp.second = Pozitii.front().second + 1;
			Pozitii.push(temp);
		}
		if (matrice[Pozitii.front().first - 1][Pozitii.front().second] == 0)
		{
			if (Pozitii.front().first - 1 == Branza.first && Pozitii.front().second == Branza.second)
			{
				matrice[Branza.first][Branza.second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
				var = false;
				break;

			}
			matrice[Pozitii.front().first - 1][Pozitii.front().second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
			pair<int, int> temp;
			temp.first = Pozitii.front().first - 1;
			temp.second = Pozitii.front().second;
			Pozitii.push(temp);
		}
		if (matrice[Pozitii.front().first][Pozitii.front().second - 1] == 0)
		{
			if (Pozitii.front().first == Branza.first && Pozitii.front().second - 1 == Branza.second)
			{
				matrice[Branza.first][Branza.second] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
				var = false;
				break;
			}
			matrice[Pozitii.front().first][Pozitii.front().second - 1] = matrice[Pozitii.front().first][Pozitii.front().second] + 1;
			pair<int, int> temp;
			temp.first = Pozitii.front().first;
			temp.second = Pozitii.front().second - 1;
			Pozitii.push(temp);
		}
		Pozitii.pop();
	}

}

void drumminim(int** matrice, stack <pair<int, int>>& drum)
{
	while (matrice[drum.top().first][drum.top().second] > 1)
	{
		if (matrice[drum.top().first - 1][drum.top().second] == matrice[drum.top().first][drum.top().second] - 1)
		{
			pair<int, int>temp;
			temp.first = drum.top().first - 1;
			temp.second = drum.top().second;
			drum.push(temp);
		}
		else
			if (matrice[drum.top().first][drum.top().second - 1] == matrice[drum.top().first][drum.top().second] - 1)
			{
				pair<int, int>temp;
				temp.first = drum.top().first;
				temp.second = drum.top().second - 1;
				drum.push(temp);
			}
			else
				if (matrice[drum.top().first + 1][drum.top().second] == matrice[drum.top().first][drum.top().second] - 1)
				{
					pair<int, int>temp;
					temp.first = drum.top().first + 1;
					temp.second = drum.top().second;
					drum.push(temp);
				}
				else
					if (matrice[drum.top().first][drum.top().second + 1] == matrice[drum.top().first][drum.top().second] - 1)
					{
						pair<int, int>temp;
						temp.first = drum.top().first;
						temp.second = drum.top().second + 1;
						drum.push(temp);
					}
	}
	delete[]matrice[0];
	delete[]matrice;

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
}
void afisaredrumminim(stack <pair<int, int>>drum)
{
	cout << "Drumul cel mai scurt este reprezentat de urmatoarele coordonate:" << endl;
	while (drum.empty() != 1)
	{
		cout << "(" << drum.top().first - 1 << "," << drum.top().second - 1 << ")" << endl;
		drum.pop();
	}
}

int main()
{
	string filepath = "Labirint.txt";
	queue <pair<int, int>> Pozitii;
	stack <pair<int, int>> Drum;
	int** matrice, ** matrice2;
	int nr_linii, nr_coloane;
	pair<int, int> Soarece, Branza;
	citire_vector_fisier(filepath, nr_linii, nr_coloane, matrice);
	afisarelabirint(nr_linii, nr_coloane, matrice);
	cout << endl;
	cout << "Introduceti coordonatele soarecelui si a branzei in labirint:";
	cin >> Soarece.first >> Soarece.second >> Branza.first >> Branza.second;
	Soarece.first++;
	Soarece.second++;
	Branza.first++;
	Branza.second++;
	bordarelabirint(nr_linii, nr_coloane, matrice, matrice2);
	Pozitii.push(Soarece);
	parcurgerelabirint(matrice2, Pozitii, Branza);
	if (Pozitii.empty() == 1)
		cout << "Nu exista drum accesibil!";
	else
	{
		Drum.push(Branza);
		drumminim(matrice2, Drum);
		afisaredrumminim(Drum);
	}
	return 0;
}