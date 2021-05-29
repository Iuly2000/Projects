#include "Gramathics.h"
int main()
{
	Gramathics gram;
	int NumberofWords;
	bool optiune;
	gram.Read();
	srand(time(NULL));
	if (gram.Verify())
	{
		gram.Write();
		std::cout << '\n';
		std::cout << "Introduceti numarul de cuvinte:";
		std::cin >> NumberofWords;
		std::cout << "Introduceti optiunea de afisare:";
		std::cin >> optiune;
		while (NumberofWords > 0)
		{
			gram.Generation(optiune);
			NumberofWords--;
		}
	}
	else
		std::cout << "The grammar is not correct.";
	return 0;
}