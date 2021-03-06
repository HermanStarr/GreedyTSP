//Salesman by Kamil Szymoniak
//18-01-2019
/** @file */
#include "functions.h"

/**	Function main checks command line arguments and initiazes program
	@param argc command line argument
	@param argv[] listed command line arguments */
int main(int argc, char* argv[])
{

	int counter = 0;
	double totalDistance = 0;
	firstClient* listedDistances = nullptr;
	std::string inputFile;
	std::string outputFile;
	int numb;
	bool input = false;
	bool output = false;
	if (checkParameters(argc, argv, inputFile, outputFile) == true)
	{
		numb = getN(inputFile);
		if (numb == -1)
			return 0;
		fill(listedDistances, numb);
		readFile(listedDistances, inputFile);
		std::ofstream file;
		file.open(outputFile);
		minimalCost(1, file, listedDistances, outputFile, counter, numb, totalDistance);
		file.close();
		deleteStructs(listedDistances);
	}
	else
		std::cout << std::endl << "Incorrect parameters";
	return 0;
}
