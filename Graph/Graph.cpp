#include "Graph.h"
#include <unordered_set>
#include <functional>
#include <memory>

class Graph::GraphImpl
{
public:
	explicit GraphImpl() : m_nodes(), m_numEdges(0) {
	}
	bool hasNode(const size_t node) const {
		const std::unique_ptr<GraphNode> nodePtr(new GraphNode(node));
		return m_nodes.find(nodePtr.get()) != m_nodes.end();
	}

	void addEdge(const int from, const int to) {
		std::unique_ptr<GraphNode> node(new GraphNode(from));
		auto it = m_nodes.find(node.get());
		if (it != m_nodes.end()) {
			(*it)->addNeighbor(to);
			m_numEdges++;
		} else {
			node->addNeighbor(to);
			m_nodes.insert(node.release());
		}
	}
	void removeEdge(const int from, const int to) {
		std::unique_ptr<GraphNode> node(new GraphNode(from));
		auto it = m_nodes.find(node.get());
		if (it != m_nodes.end()) {
			(*it)->removeNeighbor(to);
			m_numEdges--;
		}
	}

	const size_t getNumVertices() const
	{
		return m_nodes.size();
	}

	const size_t getNumEdges() const
	{
		return m_numEdges;
	}

	const std::unordered_set<size_t> getNeighbors(const size_t node) const
	{
		std::unique_ptr<GraphNode> nodePtr(new GraphNode(node));
		auto it = m_nodes.find(nodePtr.get());
		return (*it)->getNeighbors();
	}
private:
	class GraphNode {
		size_t m_nodeId;
		std::unordered_set<size_t> m_neighborNodes;
	public:
		explicit GraphNode(const int nodeId) : 
		m_nodeId(nodeId), m_neighborNodes() {}


		const int getNodeId() const {
			return m_nodeId;
		}

		void addNeighbor(const size_t newNeighbor)
		{
			m_neighborNodes.insert(newNeighbor);
		}

		void removeNeighbor(const size_t neighbor)
		{
			m_neighborNodes.erase(neighbor);
		}

		const size_t getNumNeighbors() const 
		{
			return m_neighborNodes.size();
		}

		const std::unordered_set<size_t> getNeighbors() const
		{
			return m_neighborNodes;
		}
	};
	struct AreNodeSame
	{
		bool operator()(const GraphNode * lhs, const GraphNode * right)
		{
			return lhs->getNodeId() == right->getNodeId();
		}
	};
	struct Hasher
	{
		size_t operator()(const GraphNode *node)
		{
			return std::hash<size_t>()(node->getNodeId());
		}
	};
	std::unordered_set<GraphNode *, Hasher, AreNodeSame> m_nodes;
	size_t m_numEdges;
};

Graph::Graph() : m_pImpl(new Graph::GraphImpl()) {
}

void Graph::addEdge(const int from, const int to) {
	m_pImpl->addEdge(from, to);
}

void Graph::removeEdge(const int from, const int to) {
	m_pImpl->removeEdge(from, to);
}

const size_t Graph::getNumVertices() const
{
	return m_pImpl->getNumVertices();
}

const size_t Graph::getNumEdges() const
{
	return m_pImpl->getNumEdges();
}

const std::unordered_set<size_t> Graph::getNeighbors(const size_t node) const
{
	return m_pImpl->getNeighbors(node);
}