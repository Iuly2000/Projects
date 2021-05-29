#include <iostream>
using namespace std;
struct Nod
{
	int info;
	Nod* urm;

};
struct Stiva
{
	Nod* varf;
	Stiva()
	{
		varf = NULL;
	}

	void Push(int k)
	{
		Nod* x = new Nod;
		x->info = k;
		x->urm = varf;
		varf = x;

	}

	void Pop()
	{
		if (Isempty() == false)
		{
			Nod* y = varf;
			varf = varf->urm;
			delete y;
		}
		else
			cout << "Stiva este goala!";
	}
	int Top()
	{
		if (Isempty() == false)
			return varf->info;
		return 0;

	}
	bool Isempty()
	{
		if (varf == NULL)
			return true;
		return false;

	}
};

int main()
{
	Stiva noua;
	int n, numar;
	cout << "Introduceti numarul de elemente ale stivei:";
	cin >> n;
	cout << "Introduceti elementele:";
	for (int index = 0; index < n; index++)
	{
		cin >> numar;
		noua.Push(numar);
	}
	for (int index = 0; index < n; index++)
	{
		cout << noua.Top()<<" ";
		noua.Pop();
	}
	return 0;
}