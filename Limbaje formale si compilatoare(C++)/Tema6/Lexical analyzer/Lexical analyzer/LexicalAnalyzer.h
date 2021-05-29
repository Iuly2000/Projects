#pragma once
#include "AFD.h"
#include "TokenType.h"
#include <unordered_set>

class LexicalAnalyzer
{
public:
	LexicalAnalyzer() = default;
	LexicalAnalyzer(const LexicalAnalyzer&) = default;
	~LexicalAnalyzer() = default;
	void Read();
	void WriteTokens();
private:
	AFD m_ArithmeticOperator;
	AFD m_AssignmentOperator;
	AFD m_Bracket;
	AFD m_Identifier;
	AFD m_Numeric;
	AFD m_RelationalOperator;
	AFD m_Separator;
	std::unordered_set<std::string> m_keyWords;

	std::vector<std::pair<TokenType, std::string>> tokens;
	std::unordered_set<std::string> m_Identifiers;

	void ReadAFDs();
	void RemoveComments(std::string& line);
	void RemoveBlanks(std::string& line);
	void Parser(std::string& line);
	void SearchAFD(AFD afd,TokenType token,std::string&);
};

