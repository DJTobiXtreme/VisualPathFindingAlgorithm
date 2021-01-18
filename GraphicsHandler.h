#ifndef GRAPHICSHANDLER_H
#define GRAPHICSHANDLER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include "Dijstras.h"
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class GraphicsHandler {
public:
	GraphicsHandler();
	void loop();
private:
	void Draw();
	void OnMouseReleased(int x, int y);
	void OnMousePressed(int x, int y);
	
	
	Dijstras d;
	RenderWindow m_w;
	Clock m_clock;
	RectangleShape guiUnchecked;
	RectangleShape guiChecked;
	RectangleShape guiBacktrace;
	RectangleShape guiStart;
	RectangleShape guiFinal;
	RectangleShape guiWall;
	int sr, sc, fr, fc;
	bool is_s_pressed;
	bool is_f_pressed;
	bool is_w_pressed;
	
};

#endif

