#include "AFD.h"

void AFD::Read()
{
	std::ifstream file("AFD.txt");
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
		const uint16_t first = 0, middle = 3, last = 5, count = 2;
		while (line.size() > 2)
		{
			m_Delta.push_back(std::make_tuple(line.substr(first, count), line[middle], line.substr(last, count)));
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
	for (uint16_t index = 0; index < m_Delta.size(); index++)
		std::cout << '(' << std::get<0>(m_Delta[index]) << ',' << std::get<1>(m_Delta[index]) << ")=" << std::get<2>(m_Delta[index]) << ", ";
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
	
	for (uint16_t index = 0; index < m_Delta.size(); index++)
	{
		bool identify1 = false, identify2 = false, identify3 = false;
		for (uint16_t index1 = 0; index1 < m_Q.size(); index1++)
		{
			if (std::get<0>(m_Delta[index]) == m_Q[index1])
				identify1 = true;
			if (std::get<2>(m_Delta[index]) == m_Q[index1])
				identify2 = true;
		}
		for (uint16_t index2 = 0; index2 < m_Sigma.size(); index2++)
			if (std::get<1>(m_Delta[index]) == m_Sigma[index2])
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

void AFD::VerifyWord(std::string word)
{
	std::string current_state = m_q0;
	bool identify;
	while (word.size()!=0)
	{
		 identify = false;
		for(uint16_t index1=0;index1<m_Delta.size();index1++)
			if (current_state == std::get<0>(m_Delta[index1]) && word[0] == std::get<1>(m_Delta[index1]))
			{
				current_state = std::get<2>(m_Delta[index1]);
				identify = true;
				break;
			}
		if (!identify)
		{
			std::cout << "Blocked";
			break;
		}
		word.erase(word.begin());
	}

	if (identify)
	{
		for (uint16_t index = 0; index < m_F.size(); index++)
			if (current_state == m_F[index])
			{
				std::cout << "Accepted";
				identify = false;
			}
		if (identify)
			std::cout << "Unaccepted";
	}

}