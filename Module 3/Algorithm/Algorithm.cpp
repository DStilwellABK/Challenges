#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <list>
#include "Node.h"

using namespace std;
using namespace std::this_thread;




// TODO: Implement a sorting algorithm using this
uint32_t GetNanos();
//void BubbleSearch(int arrayToSort[], int size);

// For A* Pathfinding
void FindShortestPath(list<Node> positions, char start, char end);

void DisplayResults(char start, char end, int cost);
Node CreateNewNode(char x, char y, int cost);

// TODO: Make sure to add user input on what nodes list goes in and then what path to search (a -> b, b -> c
int main()
{
	int numberOfNodes = 0;
	cout << "How many nodes do you want to add?: ";
	while (numberOfNodes == 0) {
		cin >> numberOfNodes;
	}


	char x = 'a';
	char y = 'b';
	//User will setup nodes with a start and end x = start, y = end, cost = cost to that node.
	cout << "Choose a start node character, an end node character, and a number cost to that node. Make sure to hit enter after enter each of." << endl;
	cout << "EX: a b 5, a as the start, b is the end, and 5 is the cost" << endl;
	list<Node> userNodes;
	for (int i = 0; i < numberOfNodes; i++)
	{
		// Check now what path the user wants to go ( Ex: A - > c )

		int cost = 0;
		cout << endl;
		cin >> x;
		cin >> y;
		cin >> cost;
		userNodes.push_back(CreateNewNode(x,y,cost));
	}

	cout << "Now give a start and end positionn that you want to go to (EX: A -> b): ";
	cin >> x;
	cin >> y; 

	cout << endl;

	if (userNodes.size() > 0) {
		FindShortestPath(userNodes, x, y);
	}
}

Node CreateNewNode(char x, char y, int cost) {
	return Node(x,y,cost);
}

//void BubbleSearch(int arrayToSort[], int size){
//	for (int pass = 0; pass < size; pass++)
//	{
//
//	}
//}

void FindShortestPath(list<Node> positions, char start, char end) {
	bool foundAllPaths = false;
	int totalCost = 0;

	// This will be needed for each of the paths that holdes each of the nodes so the path from a > b > c as well as a > d > c in getting from a to c
	list<list<Node>> paths;

	list<Node> finalPath;
	list<Node> possibleNodes = positions;
	// If our starting position in positions is the same as the positions
	if (positions.front().x == start && positions.front().y == end) {
		totalCost = positions.front().m_cost;
	}
	else {
		// While we haven't found all paths to add
		while (!foundAllPaths) {
			
			bool foundPathToAdd = false;
		
			// Current Start of a new path
			char currentStart = start;
			
			// Create a new path for just in case
			list<Node> newPath = list<Node>();
			// Use a temp list that the for loop will go through completely
			list<Node> searchNodes = possibleNodes;
			// Start to look for a new path.
			for (Node possibleNode : searchNodes)
			{

				if (possibleNode.x == currentStart) {
					// Add in the possibleNode to the newPath
					possibleNode.DisplayNode();
					newPath.push_back(possibleNode);
					
					// Set the new start possibleNode to y ex: a -> b and making b the start possibleNode to look for b -> c
					currentStart = possibleNode.y;

					// Just resetting the list so that the current possibleNode found is removed from the possibleNodes 
					// TODO: Refactor this to run just one loop completely removing all the items from this new path on possible nodes to look for
					list<Node> tempPossibleNodes;
					for (Node _possibleNode : possibleNodes)
					{
						if (!possibleNode.CompareNode(_possibleNode)) {
							tempPossibleNodes.push_back(_possibleNode);
						}
					}
					possibleNodes = tempPossibleNodes;

					// Let the loop know that we have a path to go on. 
					if (!foundPathToAdd)
						foundPathToAdd = true;

					

					// If we're at the c of a -> b -> c then break from the loop, and itterate on while loop to search a new path.
					if (possibleNode.y == end) break;
				}


			}
			
			// We found a new path? Well then lets add that to the list of paths that we have now.
			if (foundPathToAdd) {
				paths.push_back(newPath);
			}
			// If we found a path to add, continue to keep found all paths false. Else if foundPathToAdd is false, it'll return true on found all paths
			// Making it so we stop searching for paths.
			//cout << foundPathToAdd << endl;
			foundAllPaths = !foundPathToAdd;
		}
	}
	// Go through and find the lowest cost
	int lowestCost = NULL;
	if (paths.size() > 0) {
		for (list<Node> path : paths)
		{
			int cost = 0;
			// Go through each of the nodes in this path to calculate the cost of that path EX: A->b += 5 b->c += 1 making a total of cost = 6
			for (Node position : path) {
				cost += position.m_cost;
				//position.DisplayNode();
				cout << endl;
			}

			// Make sure we're not using a null interger
			if (lowestCost == NULL) {
				lowestCost = cost;
				totalCost = cost;
			}
			// If we aren't then did we find a new lowest cost?
			else if (lowestCost > cost) {
				totalCost = cost;
				lowestCost = cost;
				finalPath = path;
			}
		}
	}


	// Determine the final cost

	DisplayResults(start, end, totalCost);

}


void DisplayResults(char start, char end, int cost) {
	system("cls");
	cout << endl;
	cout << "RESULTS: " << endl;
	cout << " * Starting position: " << start << endl;
	cout << " * Ending position: " << end << endl;
	cout << " * Minimum cost to end position: " << cost << endl;
}

uint32_t GetNanos() {
	using namespace chrono;
	return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

