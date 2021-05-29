#pragma once
#include <vector>
#include "Productions.h"
#include <fstream>
#include <time.h>
class Gramathics
{
private:
	std::vector<char> m_VN;
	std::vector<char> m_VT;
	char m_S;
	std::vector<Productions> m_P;
	bool VerifyVNintVT();
	bool VerifySVN();
	bool VerifyVNatleastone();
	bool VerifySimbol();
	bool VerifyVN_VT();
	bool FindChr(std::vector<char>&,const char&);
	void TerminalWord(std::string& word);
public:
	Gramathics()=default;
	Gramathics(const Gramathics& other) = default;
	void Read();
	bool Verify();
	void Write();
	void Generation(bool& option);
	~Gramathics()=default;

};

