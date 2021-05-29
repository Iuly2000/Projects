#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;
struct Nod
{
	int info;
	Nod* urm;

};

struct Graf
{
	Nod* cap;
	Graf()
	{
		cap = NULL;
	}
	void Insert(int k)
	{
		Nod* nou = new Nod;
		nou->info = k;
		nou->urm = cap;
		cap = nou;
	}
	void Print_Graph()
	{
		Nod* copy = cap;
		while (copy != NULL)
		{
			cout << copy->info << " ";
			copy = copy->urm;
		}
	}
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
			while (myfile >> number)
			{
				if (myfile.peek() == '\n')
				{
					lista[index1].Insert(number);
					break;
				}
				else
					lista[index1].Insert(number);
			}
		}
		myfile.close();
	}
	else
		cout << "Unable to open the file";

}
bool existadrum(int& nodx, int& nody, Graf* lista, int nr_noduri)
{
	queue <Nod*> coada;
	cout << "Introduceti primul nod:";
	cin >> nodx;
	cout << "Introduceti al doilea nod:";
	cin >> nody;
	int* marcaj = new int[nr_noduri];
	for (int index = 0; index < nr_noduri; index++)
		marcaj[index] = 0;
	if (lista[nodx - 1].cap->info == nody)
		return true;
	coada.push(lista[nodx - 1].cap);
	marcaj[nodx - 1] = 1;
	while (coada.empty() == 0)
	{
		while (lista[coada.front()->info - 1].cap->urm != NULL)
		{
			if (lista[coada.front()->info - 1].cap->urm->info == nody)
				return true;
			if (marcaj[lista[coada.front()->info - 1].cap->urm->info - 1] == 0)
			{
				marcaj[lista[coada.front()->info - 1].cap->urm->info - 1] = 1;
				coada.push(lista[coada.front()->info - 1].cap->urm);
			}
			lista[coada.front()->info - 1].cap = lista[coada.front()->info - 1].cap->urm;
		}
		coada.pop();

	}
	delete[] marcaj;
	return false;

}



int main()
{
	Graf* lista;
	int nr_noduri, nodx, nody;
	string filepath = "Graf.txt";
	citire_lista_fisier(filepath, nr_noduri, lista);
	for (int index = 0; index < nr_noduri; index++)
	{
		lista[index].Print_Graph();
		cout << endl;
	}
	if (existadrum(nodx, nody, lista, nr_noduri) == true)
		cout << "Exista drum!";
	else
		cout << "Nu exista drum!";

	return 0;
}

