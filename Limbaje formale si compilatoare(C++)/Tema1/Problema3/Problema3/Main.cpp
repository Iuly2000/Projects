#include <iostream>
#include <string>
#include <stdio.h>
void ReplaceString(std::string& str, std::string str1, std::string str2)
{
	for (int index = 0; index < str.size() / 2; index++)
	{
		char aux = str[index];
		str[index] = str[str.size() - 1 - index];
		str[str.size() - 1 - index] = aux;
	}
	int pointer = str.find(str1);
	while (pointer>=0&&pointer<str.size())
	{
		str.replace(pointer,str1.size(), str2);
		pointer= str.find(str1);
	}
}

int main()
{
	std::string str, str1, str2;
	std::cout << "Insert your string:";
	std::getline(std::cin, str);
	std::cout << "Insert your substring that you want to replace:";
	std::getline(std::cin, str1);
	std::cout << "Insert your replacing substring:";
	std::getline(std::cin, str2);
	ReplaceString(str, str1, str2);
    std::cout << str;
	return 0;
}