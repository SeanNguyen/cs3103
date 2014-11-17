#pragma once
#include <vector>
#include <map>

using namespace std;

namespace cs3103 {

	class Model
	{
	private:
		vector< vector<int> > paths;
		map <int, vector<int>> nodes;

	public:
		Model(void);
		~Model(void);
		void insertPath(vector<int> path);
		bool isPathExist(vector<int> path);
		int getNumberOfPath();
		int getNumberOfNode();
		vector<int> getPath(int index);

	private:
		int binarySearch(vector<int> path, int imax, int imin);
		int comparePath (vector<int> path1, vector<int> path2);
	};

}