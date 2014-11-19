#include "stdafx.h"
#include "Serializer.h"
#include "Model.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace cs3103 {

	Serializer::Serializer(void)
	{
	}

	Serializer::~Serializer(void)
	{
	}

	void Serializer::SerializeTask1(Model& model) {
		ofstream file(".//outputs//output_task1.txt");
		file << "TASK 1" << endl;
		file << "(These paths below are not in input order, they were sorted to increase performance)" << endl;
		for (int i = 0; i < model.getNumberOfPath(); i++) {
			vector<int> path = model.getPath(i);
			for (int j = 0; j < path.size(); j++) {
				file << path[j] << " ";
			}
			file << endl;
		}
		file << endl;
		file << "Number of ASes: " << model.getNumberOfNode() << endl;
		file << "Number of Paths: " << model.getNumberOfPath() << endl;
		file.close();
	}

	void Serializer::SerializeTask2(Model& model, vector<int> nodes) {
		ofstream file(".//outputs//output_task2.txt");
		file << "TASK 2" << endl;
		file << "Top ten ASes which have biggest degree:" << endl;
		for (int i = 0; i < nodes.size(); i++) {
			file << i + 1 << ".\t" << "Degree: " << model.getNodeDegree(nodes[i])<< "\t\t AS: " << nodes[i] << endl;
		}
		file.close();
	}

	void Serializer::SerializeTask3(Model& model) {
		ofstream file(".//outputs//output_task3.txt");
		file << "TASK 3" << endl;
		vector<int> nodes = model.getAllNodes();
		for (int i = 0; i < nodes.size(); i++) {
			map<int, EdgeInfo> neighbours = model.getEdges(nodes[i]);
			for (std::map<int, EdgeInfo>::iterator it = neighbours.begin(); it != neighbours.end(); ++it) {
				string edgeType = "Undirected";
				switch (it->second.edgeType) {
				case EdgeType::C2P: edgeType = "c2p"; break;
				case EdgeType::P2C: edgeType = "p2c"; break;
				case EdgeType::P2P: edgeType = "p2p"; break;
				case EdgeType::S2S: edgeType = "s2s"; break;
				}
				file << nodes[i] << " " << it->first << " " << edgeType.c_str() << endl;
			}
		}
	}

	void Serializer::SerializeTask4(Model& model) {
		ofstream file(".//outputs//output_task4.txt");
		file << "TASK 4" << endl;
		vector<int> nodes = model.getAllNodes();
		for (int i = 0; i < nodes.size(); i++) {
			map<int, EdgeInfo> neighbours = model.getEdges(nodes[i]);
			string nodeType = "Undefined";
			switch (model.getNodeType(nodes[i])) {
			case NodeType::Core: nodeType = "Core"; break;
			case NodeType::DenseCore: nodeType = "Dense Core"; break;
			case NodeType::OuterCore: nodeType = "Outer Core"; break;
			case NodeType::RegionalIsp: nodeType = "Regional ISP"; break;
			case NodeType::Stub: nodeType = "Stub"; break;
			case NodeType::TransitCore: nodeType = "Transit Core"; break;
			}
			file << nodes[i] << " " << nodeType.c_str() << endl;
		}
	}

}