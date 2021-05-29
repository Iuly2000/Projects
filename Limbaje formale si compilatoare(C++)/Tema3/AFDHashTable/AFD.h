#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <unordered_map>
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
	struct pair_hash
	{
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2>& pair) const
		{
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};
	std::vector<std::string> m_Q;
	std::vector<uint8_t> m_Sigma;
	std::unordered_map<std::pair<std::string, uint8_t>, std::string, pair_hash> m_Delta;
	std::string m_q0;
	std::vector <std::string > m_F;
	bool VerifyStart();
	bool VerifyFinals();
	bool VerifyTransitions();
};

