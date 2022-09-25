#include "Set.h"
#include "Tester.h"

#include <iostream>


void test()
{
	Tester tester;

	tester.TestSetRead();
	tester.TestGrahamScan();
}


int main(int argc, char const* argv[])
{
#ifdef _DEBUG
	test();
#endif

	if (argc != 3)
	{
		std::cout << "Inccorect number of arguments\n"\
			"Correct order:\n"\
			"	1: Filename of input set of points\n"\
			"	2: Filename of output convex hull\n";

		return -1;
	}

	Set set;

	if (!set.ReadFromFile(argv[1]))
	{
		std::cout << "Wrong path to input file\n";
		return -2;
	}

	ConvexPolygon convexHull = set.ConvexHull();

	if (!convexHull.WriteToFile(argv[2]))
	{
		std::cout << "Wrong path to output file\n";
		return -2;
	}

	std::cout << "Succeeded!\n";
	return 0;
}
