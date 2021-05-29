#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
class nod
{
public:
	char caracter;
	int frecventa;
	nod* st;
	nod* dr;
	nod(char k = ' ', int m = 0)
	{
		caracter = k;
		frecventa = m;
		st = dr = nullptr;
	}
};
class PRIORITY_QUEUE
{
private:
	vector <nod*> Data;
public:
	void MinHeap(int index)
	{
		int st = index * 2 + 1, dr = index * 2 + 2;
		int imin = index;
		if (st < Data.size() && Data[st]->frecventa < Data[index]->frecventa)
			imin = st;
		if (dr < Data.size() && Data[dr]->frecventa < Data[imin]->frecventa)
			imin = dr;
		if (imin != index)
		{
			nod* aux = Data[index];
			Data[index] = Data[imin];
			Data[imin] = aux;
			MinHeap(imin);
		}
	}

	void ConstrHeap()
	{
		for (int index = Data.size() / 2 - 1; index >= 0; index--)
			MinHeap(index);
	}
	bool IsTwo()
	{
		if (Data.size() > 1)
			return true;
		return false;

	}
	void Insert(nod* k)
	{
		Data.push_back(k);
		ConstrHeap();
	}
	void Pop()
	{
		Data[0] = Data[Data.size() - 1];
		Data.pop_back();
		ConstrHeap();
	}
	nod* ExtractMin()
	{
		nod* min = new nod;
		min = Data[0];
		Data[0] = Data[Data.size() - 1];
		Data.pop_back();
		MinHeap(0);
		return min;
	}
	void Print()
	{
		for (int index = 0; index < Data.size(); index++)
			cout << Data[index]->caracter << " ";
		cout << endl;
		for (int index = 0; index < Data.size(); index++)
			cout << Data[index]->frecventa << " ";
	}
};

class ArboreH
{
private:
	nod* rad;
	PRIORITY_QUEUE coada;
	vector<pair<char, string>>codes;
	string line;
public:
	nod* GetRad()
	{
		return rad;
	}
	ArboreH()
	{
		rad = nullptr;
	}
	void CitireFisier()
	{
		int* frecventa = new int[128];
		for (int index = 0; index < 128; index++)
			frecventa[index] = 0;
		ifstream myfile("Huffman.txt");
		getline(myfile, line);
		if (myfile.is_open())
		{

			for (int i = 0; i < line.size(); i++)
				frecventa[line[i]]++;
			for (int index = 0; index < 128; index++)
				if (frecventa[index] != 0)
				{
					nod* nou = new nod(index,frecventa[index]);
					coada.Insert(nou);
				}


			myfile.close();
		}
		else
			perror("Unable to open the file!");


	}
	void CreareArboreHuffman()
	{
		while (coada.IsTwo() == true)
		{
			pair<nod*, nod*> temp;
			temp.first = coada.ExtractMin();
			temp.second = coada.ExtractMin();
			nod* nou = new nod;
			nou->frecventa = temp.first->frecventa + temp.second->frecventa;
			nou->st = temp.first;
			nou->dr= temp.second;
			coada.Insert(nou);
			rad = nou;
		}
	}

	int inaltime(nod* y)
	{

		int s = 0;
		int d = 0;

		if (y == NULL)
		{
			return 0;
		}
		{
			s = inaltime(y->st);
			d = inaltime(y->dr);
			if (s > d || s == d)
			{
				return (s + 1);
			}
			else
			{
				return (d + 1);
			}
		}
	}
	void GetCodes(nod* x, vector <int> arr, int top)
	{
		if (x->st)
		{
			arr[top] = 0;
			GetCodes(x->st, arr, top + 1);
		}
		if (x->dr)
		{
			arr[top] = 1;
			GetCodes(x->dr, arr, top + 1);
		}
		if (!(x->st) && !(x->dr))
		{

			string var;
			for (int i = 0; i < top; i++)
				var.push_back(arr[i]);
			pair<char, string> temp(x->caracter, var);
			codes.push_back(temp);

		}


	}
	void SearchCodes(char c)
	{
		for (int i = 0; i < codes.size(); i++)
			if (codes[i].first == c)
			{
				for (int j = 0; j < codes[i].second.size(); j++)
					cout << int(codes[i].second[j]);
				cout << ".";
			}
	}


	void PrintCodes()
	{
		for (int i = 0; i < codes.size(); i++)
		{
			cout << "Codul lui " << codes[i].first << " este:";
			for (int j = 0; j < codes[i].second.size(); j++)
				cout << int(codes[i].second[j]);
			cout << endl;
		}
		cout << "Textul este codificat astfel:";
		for (int i = 0; i < line.size(); i++)
			SearchCodes(line[i]);
		cout << "\b";

	}

};
int main()
{
	ArboreH arb;
	vector<int> arr;
	int top = 0;
	arb.CitireFisier();
	arb.CreareArboreHuffman();
	arr.resize(arb.inaltime(arb.GetRad()));
	arb.GetCodes(arb.GetRad(), arr, top);
	arb.PrintCodes();

	return 0;


}