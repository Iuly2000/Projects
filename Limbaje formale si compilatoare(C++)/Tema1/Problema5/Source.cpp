#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
void Sort(std::vector<std::string> &vector)
{
	for (int index = 0; index < vector.size(); index++)
		std::sort(vector[index].begin(), vector[index].end());
}
void ReadWords(std::vector<std::string> &vector)
{
	std::string word;
	int wordsnumber;
	std::cout << "Insert the number of words:";
	std::cin >> wordsnumber;
	std::cout << "Insert your words:";
	for (int index = 0; index < wordsnumber; index++)
	{
		std::cin >> word;
		vector.push_back(word);
	}
}
void Write(std::vector<std::string> vector)
{
	for (int index = 0; index < vector.size(); index++)
		std::cout << vector[index] << std::endl;
}
int main()
{
	std::vector<std::string> vector;
	ReadWords(vector);
	Sort(vector);
	Write(vector);
	return 0;
}