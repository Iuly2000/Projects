#include <iostream>
using namespace std;
struct Nod
{
	int info;
	Nod* urm;

};

struct Lista
{
	Nod* cap;
	Lista()
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
	Nod* Search(int k)
	{
		Nod* copy = cap;
		while (copy != NULL && copy->info != k)
			copy = copy->urm;
		return copy;

	}
	void Delete(int k)
	{
		if (Search(k) == NULL)
			cout << "Elementul " << k << " nu se afla in lista." << endl;
		else
		{
			Nod* temp = Search(k);
			if (temp == cap)
				cap = cap->urm;
			else
			{
				Nod* copy = cap;
				while (copy->urm != temp)
					copy = copy->urm;
				copy->urm = temp->urm;
			}
			delete temp;
		}
	}

	bool Isempty()
	{
		if (cap == NULL)
			return true;
		return false;
	}
	void Swap(Nod* x, Nod* y)
	{
		if (Search(x->info) == NULL || Search(y->info) == NULL)
			cout << "Cel putin un nod nu face parte din lista." << endl;
		else
		{
			x = Search(x->info);
			y = Search(y->info);
			int aux = x->info;
			x->info = y->info;
			y->info = aux;
			
		}

	}
	void Sort()
	{
		for (Nod* index1 = cap; index1->urm!= NULL; index1 = index1->urm)
			for (Nod* index2 = index1->urm; index2!= NULL; index2=index2->urm)
				if (index1->info > index2->info)
				{

					int aux = index1->info;
					index1->info = index2->info;
					index2->info = aux;

				}


	}
	void Insert_Before(int k, int m)
	{
		if (Search(m) == NULL)
			cout << "Nodul " << m << " nu se afla in lista.";
		else
		if (cap->info == m || Isempty() == 1)
			Insert(k);
		else
		{
			Nod* copy = cap;
			while (copy->urm != NULL)
			{
				if (copy->urm->info == m)
				{
					Nod* nou = new Nod;
					nou->info = k;
					nou->urm = copy->urm;
					copy->urm = nou;
					copy = copy->urm->urm;
					break;
				}
				copy = copy->urm;
			}

		}

	}
	void Print_List()
	{
		Nod* copy = cap;
		while (copy != NULL)
		{
			cout << copy->info << " ";
			copy = copy->urm;
		}
	}
};

int main()
{
	Lista test;
	int input = -1;
	cout << "0.EXIT" << endl;
	cout << "1.Insert(insereaza un element in capul listei.)" << endl;
	cout << "2.Search(cauta un element in lista.)" << endl;
	cout << "3.Delete(sterge un element din lista.)" << endl;
	cout << "4.Isempty(verifica daca lista este goala.)" << endl;
	cout << "5.Swap(schimba 2 elemente din lista intre ele.)" << endl;
	cout << "6.Sort(sorteaza lista crescator.)" << endl;
	cout << "7.Insert_Before(insereaza un element in lista iantea altui element specificat.)" << endl;
	cout << "8.Print_List(afiseaza lista.)" << endl;
	while (input != 0)
	{
		int k, m;
		cin >> input;
		switch (input)
		{
		case 0:break;
		case 1:
		{
			cout << "Introduceti un numar:";
			cin >> k;
			test.Insert(k);
			break;
		}
		case 2:
		{
			cout << "Introduceti un numar:";
			cin >> k;
			if (test.Search(k) != NULL)
				cout <<"Numarul "<<test.Search(k)->info <<" a fost gasit!"<< endl;
			else
				cout << "Numarul nu a fost gasit in lista!" << endl;
			break;
		}
		case 3:
		{
			cout << "Introduceti un numar:";
			cin >> k;
			test.Delete(k);
			break;
		}
		case 4:
		{	if (test.Isempty() == 1)
			cout << "Lista este goala!" << endl;
		else
			cout << "Lista nu este goala!" << endl;
		break;
		}
		case 5:
		{
			cout << "Introduceti 2 noduri:";
			cin >> k >> m;
			Nod* nou1 = new Nod;
			Nod* nou2 = new Nod;
			nou1->info = k;
			nou2->info = m;
			test.Swap(nou1, nou2);
			break;
		}
		case 6:
		{
			test.Sort();
			break;
		}
		case 7:
		{
			cout << "Introduceti un numar si nodul inaintea caruia doriti sa il inserati:";
			cin >> k >> m;
			test.Insert_Before(k, m);
			break;
		}
		case 8:
		{
			test.Print_List();
			break;
		}

		}


	}
	return 0;
}