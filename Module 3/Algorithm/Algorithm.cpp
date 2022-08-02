#include <iostream>
#include <chrono>
#include <list>
#include "Position.h"

using namespace std;





uint32_t GetNanos();
//void BubbleSearch(int arrayToSort[], int size);

// For A* Pathfinding
void FindShortestPath(Position _positions, char start, char end, int size);

void DisplayResults(char start, char end, int cost);

int main()
{
	bool finishedAddingNodes = false;
	list<Position> userNodes;
	while (!finishedAddingNodes) {
		char x, y;
		string cost;
		cin >> x, y, cost;

		string answer;
		if (answer == )
	}

	if (userNodes.size() > 0) {

	}
}

//void BubbleSearch(int arrayToSort[], int size){
//	for (int pass = 0; pass < size; pass++)
//	{
//
//	}
//}

void FindShortestPath(Position positions, char start, char end, int size) {

	bool foundAllPaths = false;
	list<list<Position>> paths;

	list<Position> finalPath;

	// If our starting position in positions is the same as the positions
	if (positions[0].x == start && positions[0].y == end) {

	}
	else {
		// While we haven't found all paths to add
		while (!foundAllPaths) {
			
			bool foundPathToAdd = false;
		
			// Current Start of a new path
			char currentStart = start;
			
			// Start to look for a new path.
			list<Position> newPath = list<Position>();
			for (Position position : positions)
			{
				// The current position has not been used yet (Say a -> b -> c then a -> d -> c)
				if (!position.m_found) {
					if (position.x == currentStart) {
						// Add in the position to the newPath
						newPath.push_back(position);

						// Set the new start position to y ex: a -> b and making b the start position to look for b -> c
						currentStart = position.y;
						
						// Let the loop know this path has been found.
						position.m_found = true;

						// Let the loop know that we have a path to go on. 
						if (!foundPathToAdd)
							foundPathToAdd = true;

						// If we're at the c of a -> b -> c then break from the loop, and itterate on while loop to search a new path.
						if (position.y == end) break;
					}
				}
	
			}

			// If we found a path to add, continue to keep found all paths false. Else if foundPathToAdd is false, it'll return true on found all paths
			// Making it so we stop searching for paths.
			foundAllPaths = !foundPathToAdd;
		}

	}
	// Go through and find the lowest cost
	int lowestCost = NULL;
	for (list<Position> path : paths)
	{
		int cost = 0;
		for (Position position : path) {
			cost += position.m_cost;
		}

		// Make sure we're not using a null interger
		if (lowestCost == NULL) {
			lowestCost = cost;
		}
		// If we aren't then did we find a new lowest cost?
		else if (lowestCost > cost) {
			lowestCost = cost;
			finalPath = path;
		}
	}


	// Determine the final cost
	int totalCost = 0;
	for (Position position : finalPath)
	{
		totalCost += position.m_cost;
	}

	DisplayResults(start, end, totalCost);

}


void DisplayResults(char start, char end, int cost) {
	cout << "Starting position: " << start << endl;
	cout << "Ending position: " << end << endl;
	cout << "Minimum cost to end position: " << cost << endl;
}

uint32_t GetNanos() {
	using namespace chrono;
	return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

