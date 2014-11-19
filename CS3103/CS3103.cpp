// CS3103.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Serializer.h"

using namespace cs3103;

void solveTask1(Model& model);
vector<int> solveTask2(Model& model);
void solveTask3(Model& model);
void solveTask4(Model& model);

int _tmain(int argc, _TCHAR* argv[]) {
	Model model;
	Serializer serializer;

	cout << "PROGRAM BEGIN !!!" << endl;
	cout << "Solving Task 1" << endl;
	solveTask1(model);
	cout << "Saving Task 1 result" << endl;
	serializer.SerializeTask1(model);

	cout << "Solving Task 2" << endl;
	vector<int> task2Result = solveTask2(model);
	cout << "Saving Task 2 result" << endl;
	serializer.SerializeTask2(model, task2Result);
	
	cout << "Solving Task 3" << endl;
	solveTask3(model);
	cout << "Saving Task 3 result" << endl;
	serializer.SerializeTask3(model);

	cout << "Solving Task 4" << endl;
	solveTask4(model);
	cout << "Saving Task 4 result" << endl;
	serializer.SerializeTask4(model);

	cout << "PROGRAM END !!!" << endl;
	cin.get();
}

void solveTask1(Model& model) {
	//TASK 1================================================================================================================
	Parser parser;
	parser.parse(".//inputs//2001.10.26.txt", model);
}

vector<int> solveTask2(Model& model) {
	//TASK 2================================================================================================================
	//The graph and degree are generated in the parsing phase in Task 1 
	//so now we only need to extract 10 ASes that have biggest degree
	vector <int> nodes = model.getAllNodes();
	vector <int> result(10, -1);
	for (int i = 0; i < nodes.size(); i++) {
		int pos = -1;
		for (int j = result.size() - 1; j >= 0; j--) {
			if (result[j] == -1 || model.getNodeDegree(nodes[i]) > model.getNodeDegree(result[j])) {
				pos = j;
			}
		}
		if (pos != -1) {
			result.insert(result.begin() + pos, nodes[i]);
		}
		if (result.size() > 10) {
			result.erase(result.begin() + 10);
		}
	}
	return result;
}

void solveTask3(Model& model) {
	//TASK 3 - Heuristic Algorithm==========================================================================================
	//Phase 1: Calculate degree of ASes (done in task 2)

	//Phase 2: Parse AS path to initialize consecutive AS's pair transit relationship
	//for each path
	int numberOfPath = model.getNumberOfPath();
	for (int i = 0; i < numberOfPath; i++) {
		vector<int> path = model.getPath(i);
		//find a node that has biggest degree
		int j = 0;
		for (int k = 0; k < path.size(); k++) {
			if (model.getNodeDegree(path[k]) > model.getNodeDegree(path[j])) {
				j = k;
			}
		}
		//set transit pairs
		for (int k = 0; k < j; k++) {
			int transitValue = model.getTransit(path[k], path[k + 1]) + 1;
			model.setTransit(path[k], path[k + 1], transitValue);
		}
		for (int k = j; k < path.size() - 1; k++) {
			int transitValue = model.getTransit(path[k + 1], path[k]) + 1;
			model.setTransit(path[k + 1], path[k], transitValue);
		}
	}

	//Phase 3: Assign relationship to AS pairs
	//for each AS path
	int L = 3;
	for (int i = 0; i < numberOfPath; i++) {
		vector<int> path = model.getPath(i);
		for (int k = 0; k < path.size() - 1; k++) {
			//if this pair of edges were processed, then skip
			if (model.getEdgeType(path[k], path[k + 1]) != EdgeType::Undirected) {
				continue;
			}
			int transit1 = model.getTransit(path[k], path[k + 1]);
			int transit2 = model.getTransit(path[k + 1], path[k]);
			if (transit2 > L && transit1 > L || (transit1 <= L && transit1 > 0 && transit2 <= L && transit2 > 0)) {
				model.setEdgeType(path[k], path[k + 1], EdgeType::S2S);
			} else if (transit2 > L || transit1 == 0) {
				model.setEdgeType(path[k], path[k + 1], EdgeType::P2C);
			} else if (transit1 > L || transit2 == 0) {
				model.setEdgeType(path[k], path[k + 1], EdgeType::C2P);
			}
		}
	}

	//Phase 4 (phase 2 of "Final Algorithm") Identify AS pairs that cannot hold peering relationship
	for (int i = 0; i < numberOfPath; i++) {
		vector<int> path = model.getPath(i);
		//find a node that has biggest degree
		int j = 0;
		for (int k = 0; k < path.size(); k++) {
			if (model.getNodeDegree(path[k]) > model.getNodeDegree(path[j])) {
				j = k;
			}
		}
		for (int k = 0; k < j - 1; k++) {
			model.setNotPeering(path[k], path[k + 1], 1);
		}
		for (int k = j + 1; k < path.size() - 1; k++) {
			model.setNotPeering(path[k], path[k + 1], 1);
		}
		if (j > 0 && j < path.size() - 1
			&& model.getEdgeType(path[j - 1], path[j]) != EdgeType::S2S
			&& model.getEdgeType(path[j], path[j - 1]) != EdgeType::S2S) 
		{
			if (model.getNodeDegree(path[j - 1]) > model.getNodeDegree(path[j + 1])) {
				model.setNotPeering(path[j], path[j + 1], 1);
			} else {
				model.setNotPeering(path[j - 1], path[j], 1);
			}
		}
	}

	//Phase 5 (Phase 3 of "Final Algorithm"): apply peering information
	int R = 2;
	for (int i = 0; i < numberOfPath; i++) {
		vector<int> path = model.getPath(i);
		for (int k = 0; k < path.size() - 1; k++) {
			if (model.getNotPeering(path[k], path[k + 1]) != 1 && model.getNotPeering(path[k + 1], path[k]) != 1
				&& model.getNodeDegree(path[k]) / model.getNodeDegree(path[k + 1]) < R
				&& model.getNodeDegree(path[k]) / model.getNodeDegree(path[k + 1]) > 1/R) 
			{
				model.setEdgeType(path[k], path[k + 1], EdgeType::P2P);
			}
		}
	}
}

