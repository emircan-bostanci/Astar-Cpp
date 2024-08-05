#include "Node.h"
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

Node::Node(int posX, int posY, Status status) {
	this->posX = posX;
	this->posY = posY;
	this->status = status;
}


void Node::SetParent(Node * node) {
	this->parent = node;
}
void Node::CalculateFCost() {
	this->fCost = this->gCost + this->hCost;
}
void Node::CalculateGCost() {
	this->gCost = this->parent->gCost + 1;
}
void Node::CalculateHCost(int goalX,int goalY) {
	this->hCost = sqrt(pow(this->posX - goalX, 2) + pow(this->posY - posY, 2));
}
////=====================\\
//||	   2.xy          ||
//||1.xy [] [] [] 3.xy   ||
//||8.xy [] xx [] 4.xy	 ||
//||7.xy [] [] [] 5.xy   ||
//||	   6.xy          ||
//||=====================||
//
//__________________________
//==========================
//___________________________
//Returns neighbours positions
vector<Node> Node::FindNeighbours() 
{
	std::vector<Node> neighbours;

	for (int i = -1; i <= 1; i++) {
		for (int j = 1; j >= -1; j--) {
			if (i == 0 && j == 0) continue;
			int neighbourX = Node::posX + i;
			int neighbourY = Node::posY + j;
			auto node = Node(neighbourX,neighbourY,Status::NORMAL);
			node.SetParent(this);
			neighbours.push_back(node);
		}
	}

	for (auto i : neighbours) {
		cout << "Self Location X" << this->posX << "\n";
		cout << "Self Location Y" << this->posY << "\n";
		cout << "Neighbour Location : " << i.posX  <<" - "<< i.posY << "\n";
	}

	return neighbours;
}

