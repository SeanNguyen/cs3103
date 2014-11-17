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

	void Parser::parse(string fileName, Model &model) {
		ifstream infile(fileName);
		string line;
		while (getline(infile, line)) {
			if (line.find("{") != string::npos) {
				continue;
			}
			istringstream iss(line);
			string word;
			iss >> word; //this suppose to be "ASPATH:"
			vector<int> path;
			while (iss >> word) {
				int node = atoi(word.c_str());
				if (path.size() == 0 || find (path.begin(), path.end(), node) == path.end()) {
					path.push_back(node);
				}
			}
			if (!model.isPathExist(path)) {
				model.insertPath(path);
			}
		}
	}
}