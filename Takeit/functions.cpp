/** @file */

#include "functions.h"

void deleteDistances(distances* distance)
{
	if (distance)
	{
		deleteDistances(distance->next);
		delete distance;
	}
}

void deleteStructs(firstClient* listedDistances)
{
	if (listedDistances)
	{
		deleteDistances(listedDistances->distancesToNextClients);
		deleteStructs(listedDistances->next);
		delete listedDistances;
	}
	
}

firstClient* searchNode(int i, firstClient*&listedDistances)
{
	auto header = listedDistances;
	while (header)
	{
		if (header->clientNumber == i)
		{
			return header;
		}
		header = header->next;
	}
	return nullptr;
}

int leastEffort(int c, firstClient*&listedDistances, double&totalDistance)
{
	auto variableDist = searchNode(c, listedDistances)->distancesToNextClients;
	auto variableFirstClient = listedDistances;
	int nextClient = INT_MAX;
	double minimalDistance = INFINITY, currentMin = 0;

	while (variableDist)
	{
		if (variableDist->distance != 0 && variableFirstClient->covered == 0)
		{
			if (2 * variableDist->distance < minimalDistance && searchNode(variableDist->nextClientNumber, listedDistances) != 0)
			{
				minimalDistance = returnToHQ(variableFirstClient) + variableDist->distance;
				currentMin = variableDist->distance;
				nextClient = variableDist->nextClientNumber;
			}
		}
		variableDist = variableDist->next;
		variableFirstClient = variableFirstClient->next;
	}
	if (minimalDistance != INFINITY)
	{
		totalDistance += currentMin;
	}
	return nextClient;
}

double returnToHQ(firstClient*&header)
{
	auto distances = header->distancesToNextClients;
	while (distances)
	{
		if (distances->nextClientNumber == 1)
			return distances->distance;
		distances = distances->next;
	}
	return -1;
}

void minimalCost(int c, std::ofstream&file, firstClient*&listedDistances, std::string name, int counter, int numb, double&totalDistance)
{
	auto header = searchNode(c, listedDistances);
	if (header == nullptr)
	{
		file.close();
		file.open(name);
		file << "Error, route is not possible";
		std::cout << "Error, route is not possible 1";
		return;
	}
	header->covered = true;
	std::cout << c << "--->";
	if (c == 1)
		file << c;
	else
		file << "--->" << c;
	counter++;
	int nextClient = leastEffort(c, listedDistances, totalDistance);
	if (totalDistance == INFINITY || totalDistance == 0)
	{
		file.close();
		file.open(name);
		file << "Error, route is not possible";
		std::cout << "Error, route is not possible 2";
		return;
	}

	if (nextClient == INT_MAX)
	{
		if (counter < numb)
		{
			file.close();
			file.open(name);
			file << "Error, route is not possible";
			std::cout <<std::endl<<counter<<std::endl<< numb << std::endl;
			std::cout << "Error, route is not possible 3";
			return;
		}
		nextClient = 0;
		std::cout << 1 << std::endl;
		file << "--->" << nextClient + 1;
		auto returnHQ = returnToHQ(header);
		if (returnHQ == -1 || returnHQ == 0)
		{
			file.close();
			file.open(name);
			file << "Error, route is not possible";
			std::cout << "Error, route is not possible 4";
			return;
		}
		else
			totalDistance += returnToHQ(header);
		file << std::endl << "cost: " << totalDistance;
		std::cout << "cost: " << totalDistance;
		return;
	}

	minimalCost(nextClient, file, listedDistances, name, counter, numb, totalDistance);
}

void addDistance(distances * header, int nxtCli, double dist, bool check)
{
	while (header)
	{
		if (header->nextClientNumber == nxtCli)
		{
			if (check == true)
			{
				break;
			}
			else
			{
				header->distance = dist;
				break;
			}
		}
		header = header->next;
	}
}

