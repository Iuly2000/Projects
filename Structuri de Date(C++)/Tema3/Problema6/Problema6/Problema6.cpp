#include<iostream>
#include<queue>
#include<string>
#include<fstream>

struct nod {

	int info;
	nod* st, * dr, * p;
	nod(int k = 0)
	{
		info = k;
		st = dr = p = nullptr;
	}
};

struct arbore {
	nod* rad;
	arbore()
	{
		rad = nullptr;
	}

	void citeste(std::string filename)
	{
		std::ifstream f;
		f.open(filename);
		int info;
		int copii;
		nod* nod_curent;
		std::queue<std::pair<nod*, int>> C;
		std::pair<nod*, int> curent; 
		f >> info;
		f >> copii;
		rad = new nod(info);
		C.push(std::pair<nod*, int>(rad, copii)); 
		while (!C.empty())
		{
			nod* stanga = nullptr, * dreapta = nullptr;
			curent = C.front(); 
			C.pop();

			nod_curent = curent.first;
			if (curent.second == -1 || curent.second == 2) 
			{
				f >> info;
				f >> copii;
				stanga = new nod(info);
				stanga->p = nod_curent;
				C.push(std::pair<nod*, int>(stanga, copii));
			}
			if (curent.second == 1 || curent.second == 2) 
			{
				f >> info;
				f >> copii;
				dreapta = new nod(info);
				dreapta->p = nod_curent;
				C.push(std::pair<nod*, int>(dreapta, copii));
			}
			nod_curent->st = stanga;
			nod_curent->dr = dreapta;
		}



		f.close();
	}
	void RSD(nod* x)
	{
		if (x)
		{
			std::cout << x->info << " ";
			RSD(x->st);
			RSD(x->dr);
		}
	}
	int inaltime(nod* y)
	{

		int s = 0;
		int d = 0;

		if (y== NULL)
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
};

int main()
{
	arbore A;
	A.citeste("Text1.txt");
	A.RSD(A.rad);
	std::cout << std::endl;
	std::cout << "Inaltimea arborelui este:" << A.inaltime(A.rad);
}
