/** @file */

#include "structs.h"

/** Function deletes distances structures
	@param distance pointer to first element of distances structure connected to firstClient */
void deleteDistances(distances* distance);

/** Function deletes firstClient structures
	@param listedDistances pointer to first element of firstClient structure */
void deleteStructs(firstClient* listedDistances);

/** Function searches for specified firstClient element
*	return pointer to this element
	@param i number of client
	@param listedDistances pointer to first element of firstClient structure */
firstClient* searchNode(int i, firstClient*&listedDistances);

/**	Function searches for the client which in return would give the shortest route, updates total distance value
*	returns number of next client to be visited
	@param c number of client, that has been just visited
	@param listedDistances pointer to first element in firstClient
	@param totalDistance total distance covered by salesman so far */
int leastEffort(int c, firstClient*&listedDistances, double&totalDistance);

/** Functions searches for the distance between the last client and HQ
*	returns distance value
	@param header pointer to firstClient element*/
double returnToHQ(firstClient*&header);

/**	Function marks client as visited, writes him into the output file,
*	runs a function to detect the best route from this client and writes total distance to output file
	@param c number of client, that has been just visited 
	@param file output file name
	@param listedDistances 
	@param name name of output file
	@param counter checks if all clients have been visited
	@param numb number of clients
	@param totalDistance total distance covered by salesman so far */
void minimalCost(int c, std::ofstream&file, firstClient*&listedDistances, std::string name, int counter, int numb, double&totalDistance);

/** Function adds information about route to the second client, distance and nature of route
	@param header pointer to first element in distances connected to firstClient
	@param nxtCli next client number
	@param dist distance between first and second client
	@param check variable indicating uni or bidirectionality*/
void addDistance(distances * header, int nxtCli, double dist, bool check);

/** Function reads the file to get each number of first and second client along with distance between them and nature of the connection
*	Function also fills mirror route, if possible
	@param header pointer to first firstClient element
	@param input input file name */
void readFile(firstClient*header, const std::string&input);

/**	Function creates distances structs connected to firstClient and those structs are filled with ensuing client numbers and distances set to "0"
*	returns pointer to next element
	@param numb number of clients
	@param header pointer to first element in connected struct*/
distances* fillDist(int numb, distances*header);

/** Function creates structs firstClient with ensuing client numbers, marks them as not visited and add connected distance structures
	@param listedDistances pointer to first element in firstClient struct
	@param numb number of clients */
void fill(firstClient*&listedDistances, int numb);

/** Function reads the number of all clients from the file
	*returns number of clients
	@param input name of input file */
int getN(const std::string&input);

/** Function checks implementation of in/out files and, if needed, creates output file
	*returns bool to indice if in/out files were called properly
	@param argc number of an argument
	@paarm argv[] content of an argument
	@param inputFile name of the input file
	@param outputFile name of the output file */
bool checkParameters(int argc, char*argv[], std::string&inputFile, std::string&outputFile);