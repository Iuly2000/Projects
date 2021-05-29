#include <iostream>
#include <string>
#include <vector>
void PrefixWrite(std::string word)
{
	std::vector<std::string> vector;
	for (int index = 0; index < word.size()-1; index++)
		vector.push_back(word.substr(0, index+1));
	for (int index = 0; index < vector.size(); index++)
		std::cout << vector[index] << std::endl;
}

int main()
{
	std::string word;
	std::cout << "Insert your word:";
	std::cin >> word;
	PrefixWrite(word);
	return 0;
}