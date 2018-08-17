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

	std::vector<dijkstra::Node*> path = myPATH.findPath(graph[0], graph[19]);

	myPATH.myDraw(myPATH.graph);

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

	myAPPLICATION.m_2dRenderer->end();

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

			myPATH.graph[i]->gScore = 1e10;

			myAPPLICATION.m_2dRenderer->setRenderColour(1,0,0,1);

			myAPPLICATION.m_2dRenderer->drawCircle(myPATH.graph[i]->x, myPATH.graph[i]->y, 20, 1);

			std::vector<dijkstra::Node*> newPath = myPATH.findPath(myPATH.graph[0], myPATH.graph[19]);

			myPATH.myDraw(newPath);

			std::cout << myPATH.graph[i]->gScore << "\n\n";

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

			if (distance < 40)
			{
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

	// wipe the screen to the background colour
	clearScreen();

	myPATH.myDraw(myPATH.graph);

	/****************************************************************************************
	****************************************************************************************/

	//myPATH.myDraw(myPATH.graph);

	//// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	//// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	//m_2dRenderer->drawSprite(m_shipTexture, 600, 400, 0, 0, m_timer, 1);

	//// draw a thin line
	

	//// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);

	//// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	//// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	//
	//// output some text, uses the last used colour
	//char fps[32];
	//sprintf_s(fps, 32, "FPS: %i", getFPS());
	//m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	//m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);


}


/****************************************************************************************
****************************************************************************************/
Application2D & Application2D::instance2D()
{
	static Application2D Application2D;
	return Application2D;
}