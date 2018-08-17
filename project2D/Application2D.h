#pragma once

#include "Application.h"
#include "Renderer2D.h"

#define myAPPLICATION       Application2D::instance2D()



class Application2D : public aie::Application {
public:

	static Application2D & instance2D();

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	aie::Renderer2D  *m_2dRenderer = nullptr;

protected:
	aie::Texture	*m_texture = nullptr;
	aie::Texture	*m_shipTexture = nullptr;
	aie::Font		*m_font = nullptr;

	float m_cameraX, m_cameraY;
	float m_timer;
};