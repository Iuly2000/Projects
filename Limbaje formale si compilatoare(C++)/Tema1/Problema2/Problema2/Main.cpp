#include <iostream>
#include <string>

bool VerifyNaturalNumber(std::string str)
{
	if (str[0] == '0' && str.size() != 1)
		return false;
	for (int index = 0; index < str.size(); index++)
		if (!(str[index] >= '0' && str[index] <= '9'))
			return false;
	return true;

}
bool VerifyInteger(std::string str)
{
	if (VerifyNaturalNumber(str) == true || (str[0] == '-' && VerifyNaturalNumber(str.substr(1, str.size()))))
		return true;
	return false;
}
bool VerifyFloat(std::string str)
{
	if (str[0] != '.' && str[str.size() - 1] != '.')
	{
		int index = 0;
		while (str[index] != '.' && index < str.size())
			index++;
		if (index == str.size() && VerifyInteger(str) == false)
			return false;
		if (str[index] == '.' && VerifyInteger(str.substr(0, index)) == false)
			return false;
		for (++index; index < str.size(); index++)
			if (!(str[index] >= '0' && str[index] <= '9'))
				return false;
		return true;

	}
	return false;
}
bool VerifyFloatExponential(std::string str)
{
	if (str[0] != 'e' && str[str.size() - 1] != 'e' && str[0] != 'E' && str[str.size() - 1] != 'E')
	{
		int index = 0;
		while (str[index] != 'e' && str[index] != 'E'&&index<str.size())
			index++;
		if (index == str.size() && VerifyFloat(str) == false)
			return false;
		if ((str[index] == 'e' || str[index] == 'E') && VerifyFloat(str.substr(0, index)) == false)
			return false;
		if (VerifyInteger(str.substr(++index, str.size() - index)) == false)
			return false;
		return true;

	}
	return false;

}
int main()
{
	std::string str;
	std::cout << "Insert your string:";
	std::cin >> str;
	if (VerifyNaturalNumber(str) == true)
		std::cout << "Natural number.";
	else
		if (VerifyInteger(str) == true)
			std::cout << "Integer number.";
		else
			if (VerifyFloat(str) == true)
				std::cout << "Float number.";
			else
				if (VerifyFloatExponential(str) == true)
					std::cout << "Float exponential number.";
				else
					std::cout << "Not a number.";
	return 0;
}