void solveTask4(Model& model) {
	//TASK 4================================================================================================================
	vector<int> nodes = model.getAllNodes();

	//remove stub ASes
	for (int i = 0; i < nodes.size(); i++) {
		map<int, EdgeInfo> edges = model.getEdges(nodes[i]);
		bool isLeaf = true;
		//for each neighbour
		for (std::map<int, EdgeInfo>::iterator it = edges.begin(); it != edges.end(); ++it)	{
			EdgeType edgeType = it->second.edgeType;
			if (edgeType == EdgeType::P2C || edgeType == EdgeType::P2P || edgeType == EdgeType::S2S) {
				isLeaf = false;
				break;
			}
		}
		if (isLeaf) {
			model.setNodeType(nodes[i], NodeType::Stub);
			nodes.erase(nodes.begin() + i);
			i--;
		}
	}

	//remove Regional ISPs
	for (int i = 0; i < nodes.size(); i++) {
		map<int, EdgeInfo> edges = model.getEdges(nodes[i]);
		bool isRegionalIsp = true;
		for (std::map<int, EdgeInfo>::iterator it = edges.begin(); it != edges.end(); ++it)	{
			int neighbour = it->first;
			EdgeInfo edgeInfo = it->second;
			if (model.getNodeType(neighbour) != NodeType::Stub && edgeInfo.edgeType != EdgeType::C2P) {
				isRegionalIsp = false;
				break;
			}
		}
		if (isRegionalIsp) {
			model.setNodeType(nodes[i], NodeType::RegionalIsp);
			nodes.erase(nodes.begin() + i);
			i--;
		}
	}

	//set all residual ASes to Core
	for (int i = 0; i < nodes.size(); i++) {
		model.setNodeType(nodes[i], NodeType::Core);
	}

	//remove all dense core
	for (int i = 0; i < nodes.size(); i++) {
		map<int, EdgeInfo> edges = model.getEdges(nodes[i]);
		bool isDenseCore = true;
		for (std::map<int, EdgeInfo>::iterator it = edges.begin(); it != edges.end(); ++it)	{
			EdgeType edgeType = it->second.edgeType;
			if (edgeType == EdgeType::C2P) {
				isDenseCore = false;
				break;
			}
		}
		if (isDenseCore) {
			model.setNodeType(nodes[i], NodeType::DenseCore);
			nodes.erase(nodes.begin() + i);
			i--;
		}
	}

	//remove all Transit ASes
	for (int i = 0; i < nodes.size(); i++) {
		map<int, EdgeInfo> edges = model.getEdges(nodes[i]);
		for (std::map<int, EdgeInfo>::iterator it = edges.begin(); it != edges.end(); ++it)	{
			EdgeType edgeType = it->second.edgeType;
			int neighbour = it->first;
			if (edgeType == EdgeType::P2P && model.getNodeType(neighbour) == DenseCore 
				&& model.getNodeType(neighbour) == Core && model.getNodeType(neighbour) == TransitCore)
			{
				model.setNodeType(nodes[i], NodeType::TransitCore);
				nodes.erase(nodes.begin() + i);
				i--;
				break;
			}
		}
	}

	//Set all residual ASes to Outer Core
	for (int i = 0; i < nodes.size(); i++) {
		model.setNodeType(nodes[i], NodeType::OuterCore);
	}
}