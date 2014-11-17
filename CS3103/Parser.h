#pragma once
#include <vector>
#include <iostream>
#include <map>
#include "Model.h"

using namespace std;

namespace cs3103 {
	class Parser
	{

	public:
		Parser(void);
		~Parser(void);
		void parse(string fileName, Model &model);
	};
}
