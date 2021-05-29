#include "AFD.h"

void AFD::Read(const std::string& txt)
{
	std::ifstream file(txt);
	if (file.is_open())
	{

		std::string line;
		std::getline(file, line);
		uint16_t previous = 0;
		for (uint16_t index = 0; index < line.size(); index++)
			if (line[index] == ' ')
			{
				m_Q.push_back(line.substr(previous, index - previous));
				previous = index + 1;
			}
		m_Q.push_back(line.substr(previous, line.size() - previous));
		std::getline(file, line);
		for (uint16_t index = 0; index < line.size(); index++)
			if (line[index] != ' ')
				m_Sigma.push_back(line[index]);

		std::getline(file, line);
		while (line.size() > 2)
		{
			uint16_t first = 0, pointer1 = line.find(' '), pointer2 = line.rfind(' ');
			m_Delta[{line.substr(first, pointer1), line[pointer1 + 1]}] = line.substr(pointer2 + 1, line.size() - pointer2 - 1);
			std::getline(file, line);
		}
		m_q0 = line;
		std::getline(file, line);
		previous = 0;
		for (uint16_t index = 0; index < line.size(); index++)
			if (line[index] == ' ')
			{
				m_F.push_back(line.substr(previous, index - previous));
				previous = index + 1;
			}
		m_F.push_back(line.substr(previous, line.size() - previous));
		file.close();
	}
	else
		std::cout << "Unable to open the file!";

}

void AFD::Write()
{
	std::cout << "Q={";
	for (uint16_t index = 0; index < m_Q.size(); index++)
		std::cout << m_Q[index] << ",";
	std::cout << "\b}\n";
	std::cout << "Sigma={";
	for (uint16_t index = 0; index < m_Sigma.size(); index++)
		std::cout << m_Sigma[index] << ",";
	std::cout << "\b}\n";
	std::cout << "Delta={";
	for (const auto& index : m_Delta)
		std::cout << '(' << index.first.first << ',' << index.first.second << ")=" << index.second << ", ";
	std::cout << "\b\b}\n";
	std::cout << "Start=" << m_q0 << '\n';
	std::cout << "F={";
	for (uint16_t index = 0; index < m_F.size(); index++)
		std::cout << m_F[index] << ",";
	std::cout << "\b}";
}

bool AFD::VerifyStart()
{
	for (uint16_t index = 0; index < m_Q.size(); index++)
		if (m_q0 == m_Q[index])
			return true;
	return false;
}

bool AFD::VerifyFinals()
{
	bool identify = false;
	for (uint16_t index = 0; index < m_F.size(); index++)
	{
		for (uint16_t index1 = 0; index1 < m_Q.size(); index1++)
			if (m_F[index] == m_Q[index1])
				identify = true;
		if (!identify)
			return false;
	}
	return true;
}

bool AFD::VerifyTransitions()
{

	for (const auto& index : m_Delta)
	{
		bool identify1 = false, identify2 = false, identify3 = false;
		for (uint16_t index1 = 0; index1 < m_Q.size(); index1++)
		{
			if (index.first.first == m_Q[index1])
				identify1 = true;
			if (index.second == m_Q[index1])
				identify2 = true;
		}
		for (uint16_t index2 = 0; index2 < m_Sigma.size(); index2++)
			if (index.first.second == m_Sigma[index2])
				identify3 = true;
		if (!identify1 || !identify2 || !identify3)
			return false;
	}
	return true;
}

bool AFD::VerifyAFD()
{
	if (VerifyStart() && VerifyFinals() && VerifyTransitions())
		return true;
	return false;
}
std::string AFD::VerifyWord(std::string& word)
{
	std::string current_state = m_q0;
	uint16_t index = 0;
	while (index < word.size())
	{
		if (m_Delta[{current_state, word[index]}] != "")
			current_state = m_Delta[{current_state, word[index]}];
		else
			break;
		++index;
	}

	std::string atribute;
	for (uint16_t index1 = 0; index1 < m_F.size(); ++index1)
	{
		if (current_state == m_F[index1])
		{
			atribute = word.substr(0, index);
			word.erase(0, index);
			if (word[0] == ' ')
				while (word[0] == ' ')
					word.erase(word.begin());
			return atribute;
		}
	}

	if (index != 0)
	{
		word.erase(0, index);
		if (word[0] == ' ')
			while (word[0] == ' ')
				word.erase(word.begin());
		return "Error";
	}

	return "";

}