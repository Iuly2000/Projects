#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Nod
{
	int  info;
	Nod* urm;

};
struct Stiva
{
	Nod* varf;
	Stiva()
	{
		varf = NULL;
	}

	void push(int k)
	{
		Nod* x = new Nod;
		x->info = k;
		x->urm = varf;
		varf = x;

	}

	void pop()
	{
		if (isempty() == false)
		{
			Nod* y = varf;
			varf = varf->urm;
			delete y;
		}
	}
	int top()
	{
		if (isempty() == false)
			return varf->info;
		return 0;

	}
	bool isempty()
	{
		if (varf == NULL)
			return true;
		return false;

	}
};
void citire_fisier(string filepath, string& expresie)
{

	ifstream myfile(filepath);
	if (myfile.is_open())
	{

		getline(myfile, expresie);
		myfile.close();
	}
	else
		cout << "unable to open the file";

}
int preced(char element)
{
	if (element == '(')
		return 0;
	if (element == '-' || element == '+')
		return 1;
	if (element == '*' || element == '/')
		return 2;
	return -1;
}
int cazuri(char element)
{
	if (element == '-')
		return 1;
	if (element == '+')
		return 2;
	if (element == '*')
		return 3;
	if (element == '/')
		return 4;
	return -1;
}
void formapoloneza(string expresie, char*& polonez, Stiva operatori, int& var)
{
	polonez = new char[expresie.length()];
	int contor = 0;
	for (int index = 0; index < expresie.length(); index++)
	{
		if (expresie[index] >= '0' && expresie[index] <= '9')
			polonez[contor++] = expresie[index];
		else
			if (preced(expresie[index]) == -1 && expresie[index] != ')')
			{
				var = -1;
				break;
			}
			else
				if (expresie[index] == '(')
					operatori.push(expresie[index]);
				else
					if (expresie[index] == ')')
					{
						while (operatori.isempty() != 1 && char(operatori.top()) != '(')
						{
							polonez[contor++] = operatori.top();
							operatori.pop();
						}
						if (operatori.top()!='(')
						{
							var = -2;
							break;
						}
						operatori.pop();
					}
					else
					{
						while (operatori.isempty() != 1 && preced(expresie[index]) <= preced(char(operatori.top())))
						{

							polonez[contor++] = operatori.top();
							operatori.pop();
						}
						operatori.push(expresie[index]);
					}

	}
	while (operatori.isempty() != 1&&var!=-1)
	{
		if (char(operatori.top()) == '(')
		{
			var = -2;
			break;
		}
		polonez[contor++] = operatori.top();
		operatori.pop();

	}
	if (var != -1 && var != -2)
		var = contor;
}

void afisarepoloneza(char* polonez, Stiva numere, int  var)
{
	int verific = 0;
	for (int index = 0; index < var; index++)
	{
	
		if (polonez[index] >= '0' && polonez[index] <= '9')
				numere.push(polonez[index] - '0');
				else
					switch (cazuri(polonez[index]))
					{
					case 1:
					{
						int rezultat = numere.top();
						numere.pop();
						if (numere.isempty() == 1)
							verific = 1;
						rezultat = numere.top() - rezultat;
						numere.pop();
						numere.push(rezultat);
						break;
					}
					case 2:
					{
						int rezultat = numere.top();
						numere.pop();
						if (numere.isempty() == 1)
							verific = 1;
						rezultat = numere.top() + rezultat;
						numere.pop();
						numere.push(rezultat);
						break;
					}
					case 3:
					{
						int rezultat = numere.top();
						numere.pop();
						if (numere.isempty() == 1)
							verific = 1;
						rezultat = numere.top() * rezultat;
						numere.pop();
						numere.push(rezultat);
						break;
					}
					case 4:
					{;
					int rezultat = numere.top();
					numere.pop();
					if (numere.isempty() == 1)
						verific = 1;
					rezultat = numere.top() / rezultat;
					numere.pop();
					numere.push(rezultat);
					break;
					}

					}
	}

	if (verific == 1)
		cout << "prea multi operatori!";
	else
		cout << numere.top();
}

int main()
{
	string filepath = "expresie.txt", expresie;
	Stiva operatori, numere;
	char* polonez;
	int var = 0;
	citire_fisier(filepath, expresie);
	formapoloneza(expresie, polonez, operatori, var);
	if (var == -1)
		cout << "expresia introdusa are caractere necunoscute!";
	else
		if (var == -2)
			cout << "parantezarea nu este corecta!";
		else
		{
			for (int index = 0; index < var; index++)
				cout << polonez[index];
			cout << endl;
			afisarepoloneza(polonez, numere, var);
		}
	delete[]polonez;
	return 0;
}