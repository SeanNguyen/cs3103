//A0088441B - Nguyen Trong Son
#include "stdafx.h"
#include "Model.h"
#include <math.h>
#include <iostream>

namespace cs3103 {

	Model::Model(void)
	{
	}

	Model::~Model(void)
	{
	}

	void Model::insertPath(vector<int> path) {
		//insert nodes and edges
		nodes[path[0]];
		for (int i = 0; i < path.size() - 1; i++) {
			nodes[path[i]].neighbours[path[i + 1]];
			nodes[path[i + 1]].neighbours[(path[i])];
		}

		////inster path in a sorted order
		int insertIndex = binarySearchInsertPoistion(path, paths);
		paths.insert(paths.begin() + insertIndex, path);
	}

	bool Model::isPathExist(vector<int> path) {
		return binarySearch(path, paths) != -1;
	}

	int Model::getNumberOfPath() {
		return paths.size();
	}

	int Model::getNumberOfNode() {
		return nodes.size();
	}

	vector<int> Model::getPath(int index) {
		if (index < 0 && index >= paths.size()) {
			throw;
		}
		return paths[index];
	}

	vector<int> Model::getAllNodes() {
		vector<int> result;
		for (std::map<int, NodeInfo>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			result.push_back(it->first);
		}
		return result;
	}

	map<int, EdgeInfo> Model::getEdges(int node) {
		if (nodes.count(node) == 0) {
			throw;
		}
		return nodes[node].neighbours;
	}

	int Model::getNodeDegree(int node) {
		if (nodes.count(node) == 0) {
			throw;
		}
		return nodes[node].neighbours.size();
	}

	int Model::getTransit(int node1, int node2) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		return nodes[node1].neighbours[node2].transit;
	}

	EdgeType Model::getEdgeType(int node1, int node2) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		return nodes[node1].neighbours[node2].edgeType;
	}

	int Model::getNotPeering(int node1, int node2) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		return nodes[node1].neighbours[node2].notPeering;
	}

	NodeType Model::getNodeType(int node) {
		if (nodes.count(node) == 0) {
			throw;
		}
		return nodes[node].type;
	}

	int Model::getNumberOfEdge() {
		int count = 0;
		for (std::map<int, NodeInfo>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			count += it->second.neighbours.size();
		}
		return count / 2;
	}

	double Model::getAveragePathLength() {
		int total = 0;
		for (int i = 0; i < paths.size(); i++) {
			total += paths[i].size();
		}
		return (double)total / paths.size();
	}

	bool Model::setTransit(int node1, int node2, int value) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		nodes[node1].neighbours[node2].transit = value;
		return true;
	}

	bool Model::setEdgeType(int node1, int node2, EdgeType edgeType) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		if (edgeType == EdgeType::C2P) {
			nodes[node1].neighbours[node2].edgeType = C2P;
			nodes[node2].neighbours[node1].edgeType = P2C;
		} else if (edgeType == EdgeType::P2C) {
			nodes[node1].neighbours[node2].edgeType = P2C;
			nodes[node2].neighbours[node1].edgeType = C2P;
		} else {
			nodes[node1].neighbours[node2].edgeType = edgeType;
			nodes[node2].neighbours[node1].edgeType = edgeType;
		}
		return true;
	}

	bool Model::setNotPeering(int node1, int node2, int value) {
		if (nodes[node1].neighbours.count(node2) == 0) {
			throw;
		}
		nodes[node1].neighbours[node2].notPeering = value;
		return true;
	}

	bool Model::setNodeType(int node, NodeType type) {
		if (nodes.count(node) == 0) {
			throw;
		}
		nodes[node].type = type;
		return true;
	}

	//Private support methods

	int Model::binarySearchInsertPoistion(vector<int> &element, vector<vector<int>> &list) {
		int imin = 0;
		int imax = list.size() - 1;
		while (imax >= imin) {
			int imid = (imax + imin) / 2;
			if (comparePath(element, list[imid]) == 1) {
				if (imid == list.size() - 1) {
					return imid;
				} else if (comparePath(element, list[imid + 1]) == -1) {
					return imid + 1;
				} else {
					imin = imid + 1;
				}
			} else {
				if (imid == 0) {
					return 0;
				} else if (comparePath(element, list[imid - 1]) == 1) {
					return imid;
				} else {
					imax = imid -1;
				}
			}
		}
		return 0;
	}

	int Model::binarySearch(vector<int> &element, vector<vector<int>> &list) {
		int imin = 0;
		int imax = list.size() - 1;
		while (imax >= imin) {
			// calculate the midpoint for roughly equal partition
			int imid = (imax + imin) / 2;
			if(comparePath(element, list[imid]) == 0) {
				// key found at index imid
				return imid; 
				// determine which subarray to search
			} else if (comparePath(element, list[imid]) == 1) {
				// change min index to search upper subarray
				imin = imid + 1;
			} else         
				// change max index to search lower subarray
				imax = imid - 1;
		}
		// key was not found
		return -1;
	}

	//return -1 mean path1 < path2, 0 means path1 = path2, 1 means path1 > path2
	int Model::comparePath(vector<int> path1, vector<int> path2) {
		int minSize = min(path1.size(), path2.size());
		for (int i = 0; i < minSize; i++) {
			if (path1[i] < path2[i]) {
				return -1;
			} else if (path1[i] > path2[i]) {
				return 1;
			}
		}
		if (path1.size() < path2.size()) {
			return -1;
		} else if (path1.size() > path2.size()) {
			return 1;
		}
		return 0;
	}
}