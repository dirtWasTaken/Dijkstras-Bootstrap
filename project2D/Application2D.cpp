#pragma once
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "dijkstra.h"
#include "Application2D.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}
/****************************************************************************************
****************************************************************************************/
bool Application2D::startup() {


	std::vector<dijkstra::Node*> graph = myPATH.graphStartup(20);

	std::vector<dijkstra::Node*> path = myPATH.findPath(myPATH.graph[0], myPATH.graph[19]);

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

/****************************************************************************************
****************************************************************************************/
void Application2D::shutdown() {
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}
/****************************************************************************************
****************************************************************************************/
void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	/****************************************************************************************
	****************************************************************************************/
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
	{
		float xMouse = (float)input->getMouseX();
		float yMouse = (float)input->getMouseY();

		for (size_t i = 0; i < myPATH.graph.size(); i++)
		{
			float distance = sqrtf((xMouse - myPATH.graph[i]->x) * (xMouse - myPATH.graph[i]->x) + (yMouse - myPATH.graph[i]->y) * (yMouse - myPATH.graph[i]->y));

			if (distance < 30)
			{
			myPATH.graph[i]->clicked = true;
			myPATH.graph[i]->gScore = 1e10;

			std::cout << myPATH.graph[i]->id << "  " << myPATH.graph[i]->gScore << "\n\n";
			clearScreen();
			std::vector<dijkstra::Node*> newPath = myPATH.findPath(myPATH.graph[0], myPATH.graph[19]);
			break;
			}
		}
	}
	/****************************************************************************************
	****************************************************************************************/
	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		float xMouse = (float)input->getMouseX();
		float yMouse = (float)input->getMouseY();

		for (size_t i = 0; i < myPATH.graph.size(); i++)
		{
			float distance = sqrtf((xMouse - myPATH.graph[i]->x) * (xMouse - myPATH.graph[i]->x) + (yMouse - myPATH.graph[i]->y) * (yMouse - myPATH.graph[i]->y));

			if (distance < 30)
			{
				myPATH.graph[i]->clicked = false;
				myPATH.graph[i]->gScore = 0;

				std::cout << myPATH.graph[i]->gScore << "\n";
				break;
			}
		}
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void Application2D::draw() {

m_2dRenderer = new aie::Renderer2D();

//begin drawing
m_2dRenderer->begin();

/*****************************************************************************
Draws the graph nodes and the edges purple
*****************************************************************************/
for (int i = 0; i < myPATH.graph.size(); i++)
{
	m_2dRenderer->setRenderColour(1, 0, 1, 1);
	m_2dRenderer->drawCircle(myPATH.graph[i]->x, myPATH.graph[i]->y, 20, 0);

	for (int c = 0; c < myPATH.graph[i]->connections.size(); c++)
	{
		m_2dRenderer->drawLine(myPATH.graph[i]->x, myPATH.graph[i]->y, myPATH.graph[i]->connections[c].target->x, myPATH.graph[i]->connections[c].target->y);
	}
}
	for (int i = 0; i < myPATH.graph.size(); i++) {

		if (myPATH.graph[i]->clicked == true)
		{
			m_2dRenderer->setRenderColour(1, 0, 0, 1);
			m_2dRenderer->drawCircle(myPATH.graph[i]->x, myPATH.graph[i]->y, 20, 0);
		}
	}

	/*****************************************************************************
	Draws the shortest path Nodes and their edges green
	*****************************************************************************/
	for (int p = 0; p < myPATH.path.size(); p++) {
		m_2dRenderer->setRenderColour(0, 1, 0, 1);
		m_2dRenderer->drawCircle(myPATH.path[p]->x, myPATH.path[p]->y, 20, 0);

		if (p + 1 < myPATH.path.size()) {

			m_2dRenderer->drawLine(myPATH.path[p]->x, myPATH.path[p]->y, myPATH.path[p + 1]->x, myPATH.path[p + 1]->y);
		}
	
	}
	m_2dRenderer->end();
}


/****************************************************************************************
****************************************************************************************/
Application2D & Application2D::instance2D()
{
	static Application2D Application2D;
	return Application2D;
}