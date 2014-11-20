//A0088441B - Nguyen Trong Son
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
		string data;
		infile.seekg(0, std::ios::end);   
		data.reserve(infile.tellg());
		infile.seekg(0, std::ios::beg);
		data.assign((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

		istringstream lines(data);
		string line;
		while (getline(lines, line)) {
			istringstream iss(line);
			string word;
			vector<int> path;
			bool isPathValid = true;

			iss >> word; //this suppose to be "ASPATH:"

			while (iss >> word) {
				int node = atoi(word.c_str());
				if (node == 0) {
					isPathValid = false;
					break;
				}
				if (path.size() == 0 || path.back() != node) {
					path.push_back(node);
				}
			}

			if (path.size() > 0 && isPathValid && !model.isPathExist(path)) {
				model.insertPath(path);
			}
		}
	}
}