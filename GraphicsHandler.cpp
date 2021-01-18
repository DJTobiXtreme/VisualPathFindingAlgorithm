#include "GraphicsHandler.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>
using namespace std;
using namespace sf;
const int recSize=30;

GraphicsHandler::GraphicsHandler(): m_w(VideoMode(recSize*d.width,recSize*(d.high+2)),"Shortest path"),
	guiUnchecked(Vector2f(recSize,recSize)), guiChecked(Vector2f(recSize,recSize)), guiBacktrace(Vector2f(recSize,recSize)),
	guiStart(Vector2f(recSize,recSize)), guiFinal(Vector2f(recSize,recSize)), guiWall(Vector2f(recSize,recSize)),
	sr(7), sc(5), fr(7), fc(44), is_s_pressed(false), is_f_pressed(false), is_w_pressed(false)
	{
	guiUnchecked.setFillColor(Color::Green);
	guiUnchecked.setOutlineColor(Color::Black);
	guiUnchecked.setOutlineThickness(1);
	
	guiChecked.setFillColor(Color::Blue);
	guiChecked.setOutlineColor(Color::Black);
	guiChecked.setOutlineThickness(1);
	
	guiBacktrace.setFillColor(Color::Yellow);
	guiBacktrace.setOutlineColor(Color::Black);
	guiBacktrace.setOutlineThickness(1);
	
	guiStart.setFillColor(Color::Cyan);
	guiStart.setOutlineColor(Color::Black);
	guiStart.setOutlineThickness(1);
	
	guiFinal.setFillColor(Color::Black);
	guiFinal.setOutlineColor(Color::Black);
	guiFinal.setOutlineThickness(1);
	
	guiWall.setFillColor(Color::Magenta);
	guiWall.setOutlineColor(Color::Black);
	guiWall.setOutlineThickness(1);
	
	m_w.setFramerateLimit(60);
	
}

void GraphicsHandler::loop ( ) {
	
	d.Start(sr,sc,fr,fc);

	while(m_w.isOpen()) {
		Event e;
		while(m_w.pollEvent(e)) {
			if(e.type == Event::Closed)
				m_w.close();
			
			if(e.type == Event::MouseButtonPressed)
				OnMousePressed(e.mouseButton.x/recSize, e.mouseButton.y/recSize);
			
			if(e.type == Event::MouseButtonReleased)
				OnMouseReleased(e.mouseButton.x/recSize, e.mouseButton.y/recSize);
		}
		if(e.MouseMoved && is_w_pressed && e.mouseMove.x/recSize!=0) {
			cout<<e.mouseMove.x/recSize<<" "<<e.mouseMove.y/recSize<<endl;
			d.SetWall(e.mouseMove.x/recSize, e.mouseMove.y/recSize);
		}
		
		m_w.clear(Color::Red);
		d.Loop();
		Draw();
		m_w.display();
	}
}

void GraphicsHandler::Draw ( ) {

	for(int i=0;i<d.high;i++) { 
		for(int j=0;j<d.width;j++) { 
			switch (d.getChecked(i,j)){
			case 0:
				guiUnchecked.setPosition(j*recSize,i*recSize);
				m_w.draw(guiUnchecked);
				break;
			case 1:
				guiChecked.setPosition(j*recSize,i*recSize);
				m_w.draw(guiChecked);
				break;
			case 8:
				guiWall.setPosition(j*recSize,i*recSize);
				m_w.draw(guiWall);
				break;
			case 9:
				guiBacktrace.setPosition(j*recSize,i*recSize);
				m_w.draw(guiBacktrace);
				break;
			}	
		}
	}
	guiStart.setPosition(sc*recSize,sr*recSize);
	m_w.draw(guiStart);
	guiFinal.setPosition(fc*recSize,fr*recSize);
	m_w.draw(guiFinal);
}


void GraphicsHandler::OnMousePressed (int x, int y) {
	if (x==sc && y==sr) is_s_pressed = true;
	else if (x==fc && y==fr) is_f_pressed = true;
	else if (y>d.high-1) {
		d.Start(sr,sc,fr,fc);
		d.is_started = true;
	} else is_w_pressed = true;
	cout<<x<<" "<<y<<endl;
}

void GraphicsHandler::OnMouseReleased (int x, int y) {
	if (is_s_pressed) {
		is_s_pressed = false;
		if (y<d.high && x<d.width) {sr = y; sc = x;}
	}
	if (is_f_pressed) {
		is_f_pressed = false;
		if (y<d.high && x<d.width) {fr = y; fc = x;}
	}
	is_w_pressed = false;
}


