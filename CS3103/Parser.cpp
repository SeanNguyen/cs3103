#include "stdafx.h"
#include "Parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace cs3103 {
	Parser::Parser(void)
	{
	}


	Parser::~Parser(void)
	{
	}

	void Parser::parse(string fileName) {

		ifstream infile(fileName);
		string line;
		while (getline(infile, line))
		{
			istringstream iss(line);
			string word;
			iss >> word;
			vector<int> path;
			int lastNode = -1;
			int currentNode;
			
			while (iss >> word) {
				currentNode = atoi(word.c_str());
				if (path.size() == 0 || path.back() != currentNode) {
					path.push_back(currentNode);
				}
				nodes[currentNode];
				if (lastNode != -1 && find(nodes[lastNode].begin(), nodes[lastNode].end(), currentNode) == nodes[lastNode].end()) {
					nodes[lastNode].push_back(currentNode);
				}
				lastNode = currentNode;
			}

			bool isDumplicated = false;
			for (size_t i = 0; i < paths.size(); i++) {
				vector <int> tempPath = paths[i];

				if (tempPath.size() != path.size()) {
					continue;
				}
				for (size_t j = 0; j < tempPath.size(); j++) {
					if (path[j] != tempPath[j]) {
						break;
					} else if (j == tempPath.size() - 1) {
						isDumplicated = true;
					}
				}
			}

			if (!isDumplicated) {
				paths.push_back(path);
				static int count = 1;
				cout << count++ << ":	";
				for (size_t i = 0; i < path.size(); i++) {
					cout << path[i] << " ";
				}
				cout << endl;
			}
		}
		cout << "Number of ASes: " << nodes.size() << endl;
		cout << "Number of paths: " << paths.size() << endl;
	}
}