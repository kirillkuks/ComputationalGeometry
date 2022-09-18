#include "Tester.h"

#include <iostream>

void test()
{
	Tester tester;

	tester.TestPointAngleCompare();
	tester.TestPolygonRead();
	tester.TestIterators();
	tester.TestMinkowskiSum();
}


int main(int argc, char const* argv[])
{
	if (argc != 4)
	{
		std::cout << "Incorrect number of arguments\n"\
			"Correct order:\n"\
			"	1: Filename of first polygon\n"\
			"	2: Filename of second polygon\n"\
			"	3: Filename for output polygon\n";

		return -1;
	}

#ifdef _DEBUG
	test();
#endif

	ConvexPolygon firstPolygon;
	ConvexPolygon secondPolygon;

	if (!firstPolygon.ReadFromFile(argv[1]))
	{
		std::cout << "Wrogn path to first polygon\n";
		return -2;
	}

	if (!secondPolygon.ReadFromFile(argv[2]))
	{
		std::cout << "Wrong path to second polygon\n";
		return -2;
	}

	if (!ConvexPolygon::MinkowskiSum(firstPolygon, secondPolygon).WriteToFile(argv[3]))
	{
		std::cout << "Can not write to output file\n";
		return -3;
	}

	std::cout << "Succeeded!\n";
	return 0;
}
