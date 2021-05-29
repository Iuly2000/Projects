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
	EliminateInaccesableStates();
	MinimizationAFD();
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

void AFD::EliminateInaccesableStates()
{
	std::queue<std::string> currentStates;
	std::unordered_map<std::string, bool> visited;
	std::unordered_map<std::pair<std::string, uint8_t>, std::string, pair_hash> reducedAutomat;
	currentStates.push(m_q0);
	visited[m_q0] = true;
	std::string stateTovisit;
	while (!currentStates.empty())
	{
		for (const auto& symbol : m_Sigma)
		{
			stateTovisit = m_Delta[{currentStates.front(), symbol}];
			if (stateTovisit != "")
			{
				if (!visited[stateTovisit])
				{
					currentStates.push(stateTovisit);
					visited[stateTovisit] = true;
				}
				reducedAutomat[{currentStates.front(), symbol}] = stateTovisit;
			}
			else
				m_Delta.erase({ currentStates.front(), symbol });
		}
		currentStates.pop();
	}

	for (uint16_t index = 0; index < m_Q.size(); ++index)
	{
		if (!visited[m_Q[index]])
		{
			m_Q.erase(m_Q.begin() + index);
			--index;
		}
	}

	for (uint16_t index = 0; index < m_F.size(); ++index)
	{
		if (!visited[m_F[index]])
		{
			m_F.erase(m_F.begin() + index);
			--index;
		}
	}

	m_Delta = std::move(reducedAutomat);
}

std::unordered_map<std::pair<std::string, std::string>, char, AFD::pair_hash> AFD::CreateMinimizationTable()
{
	std::unordered_map<std::pair<std::string, std::string>, char, pair_hash> minimizationTable;
	bool tableChanged = true;
	std::string firstpair, secondpair;

	for (uint16_t index1 = 0; index1 < m_Q.size() - 1; ++index1)
		for (uint16_t index2 = index1 + 1; index2 < m_Q.size(); ++index2)
			if (FindInFinals(m_Q[index1]) && !FindInFinals(m_Q[index2]) ||
				!FindInFinals(m_Q[index1]) && FindInFinals(m_Q[index2]))
				minimizationTable[{m_Q[index1], m_Q[index2]}] = 'x';
			else
				minimizationTable[{m_Q[index1], m_Q[index2]}] = '-';

	while (tableChanged)
	{
		tableChanged = false;
		for (uint16_t index1 = 0; index1 < m_Q.size() - 1; ++index1)
			for (uint16_t index2 = index1 + 1; index2 < m_Q.size(); ++index2)
				if (minimizationTable[{m_Q[index1], m_Q[index2]}] != 'x')
					for (const auto& symbol : m_Sigma)
					{
						firstpair = m_Delta[{m_Q[index1], symbol}];
						secondpair = m_Delta[{m_Q[index2], symbol}];
						if (firstpair != secondpair)
							if (minimizationTable.find({ firstpair, secondpair }) != minimizationTable.end())
							{
								if (minimizationTable[{firstpair, secondpair}] == 'x')
								{
									minimizationTable[{m_Q[index1], m_Q[index2]}] = 'x';
									tableChanged = true;
									break;
								}
							}
							else if (minimizationTable.find({ secondpair, firstpair }) != minimizationTable.end())
								if (minimizationTable[{secondpair, firstpair}] == 'x')								 
							{
								minimizationTable[{m_Q[index1], m_Q[index2]}] = 'x';
								tableChanged = true;						
								break;
							}											

						if (firstpair == "")
							m_Delta.erase({ m_Q[index1], symbol });
						if (secondpair == "")
							m_Delta.erase({ m_Q[index2], symbol });
					}

	}

	
	return minimizationTable;
}

std::vector<std::unordered_set<std::string>>
AFD::CreateEquivalentStates(std::unordered_map<std::pair<std::string, std::string>, char, pair_hash>& minimizationTable)
{
	std::vector<std::pair<std::string, std::string>> equivalentPairs;
	std::vector<std::unordered_set<std::string>> equivalentStates;
	std::string firstState, secondState;
	uint16_t indexset = 0;
	for (auto& index : minimizationTable)
		if (index.second == '-')
		{
			firstState = index.first.first;
			secondState = index.first.second;
			equivalentPairs.push_back({ firstState ,secondState });
		}
	
	while (equivalentPairs.size() > 0)
	{
		firstState = equivalentPairs[0].first;
		secondState = equivalentPairs[0].second;
		equivalentStates.push_back({ firstState,secondState });
		equivalentPairs.erase(equivalentPairs.begin());
		for (uint16_t index=0;index<equivalentPairs.size();++index)
		{		
			firstState = equivalentPairs[index].first;
			secondState = equivalentPairs[index].second;
			for (const auto& indexState : equivalentStates[indexset])
			{
				if (firstState == indexState)
				{
					equivalentStates[indexset].insert(secondState);
					equivalentPairs.erase(equivalentPairs.begin()+index);
					--index;
					break;
				}
				if (secondState == indexState)
				{
					equivalentStates[indexset].insert(firstState);
					equivalentPairs.erase(equivalentPairs.begin() + index);
					--index;
					break;
				}

			}
		}
		++indexset;
	}

	return equivalentStates;
}

void AFD::ModifyStructureNewStates(std::vector<std::unordered_set<std::string>> equivalentStates)
{
	std::string firstDeltaState, secondDeltaState;
	uint8_t symbolDeltaState;
	std::vector<std::pair<std::string, uint8_t>> statesToDelete;
	bool verify;

	for (const auto& indexSet : equivalentStates)
	{
		std::string equivalentState;
		for (const auto& indexState : indexSet)
			equivalentState += indexState;

		for (int16_t index = 0; index < m_Q.size(); ++index)
		{
			for (const auto& indexState : indexSet)
			if (m_Q[index] == indexState)
			{
				m_Q.erase(m_Q.begin() + index);
				--index;
				break;
			}
		}
		m_Q.push_back(equivalentState);

		verify = false;
		for (int16_t index = 0; index < m_F.size(); ++index)
		{
			
			for (const auto& indexState : indexSet)
			if (m_F[index] == indexState)
			{
				m_F.erase(m_F.begin() + index);
				verify = true;
				--index;
				break;
			}
		}
		if (verify)
			m_F.push_back(equivalentState);

		for (auto& transition : m_Delta)
		{
			firstDeltaState = transition.first.first;
			symbolDeltaState = transition.first.second;
			secondDeltaState = transition.second;
			for (const auto& indexState : indexSet)
			{
				if (secondDeltaState == indexState)
					transition.second = equivalentState;

				if (firstDeltaState == indexState)
				{
					m_Delta[{equivalentState, symbolDeltaState}] = m_Delta[{firstDeltaState, symbolDeltaState}];
					statesToDelete.push_back({ firstDeltaState, symbolDeltaState });
				}
			}

		}
	}

	for (const auto& index : statesToDelete)
		m_Delta.erase(index);
}

void AFD::MinimizationAFD()
{
	std::unordered_map<std::pair<std::string, std::string>, char, pair_hash>
		minimizationTable = CreateMinimizationTable();
	ModifyStructureNewStates(CreateEquivalentStates(minimizationTable));
}

bool AFD::FindInFinals(std::string state)
{
	for (const auto& finalState : m_F)
		if (finalState == state)
			return true;
	return false;
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
	bool identify = false;
	while (word.size() != 0)
	{
		identify = false;
		if (m_Delta[{current_state, word[0]}] != "")
		{
			current_state = m_Delta[{current_state, word[0]}];
			identify = true;
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