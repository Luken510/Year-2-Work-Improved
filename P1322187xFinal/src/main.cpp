/*! \mainpage RadRacer
*
* This is the documentation for the simple racing game RadRacer
*
* This program is a simple racing game
*
*/

/** \file main.cpp
* Contains the entry point for the program.
* Contains the entry point for the program which creates the main game loop
* updating the other objects constantly through the main loop
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <SFML/Window.hpp>
#include "game.h"
#include <memory>


using namespace std;
using namespace sf;


/**
The entry point for the application.
*/
int main()
{

	Game gMaster; //!< create Game class, which controls all of our game objects and functions.

	RenderWindow window(VideoMode(1024,768), "RadRacer", Style::Close | Style::Titlebar); //!< render window
	window.setFramerateLimit(60);
	float fFrameTime(1.0f / 60.0f); // fps
	float fTimePassed;


	Clock timer;

	View MainGame;
	View MiniMap;
	View HUD;

	MiniMap.zoom(5); 

	MainGame.setSize(Vector2f(window.getSize()));
	HUD.setSize(Vector2f(window.getSize()));
	gMaster.ReadTyreFile();

	// game loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (timer.getElapsedTime().asSeconds() > fFrameTime)
		{
			
			fTimePassed = timer.getElapsedTime().asSeconds();
			gMaster.update(fTimePassed);
			MainGame.setCenter(gMaster.getCarPos());

			MiniMap.setViewport(FloatRect(0.5f, 0.0f, 0.2f, 0.2f));
			MiniMap.setCenter(100, 100); // tweek

			timer.restart();
		}
		
		window.setView(MainGame);
		window.clear(Color::Green);
		window.draw(gMaster);

		window.setView(MiniMap);
		window.draw(gMaster);

		window.setView(HUD);
		window.draw(gMaster.m_HUD);

		window.display();
	}



}

