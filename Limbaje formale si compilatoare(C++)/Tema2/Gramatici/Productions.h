#pragma once
#include <iostream>
#include <string>
class Productions
{
private:
	std::string m_left;
	std::string m_right;
public:
	Productions()=default;
	Productions(std::string&, std::string&);
	const std::string GetLeft()const;
	const std::string GetRight()const;
	friend std::istream& operator>>(std::istream&, Productions&);
	friend std::ostream& operator<<(std::ostream&, const Productions&);
	~Productions() = default;

};

