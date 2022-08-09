#include <iostream>
#include "Node.h"

Node::Node() :
	nodePosition(Position()),
	connectingNodes(std::list<Node>())
{

}

void Node::ConnectNode(Node nodeToConnect) {

}

bool Node::operator==(const Node& rhs) const {
	return nodePosition.x() == rhs.nodePosition.x() && nodePosition.y() == rhs.nodePosition.y();
}

bool Node::CheckIfNodeIsConnected() {
	for (Node connectingNode : connectingNodes) {
		if (connectingNode == this)
	}
}