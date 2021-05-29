#pragma once
#include <string>
#include <iostream>
class Edge
{
public:
	Edge(std::string node, std::string neighbournode,uint16_t cost);
	std::string GetNode();
	std::string GetNeighbourNode();
	uint16_t GetCost();
	friend std::ostream& operator<<(std::ostream& write, const Edge& edge);


private:
	std::string m_node, m_neighbournode;
	uint16_t m_cost;
};

