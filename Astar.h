#pragma once
#include "Node.h"
#include <vector>

using namespace std;
class Astar
{
private:
	vector<Node*> openList;
	vector<Node*> closedList;
	Node* goalNode;
	Node* startNode;
public:

	Astar(Node * startNode,Node *  goalNode,int borderX,int borderY);
	//Node Array
	vector<Node*> Find();

};

