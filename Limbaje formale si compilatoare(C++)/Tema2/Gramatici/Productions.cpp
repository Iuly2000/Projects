#include "Productions.h"

Productions::Productions(std::string& left, std::string& right)
{
	m_left = left;
	m_right = right;
}

const std::string Productions::GetLeft() const
{
	return m_left;
}

const std::string Productions::GetRight() const
{
	return m_right;
}

std::istream& operator>>(std::istream&read, Productions&other)
{
	read >> other.m_left >> other.m_right;
	return read;
}

std::ostream& operator<<(std::ostream& write, const Productions& other)
{
	std::string arrow{ "->" };
	write << other.m_left<<arrow<< other.m_right;
	return write;
}
