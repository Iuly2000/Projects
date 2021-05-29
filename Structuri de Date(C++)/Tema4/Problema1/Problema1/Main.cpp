#include <iostream>
#include <vector>
using namespace std;
class PRIORITY_QUEUE
{
private:
	vector <int> Data;
public:
	void MaxHeap(int index)
	{
		int st = index * 2 + 1, dr = index * 2 + 2;
		int imax = index;
		if (st<Data.size() && Data[st]>Data[index])
			imax = st;
		if (dr<Data.size() && Data[dr]>Data[imax])
			imax = dr;
		if (imax != index)
		{
			int aux = Data[index];
			Data[index] = Data[imax];
			Data[imax] = aux;
			MaxHeap(imax);
		}
	}

	void ConstrHeap()
	{
		for (int index = Data.size() / 2 - 1; index >= 0; index--)
			MaxHeap(index);
	}
	bool IsEmpty()
	{
		if (Data.empty() == 1)
			return true;
		return false;

	}
	void Insert(int k)
	{
		Data.push_back(k);
		if(Data.size()>1)
		MaxHeap((Data.size()-2)/2);
	}
	int MaxElement()
	{
		return Data[0];
	}
	int ExtractMax()
	{
		if (Data.size() < 1)
			return 0;
		int max = Data[0];
		Data[0] = Data[Data.size() - 1];
		Data.pop_back();
		MaxHeap(0);
		return max;
	}
	int	CautaIndex(int element)
	{
		for (int index = 0; index < Data.size(); index++)
			if (Data[index] == element)
				return index;
		return -1;
	}
	void IncreaseKey(int element, int val)
	{
		int index = CautaIndex(element);
		if (index == -1)
			cout << "Elementul " << element << " nu a fost gasit in coada!";
		else
			if (val < Data[index])
				cout << "Valoare este prea mica!";
			else
			{

				int p = (index - 1) / 2;
				while (index > 0 && Data[p] < val)
				{
					Data[index] = Data[p];
					index = p;
					p = (index - 1) / 2;

				}
				Data[index] = val;
			}
	}
	void DecreaseKey(int element, int val)
	{
		int index = CautaIndex(element);
		if (index == -1)
			cout << "Elementul " << element << " nu a fost gasit in coada!";
		else
		if (val > Data[index])
			cout << "Valoare este prea mare!";
		else
		{

			int f1 = index * 2 + 1;
			int f2 = index * 2 + 2;
			int max = index;
			Data[index] = val;
			if (f1<Data.size() && Data[f1]>Data[index])
				max = f1;
			if (f2<Data.size() && Data[f2]>Data[max])
				max = f2;
			if (max != index)
			{
				int aux = Data[max];
				Data[max] = Data[index];
				Data[index] = aux;
				DecreaseKey(Data[max], val);
			}

		}

	}
	void Print()
	{
		for (int index = 0; index < Data.size(); index++)
			cout << Data[index] << " ";
	}

};

int main()
{
	PRIORITY_QUEUE coada;
	int input = -1;
	cout << "0.EXIT" << endl;
	cout << "1.Insert(insereaza un element in coada.)" << endl;
	cout << "2.MaxElement(returneaza elementul de prioritate maxima.)" << endl;
	cout << "3.ExtractMax(extrage elementul deprioritate maxima.)" << endl;
	cout << "4.IncreaseKey(Creste prioritatea  unui element)" << endl;
	cout << "5.DecreaseKey(Scade prioritatea unui element.)" << endl;
	cout << "6.Print(Afisarea elementelor coadei." << endl;
	while (input != 0)
	{
		int element, prioritate;
		cin >> input;
		switch (input)
		{
		case 0:break;
		case 1:
		{
			cout << "Introduceti un element in coada:\n";
			cin >> element;
			coada.Insert(element);
			break;
		}
		case 2:
		{
			cout << "Elementul de prioritate maxima este " << coada.MaxElement() << "\n";
			cout << "Continutul coadei este:";
			coada.Print();
			cout << endl;
			break;
		}
		case 3:
		{
			cout << "Elementul de prioritate maxima a fost extras:" << coada.ExtractMax() << "\n";
			cout << "Continutul coadei este:";
			coada.Print();
			cout << endl;
			break;
		}
		case 4:
		{
			cout << "Introduceti elementul al carui prioritate doriti sa o mariti:";
			cin >> element;
			cout << "Introduceti noua prioritate pentru acest element:";
			cin >> prioritate;
			coada.IncreaseKey(element, prioritate);
			cout << "Continutul coadei este:";
			coada.Print();
			cout << endl;
			break;
		}
		case 5:
		{
			cout << "Introduceti elementul al carui prioritate doriti sa o scadeti:";
			cin >> element;
			cout << "Introduceti noua prioritate pentru acest element:";
			cin >> prioritate;
			coada.DecreaseKey(element, prioritate);
			cout << "Continutul coadei este:";
			coada.Print();
			cout << endl;
			break;
		}
		case 6:
		{
			if (coada.IsEmpty() == true)
				cout << "Coada este goala!\n";
			else
			{
				cout << "Continutul coadei este:";
				coada.Print();
				cout << endl;
			}
			break;

		}
		}
	}
	return 0;
}