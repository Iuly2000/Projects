#pragma once
#include <cstdint>
#include <string>
enum class TokenType:uint8_t
{
	ArithmeticOperator,
	AssignmentOperator,
	Bracket,
	Identifier,
	Numeric,
	RelationalOperator,
	Separator,
	KeyWord,
	Error
};

std::string ConvertTokenTypetoString(const TokenType& other);
