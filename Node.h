#pragma once
#include <vector>

class Node
{
private:
	Node();
public:

	enum Status {
		NULL_AREA,
		WALL,
		GOAL,
		START,
		NORMAL
	};


	
	Node(int posX, int posY,Status status);

	int posX, posY;
	int fCost;
	int hCost;
	int gCost;

	Node * backTrackedPath;
	Node * parent;

	Status status;

	std::vector<int> FindNeighbours();
	void CalculateFCost();
	void CalculateHCost(int goalX,int goalY);
	void CalculateGCost();
	void SetParent(Node * parent);


};
