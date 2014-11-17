#pragma once
#include <vector>
#include <iostream>
#include <map>

using namespace std;

namespace cs3103 {
	class Parser
	{
	private:
		vector< vector<int> > paths;
		map <int, vector<int>> nodes;

	public:
		Parser(void);
		~Parser(void);
		void parse(string fileName);
	};
}
