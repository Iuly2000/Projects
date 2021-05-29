#include "AFN.h"
int main()
{
	
	AFN automatic;
	automatic.Read();
	if (automatic.VerifyAFN())
	{
		automatic.Write();
		std::cout << '\n';
		char input = 'y';
		std::string word;
		while (input == 'y' || input == 'Y')
		{
			std::cout << "Please enter your word:";
			std::cin >> word;
			automatic.VerifyWord(word);
			std::cout << " Would you like to insert a new word?Y/N\n";
			std::cin >> input;
		}
	}
	else
		std::cout << "Wrong AFN";
	

	
	return 0;
}