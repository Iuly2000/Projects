#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
struct Nod
{
	int info;
	Nod* tata;
	Nod* fiu;
	Nod* frate;
	Nod(int k = 0)
	{
		info = k;
		tata = nullptr;
		fiu = nullptr;
		frate = nullptr;
	}
};
bool cautare(vector<Nod*> vector, int k)
{
	for (int index = 0; index < vector.size(); index++)
		if (vector[index]->info == k)
			return true;
	return false;
}
struct Arbore
{
	Nod* rad;
	Arbore()
	{
		rad = nullptr;
	}
	void citire_graf_fisier(string filepath)
	{
		ifstream myfile(filepath);
		if (myfile.is_open())
		{
			int info, copii;
			queue<Nod*>C;
			Nod* curent;
			myfile >> info;
			rad = new Nod(info);
			C.push(rad);
			rad->tata = nullptr;
			rad->frate = nullptr;
			while (!C.empty())
			{
				curent = C.front();
				C.pop();
				myfile >> copii;
				if (copii == 0)
					curent->fiu = nullptr;
				else
				{
					Nod* anterior = nullptr;
					int fiu = 0;
					for (int index = 0; index < copii; index++)
					{

						myfile >> info;
						Nod* nou = new Nod(info);
						C.push(nou);
						if (fiu == 0)
						{
							curent->fiu = nou;
							fiu = 1;
						}
						nou->tata = curent;
						if (anterior != nullptr)
							anterior->frate = nou;
						anterior = nou;
					}
				}

			}

			myfile.close();
		}
		else
			cout << "Unable to open the file";

	}

	void printadancime(Nod* x)
	{
		while (x != nullptr)
		{
			cout << x->info << " ";
			if (x->fiu != nullptr)
				printadancime(x->fiu);
			x = x->frate;
		}



	}
};

int main()
{
	Arbore tree;
	string filepath = "Arborenar.txt";
	int nr_noduri;
	tree.citire_graf_fisier(filepath);
	tree.printadancime(tree.rad);
	return 0;

}