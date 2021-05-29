#include<iostream>
#include<stack>
#include <queue>
#include<string>
#include<fstream>
using namespace std;
struct nod {

	int info;
	nod* st, * dr, * p;
	nod(int k = 0)
	{
		info = k;
		st = dr = p = nullptr;
	}
};
void stergere(int k, int* vector, int& n)
{
	int i;
	for (i = k; i <= n - 2; i++)
		vector[i] = vector[i + 1];
	n--;
}
int cautare(int k, int* vector, int n)
{
	for (int index = 0; index < n; index++)
		if (k == vector[index])
			return index;
	return -1;

}
struct arbore {
	nod* rad;
	arbore()
	{
		rad = nullptr;
	}

	void citeste(std::string filename)
	{
		ifstream f;
		f.open(filename);
		stack <nod*> S;
		queue<nod*>C;
		int* RSD, * SRD;
		int info, contor = 0;
		f >> info;
		RSD = new int[info];
		SRD = new int[info];
		for (int i = 0; i < info; i++)
			f >> RSD[i];
		for (int i = 0; i < info; i++)
			f >> SRD[i];
		cout << endl;
		int size = info;
		int poz = 0;
		int elemdr = RSD[cautare(RSD[0], SRD, size) + 1];
		rad = new nod(RSD[0]);
		nod* curent = rad;
		int pozanterior;
		int sizefix = size;
		while (contor < sizefix)
		{
			int pozSRD = cautare(RSD[0], SRD, size);
			if (pozSRD == 0)
			{
				curent->st = nullptr;
			}
			else
			{
				nod* nou = new nod(RSD[1]);
				curent->st = nou;
				nou->p = curent;
				C.push(nou);
			}
			if (elemdr == RSD[0])
				poz = 0;
			if (poz == 0)
			{
				poz = 1;
				if (pozSRD < size - 1)
				{
					nod* nou = new nod(RSD[pozSRD + 1]);
					curent->dr = nou;
					nou->p = curent;
					S.push(nou);
				}
				else
					curent->dr = nullptr;
			}
			else
				if (pozSRD < pozanterior - 1)
				{
					nod* nou = new nod(RSD[pozSRD + 1]);
					curent->dr = nou;
					nou->p = curent;
					S.push(nou);
				}
				else
					curent->dr = nullptr;
			stergere(0, RSD, size);
			size++;
			stergere(pozSRD, SRD, size);
			if (C.empty() == 0 || S.empty() == 0)
				if (C.empty() == 0)
				{
					curent = C.front();
					C.pop();
				}
				else
				{
					curent = S.top();
					S.pop();
				}


			pozanterior = pozSRD;
			contor++;
		}
		f.close();
		delete[]RSD;
		delete[]SRD;
	}
	void RSD(nod* x)
	{
		if (x)
		{
			cout << x->info << " ";
			RSD(x->st);
			RSD(x->dr);
		}
	}
	void SDR(nod* x)
	{
		if (x)
		{
			SDR(x->st);
			cout << x->info << " ";
			SDR(x->dr);
		}
	}
	void DSR(nod* x)
	{
		if (x)
		{
			DSR(x->st);
			DSR(x->dr);
			cout << x->info << " ";
		}
	}
};

int main()
{
	string filename = "Text1.txt";
	arbore A;
	A.citeste(filename);
	A.RSD(A.rad);
	cout << endl;
	A.SDR(A.rad);
	cout << endl;
	A.DSR(A.rad);
	return 0;
}