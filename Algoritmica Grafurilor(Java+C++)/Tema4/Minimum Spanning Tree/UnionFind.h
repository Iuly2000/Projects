#pragma once

#include <vector>
#include <cstdint>
class UnionFind
{
private:
	uint16_t m_size;
	std::vector<uint16_t> m_sz;
	std::vector<uint16_t> m_parent;
	uint16_t Find(uint16_t node);
public:
	UnionFind(uint16_t size);
	bool Connected(uint16_t node1, uint16_t node2);
	void Unify(uint16_t node1, uint16_t node2);

};

