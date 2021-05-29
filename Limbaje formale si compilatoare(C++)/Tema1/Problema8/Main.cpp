#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <time.h> 
void gallows(std::vector<std::string> vector)
{
	srand(time(NULL));
	int rword = rand() % vector.size();
	int lives = 6;
	char input;
	std::string str,letters;
	std::cout << "This is the word you have to guess:";
	for (int index = 0; index < vector[rword].size(); index++)
		str.append("_ ");
	std::cout << str << "you have " << lives << " lives left\n";
	while (lives > 0)
	{
		std::cout << "Insert a letter:";
		std::cin >> input;
		if (!(vector[rword].find(input) >= 0 && vector[rword].find(input) <= vector[rword].size())||(letters.find(input)>=0&&letters.find(input)<letters.size()))
		{
			--lives;
			if (lives == 0)
				std::cout << "Sorry,you've lost!";
			else
				std::cout << "ERROR,you have " << lives << " lives remaining.\n";
		}
		else
		{
			letters.append(&input);
			for (int index = 0; index < vector[rword].size(); index++)
				if (vector[rword][index] == input)
					str[index * 2] = input;
			if (str.find("_") < 0 || str.find("_") > str.size())
			{
				std::cout << str << "\n";
				std::cout << "Congratulations,you've won!";
				lives = 0;
			}
			else
				std::cout << str << "\n";
		}
	}
}
int main()
{
	std::vector<std::string> vector = { "ananas","crocodile","banana","pool","summer","compliment","cinema","machine","robot","mansion","stronghold" };
	gallows(vector);
	return 0;
}