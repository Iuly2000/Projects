#include <iostream>
#include <vector>
using namespace std;
template <class T1, class T2>
class Nod
{
public:
	T1 cheie;
	T2 info;
	char culoare;
	Nod<T1, T2>* st, * dr, * p;
	Nod<T1, T2>(int n = 0, int k = 0)
	{
		cheie = n;
		info = k;
		culoare = 'R';
		st = dr = p = nullptr;
	}
	 Nod<T1,T2> operator=(int valoare)
	{
		this->info = valoare;
		return *this;
	}
};
template <class T1, class T2>
class MAP
{
private:
	void INSERT_REPARA(Nod<T1, T2>* nou)
	{
		Nod<T1, T2>* u;
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
	void ROT_ST(Nod<T1, T2>* y)
	{
		Nod<T1, T2>* x = y->dr;
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
	void DELETE_REPARA(Nod<T1, T2>* x)
	{
		while (x != radacina && x->culoare == 'N')
			if (x == x->p->st)
			{
				Nod<T1, T2>* w = x->p->dr;
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
				Nod<T1, T2>* w = x->p->st;
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
	void ROT_DR(Nod<T1, T2>* y)
	{
		Nod<T1, T2>* x = y->st;
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
	void TRANSPLANT(Nod<T1, T2>* u, Nod<T1, T2>* v)
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
	int inaltime(Nod<T1, T2>* y)
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
	void RSD(Nod<T1, T2>* x)
	{
		if (x != NIL)
		{
			cout << x->cheie << "|" << x->info << x->culoare << " ";
			RSD(x->st);
			RSD(x->dr);
		}
	}
	void SDR(Nod<T1, T2>* x)
	{
		if (x != NIL)
		{
			SDR(x->st);
			cout << x->cheie << "|" << x->info << x->culoare << " ";
			SDR(x->dr);
		}
	}
	void DSR(Nod<T1, T2>* x)
	{
		if (x != NIL)
		{
			DSR(x->st);
			DSR(x->dr);
			cout << x->cheie << "|" << x->info << x->culoare << " ";
		}
	}
	void AfisareNivelDat(Nod<T1, T2>* nod, int nivel)
	{
		if (nod == NIL)
			return;
		if (nivel == 1)
			cout << nod->cheie << "|" << nod->info << nod->culoare << " ";
		else
			if (nivel > 1)
			{
				AfisareNivelDat(nod->st, nivel - 1);
				AfisareNivelDat(nod->dr, nivel - 1);
			}
	}
	void AfisarePeNivele(Nod<T1, T2>* x)
	{
		int h = inaltime(x);
		for (int index = 1; index <= h; index++)
			AfisareNivelDat(x, index);
	}
	Nod<T1,T2>* Copiere(Nod<T1, T2>* nod)
	{
		Nod<T1,T2>* copie =NIL;
		if (nod!=NIL)
		{
			copie = new Nod<T1,T2>(nod->cheie,nod->info);
			copie->culoare = nod->culoare;
			if (nod->st != NIL)
			{

				copie->st = Copiere(nod->st);
				copie->st->p = copie;
			}
			else
				copie->st = NIL;
			if (nod->dr != NIL)
			{
				copie->dr = Copiere(nod->dr);
				copie->dr->p = copie;
			}
			else
				copie->dr = NIL;
		
		}
		return copie;
	}
public:
	Nod<T1, T2>* radacina;
	Nod<T1, T2>* NIL;
	MAP()
	{
		NIL = new Nod<T1, T2>();
		NIL->culoare = 'N';
		NIL->p = NIL->dr = NIL->st = NIL;
		radacina = NIL;
	}
	void INSERT(Nod<T1, T2>* nou)
	{
		Nod<T1, T2>* y = NIL;
		Nod<T1, T2>* x = radacina;
		while (x != NIL)
		{
			y = x;
			if (nou->cheie < x->cheie)
				x = x->st;
			else
				x = x->dr;
		}
		nou->p = y;
		if (y == NIL)
			radacina = nou;
		else
			if (nou->cheie < y->cheie)
				y->st = nou;
			else
				y->dr = nou;
		nou->st = NIL;
		nou->dr = NIL;
		nou->culoare = 'R';
		INSERT_REPARA(nou);
	}
	void DELETE(Nod<T1, T2>* z)
	{
		Nod<T1, T2>* y = z, * x;
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
	void EMPTYMAP()
	{
		if (radacina != NIL)
		{
			Nod<T1, T2>* x = radacina->st;
			Nod<T1, T2>* y = radacina->dr;
			delete radacina;

			if (x != NIL)
			{
				radacina = x;
				EMPTYMAP();
			}
			if (y != NIL)
			{
				radacina = y;
				EMPTYMAP();
			}
		}
		radacina = NIL;
	}
	Nod<T1, T2>* Maxim(Nod<T1, T2>* nod)
	{
		if (nod == NIL)
			return nullptr;
		while (nod->dr != NIL)
			nod = nod->dr;
		return nod;
	}
	Nod<T1, T2>* Minim(Nod<T1, T2>* nod)
	{
		if (nod == NIL)
			return nullptr;
		while (nod->st != NIL)
			nod = nod->st;
		return nod;
	}
	Nod<T1, T2>* Succesor(Nod<T1, T2>* nod)
	{
		if (nod == Maxim(radacina))
			return nullptr;
		if (nod->dr != NIL)
		{

			Nod<T1, T2>* y = Minim(nod->dr);
			return y;
		}
		Nod<T1, T2>* y = nod->p;
		while (y != NIL && y->dr == nod)
		{
			nod = y;
			y = y->p;
		}
		return y;


	}
	Nod<T1, T2>* Predecesor(Nod<T1, T2>* nod)
	{
		if (nod == Minim(radacina))
			return nullptr;
		if (nod->st != NIL)
		{
			Nod<T1, T2>* y = Maxim(nod->st);
			return y;
		}
		Nod<T1, T2>* y = nod->p;
		while (y != NIL && y->st == nod)
		{
			nod = y;
			y = y->p;
		}
		return y;


	}
	Nod<T1, T2>* Search(int x)
	{
		Nod<T1, T2>* y = radacina;
		while (y != NIL)
		{
			if (y->cheie == x)
				return y;
			else
				if (y->cheie < x)
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
	void CONSTRUCT(vector < Nod<T1, T2>* > arbore)
	{
		for (int index = 0; index < arbore.size(); index++)
			INSERT(arbore[index]);
	}
 Nod<T1, T2>& operator[](const int key)
	{
		if (Search(key) != nullptr)
			return  *Search(key);
		Nod<T1, T2>* nou = new Nod<T1, T2>(key);
		INSERT(nou);
		return  *nou;
	}
 void CLEAR()
 {
	 while (radacina != NIL)
		 DELETE(radacina);
 }

MAP<T1,T2>& operator=( MAP<T1,T2>& map)
 {
	CLEAR();
	this->NIL = map.NIL;
	this->radacina = Copiere(map.radacina);
	radacina->p = NIL;
		return *this;
 }
 int SIZE()
 {
	 int nr = 0;
	 for (Nod<T1, T2>* index = Minim(radacina); index != nullptr; index = Succesor(index))
		 nr++;
	 return nr;
 }
 bool ISEMPTY()
 {
	 if (radacina == NIL)
		 return true;
	 return false;
 }
};
int main()
{
	MAP<int, int> a,b;
	a[10] = 4;
	a[9] = 23;
	a[6] = 7;
	a[0] = 4;
	a[11] = 23;
	a[17] = 7;
	a[15] = 4;
	a[14] = 23;
	a[13] = 4;
	a[20] = 6;
	b = a;
	a.PRINT_TREE(1);
	cout << endl << a.SIZE() << endl;
	b.PRINT_TREE(1);
	cout << endl << b.SIZE()<<endl;
	a.CLEAR();
	if (a.ISEMPTY() == true)
		cout << "mapa este goala.";
	else
		cout << "mapa nu este goala.";
	return 0;
}