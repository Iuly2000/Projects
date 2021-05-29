#include <iostream>
#include "LexicalAnalyzer.h"

int main()
{
	LexicalAnalyzer lex;
	lex.Read();
	lex.WriteTokens();
	return 0;
}