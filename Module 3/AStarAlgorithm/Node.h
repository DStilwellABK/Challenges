#pragma once
#include "Position.h"
#include <list>


class Node {
public:
	Node();

	void ConnectNode(Node nodeToConnect);

	// Makes it so that 2 nodes can be compared;
	bool operator==(const Node& rhs) const;

	bool CheckIfNodeIsConnected();

private:
	Position nodePosition;
	std::list<Node> connectingNodes;
};

