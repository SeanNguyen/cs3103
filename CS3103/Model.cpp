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
		paths.push_back(path);
		for (size_t i = 0; i < path.size(); i++) {
			nodes[path[i]];
		}
		/*if (paths.empty()) {
			paths.push_back(path);
			return;
		}
		int imin = 0;
		int imax = paths.size() - 1;
		while (imax >= imin) {
			int imid = (imax + imin) / 2;
			if (comparePath(path, paths[imid]) == 1) {
				if (imid == paths.size() - 1) {
					paths.push_back(path);
					break;
				} else if (comparePath(path, paths[imid + 1]) == -1) {
					paths.insert(paths.begin() + imid + 1, path);
					break;
				} else {
					imin = imid + 1;
				}
			} else {
				if (imid == 0) {
					paths.insert(paths.begin(), path);
					break;
				} else if (comparePath(path, paths[imid - 1]) == 1) {
					paths.insert(paths.begin() + imid, path);
					break;
				} else {
					imax = imid -1;
				}
			}
		}*/
	}

	bool Model::isPathExist(vector<int> path) {
		//return binarySearch(path, paths.size() - 1, 0) != -1;
		for (size_t i = 0; i < paths.size(); i++) {
			if (comparePath(path, paths[i]) == 0)
				return true;
		}
		return false;
	}

	int Model::getNumberOfPath() {
		return paths.size();
	}

	int Model::getNumberOfNode() {
		return nodes.size();
	}

	vector<int> Model::getPath(int index) {
		if (index >= 0 && index < paths.size()) {
			return paths[index];
		}
		return vector<int>();
	}

	int Model::binarySearch(vector<int> path, int imax, int imin) {
		while (imax >= imin) {
			// calculate the midpoint for roughly equal partition
			int imid = (imax + imin) / 2;
			if(comparePath(path, paths[imid])) {
				// key found at index imid
				return imid; 
				// determine which subarray to search
			} else if (comparePath(path, paths[imid]) == 1) {
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
		for (size_t i = 0; i < minSize; i++) {
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