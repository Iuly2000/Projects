#include "Edge.h"

Edge::Edge(std::string node, std::string neighbournode, uint16_t cost)
	:m_node{node},m_neighbournode{neighbournode},m_cost{cost}
{
}

std::string Edge::GetNode()
{
	return m_node;
}

std::string Edge::GetNeighbourNode()
{
	return m_neighbournode;
}

uint16_t Edge::GetCost()
{
	return m_cost;
}

std::ostream& operator<<(std::ostream& write,const Edge& edge)
{
	write << edge.m_node << ' ' << edge.m_neighbournode << '=' << edge.m_cost<<'\n';
	return write;
}
