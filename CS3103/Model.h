#pragma once
#include <vector>
#include <map>

using namespace std;

namespace cs3103 {

	enum NodeType { Unassigned, Stub, RegionalIsp, Core, DenseCore, TransitCore, OuterCore };

	enum EdgeType { Undirected, P2C, C2P, P2P, S2S };

	struct EdgeInfo	{
		int transit;
		EdgeType edgeType;
		int notPeering;
	};

	struct NodeInfo {
		map <int, EdgeInfo> neighbours;
		NodeType type;
	};

	class Model
	{
	private:
		vector< vector<int> > paths;
		map< int, NodeInfo > nodes;

	public:
		Model(void);
		~Model(void);

		void insertPath(vector<int> path);
		
		int getNumberOfPath();
		int getNumberOfNode();
		
		bool isPathExist(vector<int> path);
		vector<int> getPath(int index);
		map<int, EdgeInfo> getEdges(int node);
		vector<int> getAllNodes();
		
		int getNodeDegree(int node);
		int getTransit(int node1, int node2);
		int getNotPeering(int node1, int node2);
		EdgeType getEdgeType(int node1, int node2);
		NodeType getNodeType(int node);

		bool setTransit(int node1, int node2, int value);
		bool setEdgeType(int node1, int node2, EdgeType edgeType);
		bool setNotPeering(int node1, int node2, int value);
		bool setNodeType(int node, NodeType type);

	private:
		int binarySearchInsertPoistion(vector<int> &element, vector<vector<int>> &list);
		int binarySearch(vector<int> &element, vector<vector<int>> &list);
		int comparePath (vector<int> path1, vector<int> path2);
	};

}