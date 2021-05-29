#include "Graph.h"

void Graph::ReadGraph()
{
	std::ifstream file("Graph.txt");
	if (file.is_open())
	{
	
		std::string node, cost, neighbournode;
		while (file.peek() != '\n')
		{
			file >> node;
			m_Nodes.insert(node);
		}
		
		while (!file.eof())
		{
			file >> node >> cost >> neighbournode;
			m_Edges.insert({ node, {(uint16_t)std::stoi(cost),neighbournode } });
			m_Edges.insert({ neighbournode, { (uint16_t)std::stoi(cost),node } });

		}
		file.close();

	}
	else
		perror("Unable to open file!");

}

void Graph::Kruskal()
{
	uint16_t totalCostTree = 0, cost;
	std::string node, neighbournode;
	std::vector<std::pair<std::string, std::pair<uint16_t, std::string>>> sortedGraph;
	std::set<std::pair<std::string, std::string>> edges;
	std::map<std::string, uint16_t> position = PositionInGraph();
	SortGraph(sortedGraph);
	UnionFind components(m_Nodes.size());

	for (const auto& iterator : sortedGraph)
	{
		node = iterator.first;
		cost = iterator.second.first;
		neighbournode = iterator.second.second;
		if (!components.Connected(position[node], position[neighbournode]))
		{
			edges.insert({ node,neighbournode });
			totalCostTree += cost;
			components.Unify(position[node], position[neighbournode]);
		}
	}

	std::cout << "The minimum spanning tree(Kruskal Algorithm) is:";
	for (const auto& iterator : edges)
	{
		node = iterator.first;
		neighbournode = iterator.second;
		std::cout << '(' << node << ',' << neighbournode << ')' << ' ';
	}
	std::cout << "\nThe total cost is:"<<totalCostTree;
}



void Graph::SortGraph(std::vector<std::pair<std::string, std::pair<uint16_t, std::string>>>& sortGraph)
{
	auto Cost = [](std::pair<std::string, std::pair<uint16_t, std::string>>const& cost1,
		std::pair<std::string, std::pair<uint16_t, std::string>> const& cost2) -> bool
	{
		return cost1.second.first < cost2.second.first;
	};

	for (const auto& iterator : m_Edges)
		sortGraph.push_back(iterator);
	
	std::sort(sortGraph.begin(), sortGraph.end(), Cost);
}

std::map<std::string, uint16_t> Graph::PositionInGraph()
{
	 std::map<std::string, uint16_t> position;
	 uint16_t index = 0;
	 for (const auto& iterator : m_Nodes)
	 {
		 position[iterator] = index;
		 ++index;
	 }

	 return position;
}

void Graph::Prim()
{
	
	uint16_t totalCostTree = 0, cost;
	std::string node, neighbournode, currentnode=*m_Nodes.begin();
	std::set<std::pair<std::string, std::string>> mst;
	std::map<std::string, bool> Visited;
	std::priority_queue<Edge, std::vector<Edge>, myComparator> edges;

	for (const auto& iterator : m_Nodes)
		Visited[iterator] = false;
	Visited[currentnode] = true;

	auto iterator = m_Edges.equal_range(currentnode);
	for (auto index = iterator.first; index != iterator.second; ++index)
	{
		node = index->first;
		cost = index->second.first;
		neighbournode = index->second.second;
		edges.push({ node,neighbournode,cost });
	}

	while (mst.size() < m_Nodes.size() - 1)
	{
		Edge neighbour = edges.top();
		if (Visited[neighbour.GetNeighbourNode()])
			edges.pop();
		else
		{
			
			Visited[neighbour.GetNeighbourNode()] = true;
			mst.insert({ neighbour.GetNode(), neighbour.GetNeighbourNode() });
			totalCostTree += neighbour.GetCost();
			currentnode = neighbour.GetNeighbourNode();
			edges.pop();
			auto iterator = m_Edges.equal_range(currentnode);
			for (auto index = iterator.first; index != iterator.second; ++index)
			{
				node = index->first;
				cost = index->second.first;
				neighbournode = index->second.second;
				if(!Visited[neighbournode])
				edges.push({ node,neighbournode,cost });
			}
		}

	}

	std::cout << "The minimum spanning tree(Prim Algorithm) is:";
	for (const auto& iterator : mst)
	{
		node = iterator.first;
		neighbournode = iterator.second;
		std::cout << '(' << node << ',' << neighbournode << ')' << ' ';
	}
	std::cout << "\nThe total cost is:" << totalCostTree;

}
