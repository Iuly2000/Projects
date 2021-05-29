#include "AFN.h"
#include <queue>
void AFN::Read()
{
	std::ifstream file("AFN.txt");
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
			int first = 0, pointer1 = line.find(' '), pointer2 = line.rfind(' ');
			m_Delta.insert({ {line.substr(first,pointer1), line[pointer1 + 1]},line.substr(pointer2 + 1,line.size() - pointer2 - 1) });
			std::getline(file, line);
		}
		m_q0 = line;
		std::getline(file, line);
		previous = 0;
		for (uint16_t index = 0; index < line.size(); ++index)
			if (line[index] == ' ')
			{
				std::cout << 1;
				m_F.push_back(line.substr(previous, index - previous));
				previous = index + 1;
			}
		m_F.push_back(line.substr(previous, line.size() - previous));
		file.close();

	}
	else
		std::cout << "Unable to open the file!";

}

void AFN::Write()
{
	std::vector<uint16_t> maxTransitions;
	SizeMaxTransitions(maxTransitions);
	std::cout << "----------";
	for (auto& index : maxTransitions)
		for (uint16_t index1 = 0; index1 < index; ++index1)
			std::cout << "-----";
	std::cout << "-\n";
	std::cout << "| DELTA  |";

	for (uint16_t index = 0; index < maxTransitions.size(); ++index)
	{
		uint16_t currentTransition = maxTransitions[index];
		if (index == maxTransitions.size() / 2)
		{
			std::cout << "SIGMA";
			currentTransition--;
		}
		for (uint8_t index1 = 0; index1 < currentTransition; ++index1)
			std::cout << "     ";
	}
	std::cout << "|\n";
	std::cout << "|        |";
	for (auto& index : maxTransitions)
		for (uint16_t index1 = 0; index1 < index; ++index1)
			std::cout << "-----";
	std::cout << "-\n";
	std::cout << "|        |";
	for (uint16_t index = 0; index < maxTransitions.size(); ++index)
	{
		for (uint16_t index1 = 0; index1 < maxTransitions[index]; ++index1)
			if (index1 == maxTransitions[index] / 2)
				if (maxTransitions[index] % 2 == 1)
					std::cout << "  " << m_Sigma[index] << "  ";
				else
					std::cout << m_Sigma[index] << "    ";
			else
				std::cout << "     ";
		std::cout << "\b|";
	}
	std::cout << "\b |\n----------";
	for (auto& index : maxTransitions)
		for (uint16_t index1 = 0; index1 < index; ++index1)
			std::cout << "-----";
	std::cout << "-\n";
	for (uint16_t index1 = 0; index1 < m_Q.size(); ++index1)
	{
		if (index1 == m_Q.size() / 2)
			std::cout << "| Q |";
		else
			std::cout << "|   |";
		std::cout << ' ' << m_Q[index1] << " |";
		for (uint16_t index2=0;index2<maxTransitions.size();++index2)
		{
			uint16_t currentTransition = maxTransitions[index2];
			std::cout << ' ';
			const auto& range = m_Delta.equal_range({ m_Q[index1],m_Sigma[index2]});
			for (auto index1 = range.first; index1 != range.second; index1++)
			{
				std::cout << index1->second <<"   ";
				currentTransition--;
			}
			for (uint8_t index1 = 0; index1 < currentTransition; ++index1)
				std::cout << "     ";
			std::cout << "\b\b|";

		}
		std::cout <<"\b |\n";
	}
	std::cout << "----------";
	for (auto& index : maxTransitions)
		for (uint16_t index1 = 0; index1 < index; ++index1)
			std::cout << "-----";
	std::cout << "-\n";
	std::cout << "Start=" << m_q0 << '\n';
	std::cout << "F={";
	for (uint16_t index = 0; index < m_F.size(); ++index)
		std::cout << m_F[index] << ',';
	std::cout << "\b}";
}

bool AFN::VerifyStart()
{
	for (int index = 0; index < m_Q.size(); index++)
		if (m_q0 == m_Q[index])
			return true;
	return false;
}

bool AFN::VerifyFinals()
{
	bool identify = false;
	for (int index = 0; index < m_F.size(); index++)
	{
		for (uint16_t index1 = 0; index1 < m_Q.size(); index1++)
			if (m_F[index] == m_Q[index1])
				identify = true;
		if (!identify)
			return false;
	}
	return true;
}

bool AFN::VerifyTransitions()
{

	for (const auto& index : m_Delta)
	{
		bool identify1 = false, identify2 = false, identify3 = false;
		for (int index1 = 0; index1 < m_Q.size(); index1++)
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

void AFN::SizeMaxTransitions(std::vector<uint16_t>& size)
{
	for (auto& index1 : m_Sigma)
	{
		uint16_t max = 0;
		for (auto& index2 : m_Q)
			if (m_Delta.count({ index2,index1 }) > max)
				max = m_Delta.count({ index2,index1 });
		size.push_back(max);
	}
}

bool AFN::VerifyAFN()
{
	if (VerifyStart() && VerifyFinals() && VerifyTransitions())
		return true;
	return false;
}
void AFN::VerifyWord(std::string word)
{
	std::queue<std::string> current_states({ m_q0 });
	while (word.size() != 0)
	{
		int index = current_states.size();
		while (index != 0)
		{
			const auto& range = m_Delta.equal_range({ current_states.front(), word[0] });
			for (auto index1 = range.first; index1 != range.second; index1++)
				current_states.push(index1->second);
			current_states.pop();
			index--;
		}

		if (current_states.empty())
		{
			std::cout << "Blocked";
			break;
		}
		word.erase(word.begin());
	}

	if (!current_states.empty())
	{
		bool verify = false;
		while (!current_states.empty())
		{
			for (int index = 0; index < m_F.size(); index++)
				if (current_states.front() == m_F[index])
				{
					verify = true;
					std::cout << "Accepted";
					break;
				}
			if (verify)
				break;
			current_states.pop();
		}
		if (!verify)
			std::cout << "Unaccepted";
	}

}