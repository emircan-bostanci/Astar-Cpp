#include "Astar.h"
#include <vector>
#include <algorithm>
using namespace std;




Astar::Astar(Node * start,Node * goal,int borderx,int borderY) {

}

/// <summary>
///	Finds optimal way according to Astar Search Algorithm 
/// </summary>
/// <returns>Return path with nodes</returns>
Node* Astar::Find() {
	while (this->openList.size() > 0) {
		sort(this->openList.begin(), this->openList.end());

	}

}
