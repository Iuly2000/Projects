#include "Gramathics.h"

bool Gramathics::FindChr(std::vector<char>& vector, const char& chr)
{
	for (int index = 0; index < vector.size(); index++)
		if (chr == vector[index])
			return true;
	return false;
}

void Gramathics::TerminalWord(std::string& word)
{
	if (word == "")
		std::cout << " Cuvantul nu este format doar din terminale.\n";
	else
	{
		bool verify = true;
		for (int index = 0; index < word.size() && verify == true; index++)
			if (FindChr(m_VT, word[index]) == false)
			{
				std::cout << " Cuvantul nu este format doar din terminale.\n";
				verify = false;
			}
			std::cout << "\n";
	}

}

bool Gramathics::VerifyVNintVT()
{
	for (int index = 0; index < m_VN.size(); index++)
		for (int index1 = 0; index1 < m_VT.size(); index1++)
			if (m_VT[index1] == m_VN[index])
				return false;
	return true;
}

bool Gramathics::VerifySVN()
{
	for (int index = 0; index < m_VN.size(); index++)
		if (m_S == m_VN[index])
			return true;
	return false;
}

bool Gramathics::VerifyVNatleastone()
{
	bool check;
	for (int index = 0; index < m_P.size(); index++)
	{
		check = false;
		for (int index1 = 0; index1 < m_P[index].GetLeft().size(); index1++)
		{
			if (FindChr(m_VN, m_P[index].GetLeft()[index1]))
				check = true;
		}
		if (check == false)
			return false;
	}
	return true;
}

bool Gramathics::VerifySimbol()
{
	for (int index = 0; index < m_P.size(); index++)
		if (m_P[index].GetLeft()[0]==m_S&& m_P[index].GetLeft().size()==1)
			return true;
	return false;

}

bool Gramathics::VerifyVN_VT()
{
	bool checkleft = true, checkright = true;
	for (int index = 0; index < m_P.size(); index++)
	{
		for (int index1 = 0; index1 < m_P[index].GetLeft().size(); index1++)
			if (!FindChr(m_VN, m_P[index].GetLeft()[index1]) && !FindChr(m_VT, m_P[index].GetLeft()[index1]))
				return false;
		for (int index1 = 0; index1 < m_P[index].GetRight().size(); index1++)
			if (!FindChr(m_VN, m_P[index].GetRight()[index1]) && !FindChr(m_VT, m_P[index].GetRight()[index1]) && m_P[index].GetRight()[index1] != '$')
				return false;
	}
	return true;
}

void Gramathics::Read()
{
	std::ifstream file("Gramathics.txt");
	if (file.is_open())
	{

		std::string line;
		std::getline(file, line);
		for (int index = 0; index < line.size(); index++)
			if (line[index] != ' ')
				m_VN.push_back(line[index]);
		std::getline(file, line);
		for (int index = 0; index < line.size(); index++)
			if (line[index] != ' ')
				m_VT.push_back(line[index]);
		char S;
		file >> S;
		m_S = S;
		std::string left;
		std::string right;
		while (file >> left >> right)
		{
			Productions P(left, right);
			m_P.push_back(P);
		}

		file.close();
	}
	else
		std::cout << "Unable to open the file!";
}

bool Gramathics::Verify()
{
	if (VerifySimbol() && VerifySVN() && VerifyVNatleastone() && VerifyVNintVT() && VerifyVN_VT())
		return true;
	return false;
}

void Gramathics::Write()
{
	std::cout << "VN={";
	for (int index = 0; index < m_VN.size(); index++)
		std::cout << m_VN[index] << ",";
	std::cout << '\b';
	std::cout << "}\n";
	std::cout << "VT={";
	for (int index = 0; index < m_VT.size(); index++)
		std::cout << m_VT[index] << ",";
	std::cout << '\b';
	std::cout << "}\n";
	std::cout << m_S << '\n';
	std::cout << "P:\n";
	for (int index = 0; index < m_P.size(); index++)
		std::cout << m_P[index] << '\n';

}

void Gramathics::Generation(bool& option)
{
	std::string CurentWord{ m_S };
	std::vector<int> Positions{ 0 };
	while (Positions.size() > 0)
	{
		Positions.clear();
		for (int index = 0; index < m_P.size(); index++)
			if (CurentWord.find(m_P[index].GetLeft()) >= 0 && CurentWord.find(m_P[index].GetLeft()) < CurentWord.size())
				Positions.push_back(index);
		if (Positions.size() == 0)
			break;
		int random = rand() % Positions.size();
		if (option == true)
			std::cout << CurentWord << "->";
		if (m_P[Positions[random]].GetRight() != "$")
			CurentWord.replace(CurentWord.find(m_P[Positions[random]].GetLeft()), m_P[Positions[random]].GetLeft().size(), m_P[Positions[random]].GetRight());
		else
			CurentWord.erase(CurentWord.find(m_P[Positions[random]].GetLeft()), m_P[Positions[random]].GetLeft().size());
	}
	if (CurentWord == "")
	{
		std::cout << "$";
		TerminalWord(CurentWord);
	}
	else
	{
		std::cout << CurentWord;
		TerminalWord(CurentWord);
	}
}

