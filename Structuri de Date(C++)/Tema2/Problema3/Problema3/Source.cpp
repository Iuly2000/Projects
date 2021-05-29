#include <iostream>
using namespace std;
struct Coada
{
	int* data;
	int size, begin, end;
	Coada()
	{
		begin = 0;
		end = 0;
	}
	void front()
	{
			if (isempty() == true)
				cout << "Coada este goala!";
			else
		cout << data[begin] << " ";

	}

	void push(int k)
	{
		if (end == 0 && begin == 0)
			data[end++] = k;
		else
			if (isfull() == true)
				cout << "Coada este plina!";
			else
			{
				if (end == size)
					end = 0;
					data[end++] = k;
			}
	}

	void pop()
	{

		if (isempty() == 1)
			cout << "Coada este goala!";
		else
		{
			if (begin == size-1)
				begin = 0;
			else
				begin++;
		}

	}
	bool isempty()
	{
		if (end == begin)
			return true;
		return false;

	}
	bool isfull()
	{
		if (end == size && begin == 0)
			return true;
		if (end == begin)
			return true;

		return false;

	}

};

int main()
{
	Coada elemente;
	int n, numar;
	cout << "Introduceti numarulde elemente din coada:";
	cin >> n;
	cout << "Introduceti elementele:";
	elemente.size = n;
	elemente.data = new int[n];
	for (int index = 0; index < elemente.size; index++)
	{
		cin >> numar;
		elemente.push(numar);
	}
	for (int index = 0; index < elemente.size; index++)
	{
		elemente.front();
		elemente.pop();
	}
	return 0;

}
