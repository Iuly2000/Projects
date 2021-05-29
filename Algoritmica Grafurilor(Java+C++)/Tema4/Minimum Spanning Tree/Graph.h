#pragma once

#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <queue>
#include <deque>
#include "Edge.h"
#include "UnionFind.h"

class Graph
{
public:
	Graph()=default;
	Graph(const Graph&)=default;
	~Graph() = default;
	void ReadGraph();
	void Kruskal();
	void Prim();
private:
     void SortGraph(std::vector<std::pair<std::string, std::pair<uint16_t, std::string>>>&sortGraph);
	std::multimap<std::string, std::pair<uint16_t, std::string>> m_Edges;
	std::set<std::string> m_Nodes;
	std::map<std::string, uint16_t> PositionInGraph();
	class myComparator
	{
	public:
		int operator() ( Edge  &cost1,  Edge& cost2)
		{
			return cost1.GetCost() > cost2.GetCost();
		}
	};
	

};

