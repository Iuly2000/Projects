#include <iostream>
#include <string>
void SegmentString(std::string str)
{
	std::string word;
	const char* token = " .,?!";
	int index1 = 1,index2=-1;
	for (int index = 0; index < str.size(); index++)
	{
		if (strchr(token, str[index]) && !(strchr(token, str[index - 1])))
		{
			word = str.substr(index2+1, index-index2-1);
			std::cout << index1++ << "." << word << std::endl;

		}
		if (strchr(token, str[index]))
			index2 = index;
		
		
	}

}

int main()
{
	std::string str;
	std::cout << "Insert your string:";
	std::getline(std::cin, str);
	SegmentString(str);
	return 0;
}
