#ifndef GRAPH_H
#define GRAPH_H

#include <memory>

class Graph
{
public:
	explicit Graph();
	bool hasNode(const size_t node) const;
	void addEdge(const int from, const int to);
	void removeEdge(const int from, const int to);
	const size_t getNumVertices() const;
	const size_t getNumEdges() const;
	const std::unordered_set<size_t> getNeighbors(const size_t node) const;
private:
	class GraphImpl;
	std::unique_ptr<GraphImpl> m_pImpl;
};

#endif