/** @file */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

/** Structure describing all distances from client firstClient to second clients */
struct distances 
{
	/** Number of second client */
	int nextClientNumber;
	/** Distance needed to cover route from firstClient member to second client */
	double distance;
	/** Pointer to next  member of distances list */
	distances* next;
};

/** Structure describing each next starting client */
struct firstClient
{
	/** Number of first client */
	int clientNumber;
	/** Value describing if client was already visited */
	bool covered;
	/** Pointer to next member of firstClient struct*/
	firstClient* next;
	/** Pointer to first element of distances struct */
	distances* distancesToNextClients;
};