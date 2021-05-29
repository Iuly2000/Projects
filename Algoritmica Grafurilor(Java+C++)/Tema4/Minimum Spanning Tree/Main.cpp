#include "Graph.h"

int main()
{
	Graph g;
	g.ReadGraph();
	g.Kruskal();
	std::cout << '\n';
	g.Prim();
	
	return 0;
}