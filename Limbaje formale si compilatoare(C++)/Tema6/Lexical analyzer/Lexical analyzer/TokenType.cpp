#include "TokenType.h"

std::string ConvertTokenTypetoString(const TokenType& other)
{
	switch (other)
	{
	case TokenType::ArithmeticOperator:
		return "ArithmeticOperator";
	case TokenType::AssignmentOperator:
		return "AssignmentOperator";
	case TokenType::Bracket:
		return "Bracket";
	case TokenType::Error:
		return "Error";
	case TokenType::Identifier:
		return "Identifier";
	case TokenType::KeyWord:
		return "KeyWord";
	case TokenType::Numeric:
		return "Numeric";
	case TokenType::Separator:
		return "Separator";
	case TokenType::RelationalOperator:
		return "RelationalOperator";
	default:
		return "";
	}
}
