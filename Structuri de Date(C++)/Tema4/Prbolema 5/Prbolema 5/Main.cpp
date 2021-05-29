#include <iostream>
#include<fstream>
#include <queue>
using namespace std;
class nod
{
public:
	pair<int, int> coordonate;
	int distanta;
	nod* parinte;
	nod(int x = 0, int y = 0, int d = 0)
	{
		coordonate.first = x;
		coordonate.second = y;
		distanta = d;
		parinte = nullptr;
	}
};
class Comparator
{
public:
	int operator()(nod*& n1, nod*& n2)
	{
		return n1->distanta > n2->distanta;
	}
};
void citire_labirint_fisier(string filepath, int& nr_linii, int& nr_coloane, int**& matrice)
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
void BordareLabirint(int nr_linii, int nr_coloane, int** matrice1, int**& matrice2)
{
	matrice2 = new int* [nr_linii + 2];
	matrice2[0] = new int[(nr_linii + 2) * (nr_coloane + 2)];
	for (int index = 1; index < nr_linii + 2; index++)
		matrice2[index] = matrice2[index - 1] + nr_coloane + 2;
	for (int index1 = 1; index1 < nr_linii + 1; index1++)
		for (int index2 = 1; index2 < nr_coloane + 1; index2++)
			matrice2[index1][index2] = matrice1[index1 - 1][index2 - 1];
	for (int index = 0; index < nr_coloane + 2; index++)
		matrice2[0][index] = 1;
	for (int index = 1; index < nr_linii + 2; index++)
		matrice2[index][nr_coloane + 1] = 1;
	for (int index = nr_coloane; index >= 0; index--)
		matrice2[nr_linii + 1][index] = 1;
	for (int index = nr_linii; index > 0; index--)
		matrice2[index][0] = 1;
	delete[]matrice1[0];
	delete[]matrice1;

}
void AfisareLabirint(int nr_linii, int nr_coloane, int** matrice)
{
	for (int index1 = 0; index1 < nr_linii; index1++)
	{
		cout << endl;
		for (int index2 = 0; index2 < nr_coloane; index2++)
			cout << matrice[index1][index2] << " ";
	}
	cout << endl;

}

int Distance(nod* curent, nod* vecin, nod* Branza)
{
	int g = abs(curent->coordonate.first - vecin->coordonate.first) + abs(curent->coordonate.second - vecin->coordonate.second);
	int h = abs(Branza->coordonate.first - vecin->coordonate.first) + abs(Branza->coordonate.second - vecin->coordonate.second);
	int f = g + h;
	return f;
}

nod* CreareNod(int x, int y)
{
	nod* nou = new nod;
	nou->coordonate.first = x;
	nou->coordonate.second = y;
	return nou;
}
bool NewPath(nod* curent, nod* vecin, nod* branza)
{
	if (vecin == nullptr)
		return false;
	if (Distance(curent, vecin, branza) < vecin->distanta)
		return true;
	return false;
}
pair<int, int> Vecin(int index, int x, int y)
{
	pair<int, int> temp;
	switch (index)
	{
	case 1:
	{
		temp.first = x - 1;
		temp.second = y;
		return temp;
		break;
	}
	case 2:
	{
		temp.first = x - 1;
		temp.second = y + 1;
		return temp;
		break;
	}
	case 3:
	{
		temp.first = x;
		temp.second = y + 1;
		return temp;
		break;
	}
	case 4:
	{
		temp.first = x + 1;
		temp.second = y + 1;
		return temp;
		break;
	}
	case 5:
	{
		temp.first = x + 1;
		temp.second = y;
		return temp;
		break;
	}
	case 6:
	{
		temp.first = x + 1;
		temp.second = y - 1;
		return temp;
		break;
	}
	case 7:
	{
		temp.first = x;
		temp.second = y - 1;
		return temp;
		break;
	}
	case 8:
	{
		temp.first = x - 1;
		temp.second = y - 1;
		return temp;
		break;
	}
	}
	return temp;
}
nod* SearchNod(priority_queue<nod*, vector<nod*>, Comparator> coada, int x, int y)
{
	while (!coada.empty())
	{
		if (coada.top()->coordonate.first == x && coada.top()->coordonate.second == y)
			return coada.top();
		coada.pop();
	}
	return nullptr;
}

