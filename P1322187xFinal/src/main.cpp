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

bool bStart = false; 
/**
The entry point for the application.
*/
int main()
{

	Game gMaster; //!< create Game class, which controls all of our game objects and functions.

	RenderWindow window(VideoMode(1024,768), "RadRacer", Style::Close | Style::Titlebar); //!< render window
	float fTimePassed;


	Clock timer;

	View MainGame;
	View MiniMap;
	View HUD;

	MiniMap.zoom(3); 

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


			if (event.type == Event::KeyPressed)
			{
				gMaster.KeyPress(event.key.code);
			}
			if (event.type == Event::KeyReleased)
			{
				gMaster.KeyRelease(event.key.code);
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)

				{
					Vector2f x;
					x = window.mapPixelToCoords(Mouse::getPosition(window), MainGame);
					std::cout << x.x << ", " << x.y << std::endl;
				}
			}

		}
		fTimePassed = timer.getElapsedTime().asSeconds();

		if (fTimePassed > 0.0125)
		{
			
			gMaster.update(fTimePassed);
			gMaster.ViewLimits(&MainGame, gMaster.getCarPos());

			MiniMap.setViewport(FloatRect(0.75f, 0.0f, 0.25f, 0.3f));
			MiniMap.setCenter(100, 100); // tweek

			timer.restart();
		}
		if (bStart == false)
			MainGame.setCenter(0, 0);

		window.setView(MainGame);
		window.clear(Color::Cyan);
		window.draw(gMaster);

		if (bStart == true)
		{
			window.setView(MiniMap);
			window.draw(gMaster);

			window.setView(HUD);
			window.draw(gMaster.m_HUD);
		}
		window.display();
	}



}

