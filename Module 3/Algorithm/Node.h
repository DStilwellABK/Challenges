#pragma once

class Node {
public:
	char x;
	char y;
	int m_cost;

	Node(char _x, char _y, int _cost);

	void DisplayNode();
	bool CompareNode(Node secondNode);
};