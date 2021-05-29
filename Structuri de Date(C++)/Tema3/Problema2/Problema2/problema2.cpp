#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct Graf
{
	vector<int> noduri;
};
void citire_lista_fisier(string filepath, int& nr_noduri, Graf*& lista)
{
	int index1;
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		myfile >> nr_noduri;
		lista = new Graf[nr_noduri];
		for (index1 = 0; index1 < nr_noduri; index1++)
		{
			int number;
			while (myfile>>number)
			{
				lista[index1].noduri.push_back(number);
				if (myfile.peek() == '\n')
					break;
				
			}
		}
		myfile.close();
	}
	else
		cout << "Unable to open the file";
}
void afisarelist(Graf* lista, int nr_noduri)
{
	for (int index = 0; index < nr_noduri; index++)
	{
		for (int index1 = 0; index1 < lista[index].noduri.size(); index1++)
			cout << lista[index].noduri[index1] << " ";
		cout << endl;
	}
}
bool gasit(Graf vector, int size, int val)
{
	for (int index = 0; index < size; index++)
		if (vector.noduri[index] == val)
			return true;
	return false;

}
void Transformaregrafneorientat(Graf*& lista, int nr_noduri)
{
	for (int index = 0; index < nr_noduri; index++)
		for (int index1 = 1; index1 < lista[index].noduri.size(); index1++)
		{
			if (gasit(lista[lista[index].noduri[index1]], lista[lista[index].noduri[index1]].noduri.size(), index) == false)
				lista[lista[index].noduri[index1]].noduri.push_back(index);
		}



}
void Componenteconexe(Graf* lista, int nr_noduri)
{
	int* vizitat = new int[nr_noduri];
	for (int index = 0; index < nr_noduri; index++)
		vizitat[index] = 0;
	queue<int> Varfuri;
	cout << "Componentele conexe sunt:";
	for (int index = 0; index < nr_noduri; index++)
	{
		if (vizitat[index] == 0)
		{
			Varfuri.push(index);
			vizitat[index] = 1;
			cout << "(" << index;
			while (Varfuri.empty() == 0)
			{
				for (int index1 = 1; index1 < lista[Varfuri.front()].noduri.size(); index1++)
					if (vizitat[lista[Varfuri.front()].noduri[index1]] == 0)
					{
						Varfuri.push(lista[Varfuri.front()].noduri[index1]);
						vizitat[lista[Varfuri.front()].noduri[index1]] = 1;
						cout << "," << lista[Varfuri.front()].noduri[index1];
					}
				Varfuri.pop();
			}
			cout << ") ";

		}


	}
	delete[] vizitat;

}

int main()
{
	Graf* lista;
	string filepath = "Graf.txt";
	int nr_noduri;
	citire_lista_fisier(filepath, nr_noduri, lista);
	afisarelist(lista, nr_noduri);
	Transformaregrafneorientat(lista, nr_noduri);
	Componenteconexe(lista, nr_noduri);
	return 0;
}