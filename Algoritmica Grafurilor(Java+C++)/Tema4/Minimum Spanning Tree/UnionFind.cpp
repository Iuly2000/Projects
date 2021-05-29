#include "UnionFind.h"

uint16_t UnionFind::Find(uint16_t node)
{
	uint16_t root = node;
	while (root != m_parent[root]) 
		root = m_parent[root];

	while (node != root) 
	{
		uint16_t next = m_parent[node];
		m_parent[node] = root;
		node = next;
	}

	return root;
}

UnionFind::UnionFind(uint16_t size)
{

	if (size <= 0) throw ("Size <= 0 is not allowed");

	m_size = size;
	m_sz.resize(size);
	m_parent.resize(size);

	for (uint16_t index = 0; index < size; index++)
	{
		m_parent[index] = index;
		m_sz[index] = 1; 
	}
}

bool UnionFind::Connected(uint16_t node, uint16_t node2)
{
	return Find(node) == Find(node2);
}

void UnionFind::Unify(uint16_t node1, uint16_t node2)
{

	if (Connected(node1, node2)) return;

	uint16_t root1 = Find(node1);
	uint16_t root2 = Find(node2);

	if (m_sz[root1] < m_sz[root2]) {
		m_sz[root2] += m_sz[root1];
		m_parent[root1] = root2;
	}
	else {
		m_sz[root1] += m_sz[root2];
		m_parent[root2] = root1;
	}


}

