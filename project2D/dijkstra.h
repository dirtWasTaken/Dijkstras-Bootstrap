#pragma once
#include <list>
#include <assert.h>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Application2D.h"

#define myPATH		dijkstra::instance()

class dijkstra
{
public:
	dijkstra();

	~dijkstra();

	static dijkstra & instance();

	struct Node;

	struct Edge
	{
		Edge(Node *target_, float cost_) : target(target_), cost(cost_) {}

		Node* target = nullptr;
		float cost;
	};

	struct Node
	{
		Node(int id_, float x_, float y_) : id(id_) { x = x_; y = y_; }

		int id;
		float x = 0;
		float y = 0;
		bool traversed = false;
		bool isStart = false;
		float gScore = 0;
		Node *parent = nullptr;
		bool clicked = false;

		std::vector< Edge > connections;

		bool operator == (Node* other)
		{
			return this->id == other->id;
		}
	};

	std::vector<Node*> findPath(Node* start, Node* end);

	std::vector<Node*>  graphStartup(int graphSize);

	void myDraw();

	std::vector<Node*> graph;
	std::vector<Node*> path;

private:


	std::list<Node*> openList;
	std::list<Node*> closedList;
};
