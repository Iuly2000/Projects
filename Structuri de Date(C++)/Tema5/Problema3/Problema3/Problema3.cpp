#include <iostream>
#include <vector>
using namespace std;
template <class T>
class Nod
{
public:
	T info;
	char culoare;
	Nod<T>* st, * dr, * p;
	Nod<T>(int k = 0)
	{
		info = k;
		culoare = 'R';
		st = dr = p = nullptr;
	}
};
template <class T>
class ARN
{
private:
	Nod<T>* NIL;
	void INSERT_REPARA(Nod<T>* nou)
	{
		Nod<T>* u;
		while (nou->p->culoare == 'R')
			if (nou->p == nou->p->p->st)
			{
				u = nou->p->p->dr;
				if (u->culoare == 'R')
				{
					u->culoare = 'N';
					nou->p->culoare = 'N';
					nou->p->p->culoare = 'R';
					nou = nou->p->p;
				}
				else
				{
					if (nou == nou->p->dr)
					{
						nou = nou->p;
						ROT_ST(nou);
					}
					nou->p->culoare = 'N';
					nou->p->p->culoare = 'R';
					ROT_DR(nou->p->p);
				}

			}
			else
			{
				u = nou->p->p->st;
				if (u->culoare == 'R')
				{
					u->culoare = 'N';
					nou->p->culoare = 'N';
					nou->p->p->culoare = 'R';
					nou = nou->p->p;
				}
				else
				{
					if (nou == nou->p->st)
					{
						nou = nou->p;
						ROT_DR(nou);
					}
					nou->p->culoare = 'N';
					nou->p->p->culoare = 'R';
					ROT_ST(nou->p->p);
				}
			}
		radacina->culoare = 'N';

	}
	void ROT_ST(Nod<T>* y)
	{
		Nod<T>* x = y->dr;
		y->dr = x->st;
		if (x->st != NIL)
			x->st->p = y;
		x->p = y->p;
		if (y->p == NIL)
			radacina = x;
		else
			if (y == y->p->st)
				y->p->st = x;
			else
				y->p->dr = x;
		x->st = y;
		y->p = x;

	}
	void DELETE_REPARA(Nod<T>* x)
	{
		while (x != radacina && x->culoare == 'N')
			if (x == x->p->st)
			{
				Nod<T>* w = x->p->dr;
				if (w->culoare == 'R')
				{
					w->culoare = 'N';
					x->p->culoare = 'R';
					ROT_ST(x->p);
					w = x->p->dr;
				}
				if (w->st->culoare == 'N' && w->dr->culoare == 'N')
				{
					w->culoare = 'R';
					x = x->p;
				}
				else
				{
					if (w->dr->culoare == 'N')
					{
						w->st->culoare = 'N';
						w->culoare = 'R';
						ROT_DR(w);
						w = x->p->dr;
					}
					w->culoare = x->p->culoare;
					x->p->culoare = 'N';
					w->dr->culoare = 'N';
					ROT_ST(x->p);
					x = radacina;
				}
			}
			else
			{
				Nod<T>* w = x->p->st;
				if (w->culoare == 'R')
				{
					w->culoare = 'N';
					x->p->culoare = 'R';
					ROT_DR(x->p);
					w = x->p->st;
				}
				if (w->dr->culoare == 'N' && w->st->culoare == 'N')
				{
					w->culoare = 'R';
					x = x->p;
				}
				else
				{
					if (w->st->culoare == 'N')
					{
						w->dr->culoare = 'N';
						w->culoare = 'R';
						ROT_ST(w);
						w = x->p->st;
					}
					w->culoare = x->p->culoare;
					x->p->culoare = 'N';
					w->st->culoare = 'N';
					ROT_DR(x->p);
					x = radacina;
				}
			}
		x->culoare = 'N';
	}
	void ROT_DR(Nod<T>* y)
	{
		Nod<T>* x = y->st;
		y->st = x->dr;
		if (x->dr != NIL)
			x->dr->p = y;
		x->p = y->p;
		if (y->p == NIL)
			radacina = x;
		else
			if (y == y->p->dr)
				y->p->dr = x;
			else
				y->p->st = x;
		x->dr = y;
		y->p = x;

	}
	void TRANSPLANT(Nod<T>* u, Nod<T>* v)
	{
		if (u->p == NIL)
			radacina = v;
		else
			if (u == u->p->st)
				u->p->st = v;
			else
				u->p->dr = v;
		v->p = u->p;
	}
	int inaltime(Nod<T>* y)
	{

		int s = 0;
		int d = 0;

		if (y == NIL)
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
	void RSD(Nod<T>* x)
	{
		if (x != NIL)
		{
			cout << x->info << x->culoare << " ";
			RSD(x->st);
			RSD(x->dr);
		}
	}
	void SDR(Nod<T>* x)
	{
		if (x != NIL)
		{
			SDR(x->st);
			cout << x->info << x->culoare << " ";
			SDR(x->dr);
		}
	}
	void DSR(Nod<T>* x)
	{
		if (x != NIL)
		{
			DSR(x->st);
			DSR(x->dr);
			cout << x->info << x->culoare << " ";
		}
	}
	void AfisareNivelDat(Nod<T>* nod, int nivel)
	{
		if (nod == NIL)
			return;
		if (nivel == 1)
			cout << nod->info << nod->culoare << " ";
		else
			if (nivel > 1)
			{
				AfisareNivelDat(nod->st, nivel - 1);
				AfisareNivelDat(nod->dr, nivel - 1);
			}
	}
	void AfisarePeNivele(Nod<T>* x)
	{
		int h = inaltime(x);
		for (int index = 1; index <= h; index++)
			AfisareNivelDat(x, index);
	}

public:
	Nod<T>* radacina;
	ARN()
	{
		NIL = new Nod<T>();
		NIL->culoare = 'N';
		NIL->p = NIL->dr = NIL->st = NIL;
		radacina = NIL;
	}
	void INSERT(Nod<T>* nou)
	{
		Nod<T>* y = NIL;
		Nod<T>* x = radacina;
		while (x != NIL)
		{
			y = x;
			if (nou->info < x->info)
				x = x->st;
			else
				x = x->dr;
		}
		nou->p = y;
		if (y == NIL)
			radacina = nou;
		else
			if (nou->info < y->info)
				y->st = nou;
			else
				y->dr = nou;
		nou->st = NIL;
		nou->dr = NIL;
		nou->culoare = 'R';
		INSERT_REPARA(nou);
	}
	void DELETE(Nod<T>* z)
	{
		Nod<T>* y = z, * x;
		char Coriginal = y->culoare;
		if (z->st == NIL)
		{
			x = z->dr;
			TRANSPLANT(z, z->dr);
		}
		else
			if (z->dr == NIL)
			{
				x = z->st;
				TRANSPLANT(z, z->st);
			}
			else
			{
				y = Minim(z->dr);
				Coriginal = y->culoare;
				x = y->dr;
				if (y->p == z)
					x->p = y;
				else
				{
					TRANSPLANT(y, y->dr);
					y->dr = z->dr;
					y->dr->p = y;
				}
				TRANSPLANT(z, y);
				y->st = z->st;
				y->st->p = y;
				y->culoare = z->culoare;
			}
		if (Coriginal == 'N')
			DELETE_REPARA(x);
	}
	void EMPTY()
	{
		if (radacina != NIL)
		{
			Nod<T>* x = radacina->st;
			Nod<T>* y = radacina->dr;
			delete radacina;

			if (x != NIL)
			{
				radacina = x;
				EMPTY();
			}
			if (y != NIL)
			{
				radacina = y;
				EMPTY();
			}
		}
		radacina = NIL;
	}
	Nod<T>* Maxim(Nod<T>* nod)
	{
		if (nod == NIL)
			return nullptr;
		while (nod->dr != NIL)
			nod = nod->dr;
		return nod;
	}
	Nod<T>* Minim(Nod<T>* nod)
	{
		if (nod == NIL)
			return nullptr;
		while (nod->st != NIL)
			nod = nod->st;
		return nod;
	}
	Nod<T>* Succesor(Nod<T>* nod)
	{
		if (nod == Maxim(radacina))
			return nullptr;
		if (nod->dr != NIL)
		{

			Nod<T>* y = Minim(nod->dr);
			return y;
		}
		Nod<T>* y = nod->p;
		while (y != NIL && y->dr == nod)
		{
			nod = y;
			y = y->p;
		}
		return y;


	}
	Nod<T>* Predecesor(Nod<T>* nod)
	{
		if (nod == Minim(radacina))
			return nullptr;
		if (nod->st != NIL)
		{
			Nod<T>* y = Maxim(nod->st);
			return y;
		}
		Nod<T>* y = nod->p;
		while (y != NIL && y->st == nod)
		{
			nod = y;
			y = y->p;
		}
		return y;


	}
	Nod<T>* Search(int x)
	{
		Nod<T>* y = radacina;
		while (y != NIL)
		{
			if (y->info == x)
				return y;
			else
				if (y->info < x)
					y = y->dr;
				else
					y = y->st;
		}
		return nullptr;
	}
	void PRINT_TREE(int opt)
	{
		switch (opt)
		{
		case 1:
		{
			RSD(radacina);
			break;
		}
		case 2:
		{
			SDR(radacina);
			break;
		}
		case 3:
		{
			DSR(radacina);
			break;
		}
		case 4:
		{
			AfisarePeNivele(radacina);
			break;
		}
		}
	}
	void CONSTRUCT(vector < Nod<T>* > arbore)
	{
		for (int index = 0; index < arbore.size(); index++)
			INSERT(arbore[index]);
	}
};



int main()
{
	ARN<int> Arbore;
	int input = -1;
	cout << "0.EXIT" << endl;
	cout << "1.Insert(insereaza un element in arbore.)" << endl;
	cout << "2.Cautare(cauta un nod in arbore.)" << endl;
	cout << "3.Stergere(sterge un nod din arbore.)" << endl;
	cout << "4.Minim(Returneaza nodul cu valoare minima din arbore.)" << endl;
	cout << "5.Maxim(Returneaza nodul cu valoare maxima din arbore.)" << endl;
	cout << "6.Succesor(Afiseaza succesorul unui nod din arbore.)" << endl;
	cout << "7.Predecesor(Afiseaza predecesorul unui nod din arbore.)" << endl;
	cout << "8.Afisare Arbore(Afiseaza continutul arborelui in functie de optiunea aleasa,prima optiune afiseaza arborele in preordine,a doua in inordine,a treia in postordine,iar ultima pe nivele.)" << endl;
	while (input != 0)
	{
		int element;
		cin >> input;
		switch (input)
		{
		case 0:break;
		case 1:
		{
			cout << "Introduceti un element in arbore:";
			cin >> element;
			Nod<int>* nou = new Nod<int>(element);
			Arbore.INSERT(nou);
			break;
		}
		case 2:
		{
			cout << "Introduceti elementul pe care doriti sa il cautati:";
			cin >> element;
			if (Arbore.Search(element) == nullptr)
				cout << "Elementul " << element << " nu a fost gasit in arbore!\n";
			else
				cout << "Elementul " << element << " a fost gasit in arbore!\n";
			break;
		}
		case 3:
		{
			cout << "Introduceti elementul pe care doriti sa il stergeti:";
			cin >> element;
			Arbore.DELETE(Arbore.Search(element));
			break;
		}
		case 4:
		{
			if (Arbore.Minim(Arbore.radacina) == nullptr)
				cout << "Arborele este gol,nu exista element minim.\n";
			else
			{
				cout << "Elementul cu valoarea minima din arbore este:" << Arbore.Minim(Arbore.radacina)->info;
				cout << endl;
			}
			break;
		}
		case 5:
		{
			if (Arbore.Maxim(Arbore.radacina) == nullptr)
				cout << "Arborele este gol,nu exista element maxim.\n";
			else
			{
				cout << "Elementul cu valoarea maxima din arbore este:" << Arbore.Maxim(Arbore.radacina)->info;
				cout << endl;
			}
			break;
		}
		case 6:
		{
			cout << "Introduceti nodul al carui succesor doriti sa il aflati:";
			cin >> element;
			if (Arbore.Search(element) == nullptr)
				cout << "Elementul " << element << " nu se afla in arbore\n";
			else
				if (Arbore.Succesor(Arbore.Search(element)) == nullptr)
					cout << "Elementul " << element << " este elementul maxim din arbore,prin urmare nu are un succesor.";
				else
					cout << "Succesorul elementului " << element << " este " << Arbore.Succesor(Arbore.Search(element))->info;
			cout << endl;
			break;
		}
		case 7:
		{
			cout << "Introduceti nodul al carui predecesor doriti sa il aflati:";
			cin >> element;
			if (Arbore.Search(element) == nullptr)
				cout << "Elementul " << element << " nu se afla in arbore\n";
			else
				if (Arbore.Predecesor(Arbore.Search(element)) == nullptr)
					cout << "Elementul " << element << " este elementul minim din arbore,prin urmare nu are un predecesor.";
				else
					cout << "Predecesorul elementului " << element << " este " << Arbore.Predecesor(Arbore.Search(element))->info;
			cout << endl;
			break;
		}
		case 8:
		{
			cout << "Introduceti una din optiunile 1,2,3,4:";
			cin >> element;
			if (element < 1 || element>4)
				while (element < 1 || element>4)
				{
					cout << "Trebuie sa introduceti o optiune dintre 1,2,3 sau 4!\n";
					cin >> element;
				}
			Arbore.PRINT_TREE(element);
			cout << endl;
		}

		}
	}

return 0;

}