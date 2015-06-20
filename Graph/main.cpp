#include "Graph.h"

#include <iostream>

class GraphAlgorithm
{
public:
	virtual void execute(const Graph & g) = 0;
	virtual ~GraphAlgorithm() = 0 {

	}
};


class ShortestDistanceAlgorithm: public GraphAlgorithm {
public:
	ShortestDistanceAlgorithm(const size_t fromNode, const size_t toNode) : 
		m_fromNode(fromNode),
		m_toNode(toNode)
	{
	}

	virtual void execute(const Graph & g) {

	}

private:
	size_t m_fromNode;
	size_t m_toNode;
};

int main()
{
	Graph g();
}