#include<iostream>
#include <string>
int Appearances(char character,std::string str)
{
	int appearance = 0;
	for (int index = 0; index < str.size(); index++)
		if (character == str[index])
			appearance++;
	return appearance;
}
int main()
{
	std::string str;
	char character;
	std::cout << "Insert the string:";
	std::cin >> str;
	std::cout << "/n Insert the character you're looking for:";
	std::cin >> character;
	std::cout << "Your character " << character << " was found in the string " << str << " " << Appearances(character, str) << " times.";

	return 0;
}