void readFile(firstClient*header, const std::string&input)
{
	std::ifstream file;
	std::string bi_or_uni;
	int client1, client2;
	double distance;
	char parenthese1, colon, parenthese2, pointBreak;
	bool check;

	file.open(input);
	if (file.good())
	{

		while (!file.eof())
		{
			file >> parenthese1 >> client1 >> bi_or_uni >> client2 >> colon >> distance >> parenthese2 >> pointBreak;

			if (bi_or_uni == "-")
				check = false;
			if (bi_or_uni == "->")
				check = true;
			if (bi_or_uni != "->" && bi_or_uni != "-")
			{
				std::cout << std::endl << "Input file: invalid data" << std::endl;
				return;
			}
			auto searched = searchNode(client1, header)->distancesToNextClients;
			addDistance(searched, client2, distance, false);
			searched = searchNode(client2, header)->distancesToNextClients;
			addDistance(searched, client1, distance, check);
		}

		file.close();
	}
	else
		std::cout << "error, file can not be opened";
}

distances* fillDist(int numb, distances*header)
{
	distances* first = nullptr;
	distances* next = nullptr;
	distances* temp = nullptr;
	for (int i = 1; i <= numb; i++)
	{
		if (!first)
		{
			next = new distances{ i, 0, nullptr };
			temp = next;
			first = next;
		}
		else
		{
			next = new distances{ i, 0, nullptr };
			temp->next = next;
			temp = temp->next;
		}
		
	}
	return first;
}

void fill(firstClient*&listedDistances, int numb)
{
	firstClient* n = nullptr;
	firstClient* temp = nullptr;

	for (int i = 1; i <= numb; i++)
	{
		if (!listedDistances)
		{
			n = new firstClient{ i, 0, nullptr, nullptr };
			n->distancesToNextClients = fillDist(numb, n->distancesToNextClients);
			temp = n;
			listedDistances = n;
		}
		else
		{
			n = new firstClient{ i, 0, nullptr, nullptr };
			n->distancesToNextClients = fillDist(numb, n->distancesToNextClients);
			temp->next = n;
			temp = temp->next;
		}
	}
}

int getN(const std::string&input)
{
	int numb = 0;
	std::ifstream file;
	char parenthese1;
	int client1;
	std::string uni_or_bi;
	int client2;
	char colon;
	double distance;
	char parenthese2;
	char pointBreak;
	file.open(input);


	if (file.good())
	{
		std::cout << "Client data is being read..." << std::endl;

		while (!file.eof())
		{
			file >> parenthese1 >> client1 >> uni_or_bi >> client2 >> colon >> distance >> parenthese2 >> pointBreak;

			if (uni_or_bi != "->" && uni_or_bi != "-")
			{
				std::cout << std::endl << "Input file: invalid data" << std::endl;
				return -1;
			}
			if (std::max(client1, client2) > 1000)
			{
				std::cout << std::endl << "Number of cities >1000, error" << std::endl;
				return -1;
			}
			if (numb < std::max(client1, client2))
				numb = std::max(client1, client2);
		}
		std::cout << "There are " << numb << " cities" << std::endl;
	}
	return numb;
}

bool checkParameters(int argc, char*argv[], std::string&inputFile, std::string&outputFile)
{
	bool input = false;
	bool output = false;
	for (int i = 0; i < argc; i++)
	{

		std::string arg = argv[i];
		std::cout << "  " << arg;
		if (arg == "-i")
		{
			inputFile = argv[i + 1];
			input = true;
		}
		if (arg == "-d")
		{
			outputFile = argv[i + 1];
			output = true;
		}
	}
	if (input == false)
	{
		std::cout << "No input file specified in command, exiting program" << std::endl;
		return false;
	}
	if (input == true && output == false)
	{
		std::cout << "No output file specified, creating new output file" << std::endl;
		outputFile = "output";
		std::ofstream newOutput{ outputFile };
		return true;
	}
	if (input == true && output == true)
	{
			return true;
	}
}