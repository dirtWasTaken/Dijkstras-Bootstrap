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
	graph[0]->connections.push_back(Edge(graph[1], 1));
	graph[0]->connections.push_back(Edge(graph[5], 5));
	graph[0]->connections.push_back(Edge(graph[6], 3));

	graph[1]->connections.push_back(Edge(graph[2], 9));
	graph[1]->connections.push_back(Edge(graph[6], 7));
	graph[1]->connections.push_back(Edge(graph[7], 2));

	graph[2]->connections.push_back(Edge(graph[3], 13));
	graph[2]->connections.push_back(Edge(graph[7], 12));
	graph[2]->connections.push_back(Edge(graph[8], 19));

	graph[3]->connections.push_back(Edge(graph[4], 22));
	graph[3]->connections.push_back(Edge(graph[8], 32));
	graph[3]->connections.push_back(Edge(graph[9], 1));

	graph[4]->connections.push_back(Edge(graph[9], 19));
	
	/**********************************************************
	***********************************************************/

	graph[5]->connections.push_back(Edge(graph[6], 3));
	graph[5]->connections.push_back(Edge(graph[10], 23));
	graph[5]->connections.push_back(Edge(graph[11], 32));

	graph[6]->connections.push_back(Edge(graph[7], 50));
	graph[6]->connections.push_back(Edge(graph[11], 65));
	graph[6]->connections.push_back(Edge(graph[12], 45));

	graph[7]->connections.push_back(Edge(graph[8], 34));
	graph[7]->connections.push_back(Edge(graph[12], 65));
	graph[7]->connections.push_back(Edge(graph[13], 37));

	graph[8]->connections.push_back(Edge(graph[9], 40));
	graph[8]->connections.push_back(Edge(graph[13], 33));
	graph[8]->connections.push_back(Edge(graph[14], 23));

	graph[9]->connections.push_back(Edge(graph[14], 29));

	/**********************************************************
	***********************************************************/
	graph[10]->connections.push_back(Edge(graph[11], 17));
	graph[10]->connections.push_back(Edge(graph[15], 13));
	graph[10]->connections.push_back(Edge(graph[16], 19));

	graph[11]->connections.push_back(Edge(graph[12], 43));
	graph[11]->connections.push_back(Edge(graph[16], 32));
	graph[11]->connections.push_back(Edge(graph[17], 54));

	graph[12]->connections.push_back(Edge(graph[13], 23));
	graph[12]->connections.push_back(Edge(graph[17], 11));
	graph[12]->connections.push_back(Edge(graph[18], 65));

	graph[13]->connections.push_back(Edge(graph[14], 23));
	graph[13]->connections.push_back(Edge(graph[18], 43));
	graph[13]->connections.push_back(Edge(graph[19], 56));

	graph[14]->connections.push_back(Edge(graph[19], 43));

	/**********************************************************
	***********************************************************/

	graph[15]->connections.push_back(Edge(graph[16], 34));

	graph[16]->connections.push_back(Edge(graph[17], 23));
	
	graph[17]->connections.push_back(Edge(graph[18], 65));

	graph[18]->connections.push_back(Edge(graph[19], 34));

	return dijkstra::graph;


}

void dijkstra::myDraw(std::vector<Node*> graph)
{
	myAPPLICATION.m_2dRenderer = new aie::Renderer2D();

	//begin drawing
	myAPPLICATION.m_2dRenderer->begin();

	// set the camera position before we begin rendering
	myAPPLICATION.m_2dRenderer->setCameraPos(0, 0);

	for (int i = 0; i < graph.size(); i++)
	{
		myAPPLICATION.m_2dRenderer->setRenderColour(1, 0, 1, 1);
		myAPPLICATION.m_2dRenderer->drawCircle(graph[i]->x, graph[i]->y, 20, 0);

		for (int c = 0; c < graph[i]->connections.size(); c++)
		{
			myAPPLICATION.m_2dRenderer->drawLine(graph[i]->x, graph[i]->y, graph[i]->connections[c].target->x, graph[i]->connections[c].target->y);
		}
	}

	for (int p = 0; p < path.size(); p++)
	{
		myAPPLICATION.m_2dRenderer->setRenderColour(0, 1, 0, 1);
		myAPPLICATION.m_2dRenderer->drawCircle(path[p]->x, path[p]->y, 20, 0);

		if (p + 1 < path.size())
		{
			myAPPLICATION.m_2dRenderer->drawLine(path[p]->x, path[p]->y, path[p + 1]->x, path[p + 1]->y);
		}

	}
		myAPPLICATION.m_2dRenderer->end();
}

bool compareNodes(const dijkstra::Node* first, const dijkstra::Node* second)
{
	return first->gScore < second->gScore;
}

std::vector <dijkstra::Node*> dijkstra::findPath(Node* start, Node* end)
{
	

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





