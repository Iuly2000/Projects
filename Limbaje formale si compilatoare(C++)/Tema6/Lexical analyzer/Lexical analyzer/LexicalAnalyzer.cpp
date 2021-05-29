#include "LexicalAnalyzer.h"

void LexicalAnalyzer::ReadAFDs()
{
	m_ArithmeticOperator.Read("AFD_ArithmeticOperator.txt");
	m_AssignmentOperator.Read("AFD_AssignmentOperator.txt");
	m_Bracket.Read("AFD_Bracket.txt");
	m_Identifier.Read("AFD_Identifier.txt");
	m_Numeric.Read("AFD_Numeric.txt");
	m_RelationalOperator.Read("AFD_RelationalOperator.txt");
	m_Separator.Read("AFD_Separator.txt");
	std::ifstream file("KeyWords.txt");
	std::string line;
	while (std::getline(file, line))
	{
		m_keyWords.insert(line);
	}
}

void LexicalAnalyzer::RemoveComments(std::string& line)
{
	for (uint16_t index = 0; index < line.size(); ++index)
	{
		if (line[index] == '/' && line[index + 1] == '/')
			line.erase(line.begin() + index, line.end());
	}
}

void LexicalAnalyzer::RemoveBlanks(std::string& line)
{
	if (!line.empty())
		while (line[0] == ' ' || line[0] == '\t')
			line.erase(line.begin());

	if (!line.empty())
	{
		size_t index = line.size() - 1;
		while (line[index] == ' ' || line[index] == '\t')
		{
			line.erase(line.begin() + index);
			index = line.size() - 1;
		}
	}
}

void LexicalAnalyzer::Parser(std::string& line)
{
	size_t check = 0;
	while (!line.empty())
	{
		check = line.size();
		SearchAFD(m_Identifier, TokenType::Identifier, line);
			std::string atribute = tokens.back().second;
			if (m_keyWords.find(atribute) != m_keyWords.end())
			{
				tokens.pop_back();
				m_Identifiers.erase(atribute);
				tokens.push_back({ TokenType::KeyWord,atribute });
			}
		SearchAFD(m_ArithmeticOperator, TokenType::ArithmeticOperator, line);
		SearchAFD(m_AssignmentOperator, TokenType::AssignmentOperator, line);
		SearchAFD(m_Bracket, TokenType::Bracket, line);
		SearchAFD(m_Numeric, TokenType::Numeric, line);
		SearchAFD(m_RelationalOperator, TokenType::RelationalOperator, line);
		SearchAFD(m_Separator, TokenType::Separator, line);

		if (check == line.size())
		{
			tokens.push_back({ TokenType::Error,"Unknown symbol" });
			line.erase(line.begin());
			while (line[0] == ' ')
				line.erase(line.begin());
		}
	}
}

void LexicalAnalyzer::SearchAFD(AFD afd, TokenType token, std::string& line)
{
	std::string atribute = afd.VerifyWord(line);
	if (atribute == "Error")
	{
		tokens.push_back({ TokenType::Error,"wrong " + ConvertTokenTypetoString(token) });
	}
	else if (atribute != "")
	{
		tokens.push_back({ token,atribute });
		if(token==TokenType::Identifier)
			m_Identifiers.insert(atribute);
	}
}


void LexicalAnalyzer::WriteTokens()
{
	for (auto& token : tokens)
	{
		std::cout << '{' << ConvertTokenTypetoString(token.first) << ':' << token.second << '}' << std::endl;
	}

	std::cout << std::endl << "List of identifiers:";
	for (auto& identifier : m_Identifiers)
		std::cout << identifier << ' ';
}

void LexicalAnalyzer::Read()
{
	ReadAFDs();
	std::ifstream file("File.txt");
	std::string line;
	while (getline(file, line))
	{
		RemoveComments(line);
		RemoveBlanks(line);
		Parser(line);
	}
}