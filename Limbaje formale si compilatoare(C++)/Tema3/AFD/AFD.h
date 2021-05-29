#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>
#include <fstream>
class AFD
{
public:
	AFD() = default;
	AFD(const AFD&) = default;
	~AFD() = default;
	void Read();
	void Write();
	bool VerifyAFD();
	void VerifyWord(std::string);
private:
	std::vector<std::string> m_Q;
	std::vector<uint8_t> m_Sigma;
	std::vector<std::tuple<std::string, uint8_t, std::string>> m_Delta;
	std::string m_q0;
	std::vector <std::string > m_F;
	bool VerifyStart();
	bool VerifyFinals();
	bool VerifyTransitions();
};

