#include "AFD.h"
int main()
{
	AFD automatic;
	automatic.Read();
	if(automatic.VerifyAFD())
	automatic.Write();
	std::cout << '\n';
	char input='y';
	std::string word;
	while (input == 'y'||input=='Y')
	{
		std::cout << "Please enter your word:";
		std::cin >> word;
		automatic.VerifyWord(word);
		std::cout << " Would you like to insert a new word?Y/N\n";
		std::cin >> input;
	}
	return 0;
}