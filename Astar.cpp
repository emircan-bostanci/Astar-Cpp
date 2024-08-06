#include "Astar.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;




Astar::Astar(Node * start,Node * goal,int borderx,int borderY) {
	this->startNode = start;
	this->goalNode = goal;
	openList = vector<Node*>();
	closedList = vector<Node*>();
	openList.push_back(start);
}

/// <summary>
///	Finds optimal way according to Astar Search Algorithm 
/// </summary>
/// <returns>Return path with nodes</returns>
vector<Node*> Astar::Find() {
	while (this->openList.size() > 0) {
		auto selectedNode = openList[0];
		for (int i = 1; i < openList.size(); i++) {
			if (selectedNode->fCost > openList[i]->fCost) {
				selectedNode = openList[i];
			}
		}
		openList.erase(openList.begin());
		//Generating Neighbours
		vector<Node*> neighbours = selectedNode->FindNeighbours();
		for (int i = 0; i < neighbours.size(); i++) {
			if (neighbours[i]->posX == Astar::goalNode->posX && neighbours[i]->posY == Astar::goalNode->posY) {
				cout << "Reached Goal !";
				vector<Node* > path = vector<Node* >();
			 	auto item = closedList[closedList.size()-1];
				path.push_back(item);
				while (item->parent != NULL) {
					path.push_back(item);
					item = item->parent;
				}
				
				return path;

			}
			
			//Calculating Costs
			neighbours[i]->CalculateGCost();
			neighbours[i]->CalculateHCost(goalNode->posX,goalNode->posY);
			neighbours[i]->CalculateFCost();

			//Searching Item. If item exist on closed list skip otherwise add to openlist 
			bool isItemExist = false;
			if(closedList.size() > 0)
			for (int j = 0; j < closedList.size(); j++) {
				if (closedList[j]->posX == neighbours[i]->posX && closedList[j]->posY == neighbours[i]->posY) {
					isItemExist = true;
				}
			}
			if (isItemExist == true) {
				continue;
			}
			if (neighbours[i]->fCost > selectedNode->fCost) {
				continue;
			}
			else {
				openList.push_back(neighbours[i]);
			}
		}
		this->closedList.push_back(selectedNode);
	}
	return vector<Node*>();
}
