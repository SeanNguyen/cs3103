// CS3103.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"

using namespace cs3103;

int _tmain(int argc, _TCHAR* argv[])
{
	Parser parser;
	Model model;
	parser.parse("input.txt", model);

	int pathSize = model.getNumberOfPath();
	for (size_t i = 0; i < pathSize; i++) {
		vector<int> path = model.getPath(i);
		for (size_t j = 0; j < path.size(); j++) {
			cout << path[j] << " ";
		}
		cout << endl;
	}

	cout << "Number of ASes: " << model.getNumberOfNode() << endl;
	cout << "Number of paths: " << pathSize << endl;
	cin.get();
	return 0;
}

