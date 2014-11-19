#pragma once
#include "Model.h"

namespace cs3103 {

	class Serializer
	{
	public:
		Serializer(void);
		~Serializer(void);

		void SerializeTask1(Model& model);
		void SerializeTask2(Model& model, vector<int> nodes);
		void SerializeTask3(Model& model);
		void SerializeTask4(Model& model);
	};

}