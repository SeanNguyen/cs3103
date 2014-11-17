// CS3103.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"

using namespace cs3103;

int _tmain(int argc, _TCHAR* argv[])
{
	Parser parser;
	parser.parse("input.txt");
	cin.get();
	return 0;
}

