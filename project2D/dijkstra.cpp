#include "dijkstra.h"
#include "Application2D.h"
#include <time.h>
#include <stdlib.h>

dijkstra::dijkstra() {}

dijkstra::~dijkstra() {}  

std::vector<dijkstra::Node*> dijkstra::graphStartup(int graphSize)
{

	graph.push_back(new Node(0, 300, 1000));
	graph.push_back(new Node(1, 500, 1000));
	graph.push_back(new Node(2, 700, 1000));
	graph.push_back(new Node(3, 900, 1000));
	graph.push_back(new Node(4, 1100, 1000));

	graph.push_back(new Node(5, 300, 800));
	graph.push_back(new Node(6, 500, 800));
	graph.push_back(new Node(7, 700, 800));
	graph.push_back(new Node(8, 900, 800));
	graph.push_back(new Node(9, 1100, 800));

	graph.push_back(new Node(10, 300, 600));
	graph.push_back(new Node(11, 500, 600));
	graph.push_back(new Node(12, 700, 600));
	graph.push_back(new Node(13, 900, 600));
	graph.push_back(new Node(14, 1100, 600));

	graph.push_back(new Node(15, 300, 400));
	graph.push_back(new Node(16, 500, 400));
	graph.push_back(new Node(17, 700, 400));
	graph.push_back(new Node(18, 900, 400));
	graph.push_back(new Node(19, 1100, 400));

	/**********************************************************
	***********************************************************/
	graph[0]->connections.push_back(Edge(graph[1], 10));
	graph[0]->connections.push_back(Edge(graph[5], 10));
	graph[0]->connections.push_back(Edge(graph[6], 1));

	graph[1]->connections.push_back(Edge(graph[2], 1));
	graph[1]->connections.push_back(Edge(graph[6], 1));
	graph[1]->connections.push_back(Edge(graph[7], 1));

	graph[2]->connections.push_back(Edge(graph[3], 1));
	graph[2]->connections.push_back(Edge(graph[7], 1));
	graph[2]->connections.push_back(Edge(graph[8], 1));

	graph[3]->connections.push_back(Edge(graph[4], 1));
	graph[3]->connections.push_back(Edge(graph[8], 1));
	graph[3]->connections.push_back(Edge(graph[9], 1));

	graph[4]->connections.push_back(Edge(graph[9], 1));

	/**********************************************************
	***********************************************************/

	graph[5]->connections.push_back(Edge(graph[6], 1));
	graph[5]->connections.push_back(Edge(graph[10], 1));
	graph[5]->connections.push_back(Edge(graph[11], 1));

	graph[6]->connections.push_back(Edge(graph[7], 1));
	graph[6]->connections.push_back(Edge(graph[11], 1));
	graph[6]->connections.push_back(Edge(graph[12], 1));

	graph[7]->connections.push_back(Edge(graph[8], 1));
	graph[7]->connections.push_back(Edge(graph[12], 1));
	graph[7]->connections.push_back(Edge(graph[13], 1));

	graph[8]->connections.push_back(Edge(graph[9], 1));
	graph[8]->connections.push_back(Edge(graph[13], 1));
	graph[8]->connections.push_back(Edge(graph[14], 1));

	graph[9]->connections.push_back(Edge(graph[14], 1));

	/**********************************************************
	***********************************************************/
	graph[10]->connections.push_back(Edge(graph[11], 1));
	graph[10]->connections.push_back(Edge(graph[15], 1));
	graph[10]->connections.push_back(Edge(graph[16], 1));

	graph[11]->connections.push_back(Edge(graph[12], 1));
	graph[11]->connections.push_back(Edge(graph[16], 1));
	graph[11]->connections.push_back(Edge(graph[17], 1));

	graph[12]->connections.push_back(Edge(graph[13], 1));
	graph[12]->connections.push_back(Edge(graph[17], 1));
	graph[12]->connections.push_back(Edge(graph[18], 1));

	graph[13]->connections.push_back(Edge(graph[14], 1));
	graph[13]->connections.push_back(Edge(graph[18], 1));
	graph[13]->connections.push_back(Edge(graph[19], 1));

	graph[14]->connections.push_back(Edge(graph[19], 1));

	/**********************************************************
	***********************************************************/

	graph[15]->connections.push_back(Edge(graph[16], 1));

	graph[16]->connections.push_back(Edge(graph[17], 1));

	graph[17]->connections.push_back(Edge(graph[18], 1));

	graph[18]->connections.push_back(Edge(graph[19], 1));


	return dijkstra::graph;
}

/*****************************************************************************

*****************************************************************************/
void dijkstra::myDraw()
{

}



bool compareNodes(const dijkstra::Node* first, const dijkstra::Node* second)
{
	return first->gScore < second->gScore;
}

std::vector <dijkstra::Node*> dijkstra::findPath(Node* start, Node* end)
{
	myAPPLICATION.clearScreen();

	//declaratin of lists used throughout the pathfinding algorithm
	dijkstra::openList;
	dijkstra::closedList;

	//allows the identification of the start Node
	start->isStart = true;
	start->parent = nullptr;
	//pushes the start node onto our list
	openList.push_back(start);
	

	while (!openList.empty())
	{
		//sorts the distances (gScore) of all the nodes as the are allocated
		openList.sort (compareNodes);

		//sets the current Node pointer based upon the open list 
		Node* currNode = openList.front();

		//breaks the loop once the loop has reached the end node (this can be and mouse input click for something like an rts or moba game)
		if (currNode == end)
		{
			break;
		}
		//removes the current node on the open list and places it onto the closed list, closed list is full of traversed nodes
		openList.erase(openList.begin());
		closedList.push_back(currNode);

		//ranged for loop 
		for (auto c : currNode->connections)
		{
			assert(c.target);
			//std::find used to locate the targert node within the closed list of the current node 
			if (std::find(closedList.begin(), closedList.end(), c.target) == closedList.end())
			{
				//then pushed the target node onto out open list 
				openList.push_back(c.target);
			}
			//sets the target nodes gScore to the current gScore plus the edge cost
			c.target->gScore = currNode->gScore + c.cost;
			//sets the parent of target to the current node
			c.target->parent = currNode;
		}
	}

	//the declation of another list which will only contain the shortest path
	dijkstra::path;

	Node* currNode = end;

	while (currNode->isStart == false)
	{
		//pushing back all the nodes that aren't the start node based on the bool we set at the start 
		path.push_back(currNode);
		//changes the current node to it's own parent pointed
		currNode = currNode->parent;
	}
	//the pushes the last node which will always be the start node 
	path.push_back(currNode);

	//returns the path
	return path;
}

dijkstra & dijkstra::instance()
{
	static dijkstra myPathFind;
	return myPathFind;
}





