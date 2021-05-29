#include <iostream>
#include <string>
#include <vector>
void ReadWords(std::vector<std::string>& vector)
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
void VerifSubstr(std::vector<std::string> vector1, std::string substr, std::vector<std::string> &vector2)
{
	std::cout << "Insert your substring:";
	std::cin >> substr;
	for (int index = 0; index < vector1.size(); index++)
	{

		if (vector1[index].find(substr)>=0&&vector1[index].find(substr)<vector1[index].size())
			vector2.push_back(vector1[index]);
	}
}
void Write(std::vector<std::string> vector)
{
	for (int index = 0; index < vector.size(); index++)
		std::cout << vector[index] << std::endl;
}
int main()
{
	std::vector<std::string> vector1;
	std::string substr;
	std::vector<std::string> vector2;
	ReadWords(vector1);
	VerifSubstr(vector1, substr, vector2);
	Write(vector2);
	return 0;
}