void AStar(nod*& rad, int** matrice, pair<int, int>Soarece, pair<int, int>Branza)
{
	priority_queue<nod*, vector<nod*>, Comparator> open, closed;
	nod* nou = CreareNod(Soarece.first, Soarece.second);
	rad = CreareNod(Branza.first, Branza.second);
	open.push(nou);
	int var = 0;
	while (open.empty() == 0)
	{

		nod* curent = open.top();
		open.pop();
		closed.push(curent);
		if (curent == rad)
		{
			var = 1;
			break;
		}
		for (int index = 1; index <= 8; index++)
		{

			pair<int, int>coordonate = Vecin(index, curent->coordonate.first, curent->coordonate.second);
			if (!(matrice[coordonate.first][coordonate.second] == 1 || SearchNod(closed, coordonate.first, coordonate.second) != nullptr))
			{
				if (NewPath(curent, SearchNod(open, coordonate.first, coordonate.second), rad) == true || SearchNod(open, coordonate.first, coordonate.second) == nullptr)
				{

					nod* nou2;
					if (coordonate.first == rad->coordonate.first && coordonate.second == rad->coordonate.second)
					{

						nou2 = rad;
						nou2->parinte = curent;
					}
					else
					{
						nou2 = CreareNod(coordonate.first, coordonate.second);
						nou2->distanta = Distance(curent, nou2, rad);
						nou2->parinte = curent;
					}
					if (SearchNod(open, coordonate.first, coordonate.second) == nullptr)
					{
						open.push(nou2);
					}
				}

			}
		}

	}
	if (var == 0)
		rad = nullptr;
	delete[] matrice[0];
	delete[] matrice;


}
void AfisareDrum(nod* rad)
{
	if (rad == nullptr)
		cout << "Nu exista drum!";
	else
	{
		cout << "Drumul de la Branza la Soarece este urmatorul:";
		while (rad)
		{
			cout << "(" << rad->coordonate.first << "," << rad->coordonate.second << ")" << " ";
			rad = rad->parinte;
		}
	}
}


int main()
{
	string filepath = "Labirint.txt";
	int** matrice, ** matrice2, nrlinii, nrcoloane, var = 0;
	pair<int, int>Soarece, Branza;
	nod* rad;
	citire_labirint_fisier(filepath, nrlinii, nrcoloane, matrice);
	AfisareLabirint(nrlinii, nrcoloane, matrice);
	try
	{
		cout << "Introduceti coordonatele Soarecelui(incepand de la 1):";
		cin >> Soarece.first >> Soarece.second;
		if (Soarece.first > nrlinii || Soarece.first<1 || Soarece.second>nrcoloane || Soarece.second < 1)
			throw 2;
		else
			if (matrice[Soarece.first - 1][Soarece.second - 1] == 1)
				throw 1;
		cout << "Introduceti coordonatele Branzei(incepand de la 1):";
		cin >> Branza.first >> Branza.second;
		if (Branza.first > nrlinii || Branza.first<1 || Branza.second>nrcoloane || Branza.second < 1)
			throw 4;
		else
			if (matrice[Branza.first - 1][Branza.second - 1] == 1)
				throw 3;

	}
	catch (const int x)
	{
		switch (x)
		{
		case 1:
		{
			var = 1;
			cout << "Coordonatele " << Soarece.first << " si " << Soarece.second << " reprezinta un zid!";
			break;
		}
		case 2:
		{
			var = 1;
			cout << "Coordonatele " << Soarece.first << " si " << Soarece.second << " nu se afla in labirint!";
			break;
		}
		case 3:
		{
			var = 1;
			cout << "Coordonatele " << Branza.first << " si " << Branza.second << " reprezinta un zid!";
			break;
		}
		case 4:
		{
			var = 1;
			cout << "Coordonatele " << Branza.first << " si " << Branza.second << " nu se afla in labirint!";
			break;
		}
		}
	}
	if (var != 1)
	{
		BordareLabirint(nrlinii, nrcoloane, matrice, matrice2);
		AStar(rad, matrice2, Soarece, Branza);
		AfisareDrum(rad);
	}

}
