#pragma once

class Edge
{
private:
	unsigned m_index1;
	unsigned m_index2;
public:
	Edge(unsigned index1, unsigned index2);

	unsigned GetIndex1() const { return m_index1; }
	unsigned GetIndex2() const { return m_index2; }
};