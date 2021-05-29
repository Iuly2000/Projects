#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
void citire_graf_fisier(string filepath, int& nr_noduri, int**& graf)
{
	ifstream myfile(filepath);
	if (myfile.is_open())
	{
		myfile >> nr_noduri;
		graf = new int* [nr_noduri];
		graf[0] = new int[nr_noduri * nr_noduri];
		for (int index = 1; index < nr_noduri; index++)
			graf[index] = graf[index - 1] + nr_noduri;
		for (int index1 = 0; index1 < nr_noduri; index1++)
			for (int index2 = 0; index2 < nr_noduri; index2++)
			{
				char number;
				myfile >> number;
				if (number == '+')
					graf[index1][index2] = 99999;
				else
					graf[index1][index2] = atoi(&number);

			}
		myfile.close();
	}
	else
		cout << "Unable to open the file";

}
void DrumMinim(int**& graf, int**& predecesor, int nr_noduri, int k)
{
	int** copie;
	predecesor = new int* [nr_noduri];
	predecesor[0] = new int[nr_noduri * nr_noduri];
	for (int index = 1; index < nr_noduri; index++)
		predecesor[index] = predecesor[index - 1] + nr_noduri;
	copie = new int* [nr_noduri];
	copie[0] = new int[nr_noduri * nr_noduri];
	for (int index = 1; index < nr_noduri; index++)
		copie[index] = copie[index - 1] + nr_noduri;
	for (int index1 = 0; index1 < nr_noduri; index1++)
		for (int index2 = 0; index2 < nr_noduri; index2++)
			copie[index1][index2] = graf[index1][index2];
	if (k == 0)
		for (int index1 = 0; index1 < nr_noduri; index1++)
			for (int index2 = 0; index2 < nr_noduri; index2++)
				if (graf[index1][index2] != 99999)
					predecesor[index1][index2] = index1 + 1;
				else
					predecesor[index1][index2] = 99999;
	else
	{
		DrumMinim(copie, predecesor, nr_noduri, k - 1);
		for (int index1 = 0; index1 < nr_noduri; index1++)
			for (int index2 = 0; index2 < nr_noduri; index2++)
			{
				int var = copie[index1][index2];
				graf[index1][index2] = min(copie[index1][index2], copie[index1][k] + copie[k][index2]);
				if (var != graf[index1][index2])
					predecesor[index1][index2] = k + 1;
			}
	}

}
void afisaregraf(int** graf, int nr_noduri)
{
	for (int index1 = 0; index1 < nr_noduri; index1++)
	{
		cout << endl;
		for (int index2 = 0; index2 < nr_noduri; index2++)
			cout << graf[index1][index2] << " ";
	}
}
int main()
{
	int** graf, ** predecesor, nr_noduri, nodinitial, nodfinal;
	string filepath = "Graf3.txt";
	citire_graf_fisier(filepath, nr_noduri, graf);
	afisaregraf(graf, nr_noduri);
	cout << endl;
	cout << "Introduceti nodul de plecare:";
	cin >> nodinitial;
	cout << "Introduceti nodul de sosire:";
	cin >> nodfinal;
	DrumMinim(graf, predecesor, nr_noduri, nr_noduri - 1);
	afisaregraf(graf, nr_noduri);
	cout << endl;
	afisaregraf(predecesor, nr_noduri);
	cout << endl;
	if (predecesor[nodinitial - 1][nodfinal - 1] == 99999)
		cout << "Nu exista drum de la " << nodinitial << " la " << nodfinal;
	else
	{
		int cost = graf[nodinitial - 1][nodfinal - 1];
		cout << "Cel mai scurt drum dintre " << nodinitial << " si " << nodfinal << " este:";
		cout << "(" << nodfinal << ",";
		while (nodinitial != nodfinal)
		{

			cout << predecesor[nodinitial - 1][nodfinal - 1] << ",";
			nodfinal = predecesor[nodinitial - 1][nodfinal - 1];
		}
		cout << '\b' << ") avand costul de " << cost;
	}

	delete[]graf[0];
	delete[]graf;
	delete[]predecesor[0];
	delete[]predecesor;
	return 0;
}