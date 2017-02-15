/** \file HUD.cpp
* cpp file for HUD class.
* * creates the HUD for the game
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include "HUD.h"
#include "car.h"

using namespace std;
using namespace sf;

/*!
Create the HUD object
sets the font(loadsfrom file)
sets the font, string, position and char size to the first lap timer
sets the font, string, position and char size to the second lap timer
sets the font, string, position and char size to the third lap timer
sets the size and color of the background to the timers
instantiates the laptstarts height, width, left and top values
instantiates the halfway height, width, left and top values
*/

HUD::HUD()
{

	if (!font.loadFromFile(".//assets//fonts//liberationsansregular.ttf"))
	{
		cout << "Font could not be found" << endl;
	}
	fLaptime = 420;
	tLaptimeText.setFont(font);
	tLaptimeText.setString(to_string(c_Laptimer.getElapsedTime().asSeconds()));
	tLaptimeText.setPosition(200.0f, 300.0f);
	tLaptimeText.setCharacterSize(17);
	tLaptimeText.setStyle(sf::Text::Bold);

	fFirstTime = 420;
	tFirstLapText.setFont(font);
	tFirstLapText.setPosition(200.0f, 325.0f);
	tFirstLapText.setCharacterSize(17);
	tFirstLapText.setStyle(sf::Text::Bold);

	fBestTime = 420;
	tBestLapText.setFont(font);
	tBestLapText.setPosition(200.0f, 350.0f);
	tBestLapText.setCharacterSize(17);
	tBestLapText.setStyle(sf::Text::Bold);

	r_LapTimerBG.setSize(sf::Vector2f(200, 90));
	r_LapTimerBG.setFillColor(sf::Color::Black);

	fr_LapStart.height = 200.0f;
	fr_LapStart.width = 200.0f;
	fr_LapStart.left = -50.0f;
	fr_LapStart.top = -1000.0f;

	fr_Halfway.height = 200.0f;
	fr_Halfway.width = 200.0f;
	fr_Halfway.left = 0.0f;
	fr_Halfway.top = -400.0f;

	
	
}
// draw function
void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(r_LapTimerBG);
	target.draw(tLaptimeText);
	target.draw(tFirstLapText);
	target.draw(tBestLapText);
	

}
// updates the time, and what to write to the screen
void HUD::Update()
{
	fLaptime = c_Laptimer.getElapsedTime().asSeconds();
	tLaptimeText.setString("Current Lap: " + to_string(c_Laptimer.getElapsedTime().asSeconds()));
}
// sets the first timers position
void HUD::setTime1Position(float x, float y)
{
	tLaptimeText.setPosition(x, y);
}
// sets the second timers position
void HUD::setTime2Position(float x, float y)
{
	tFirstLapText.setPosition(x, y);
}
// sets the third timers position
void HUD::setTime3Position(float x, float y)
{
	tBestLapText.setPosition(x, y);
}
// sets the background of the timers position
void HUD::setRectPosition(float x, float y)
{
	r_LapTimerBG.setPosition(x, y);
}
// gets the position of the first timer
sf::Vector2f HUD::getPosition()
{
	sf::Vector2f temp(tLaptimeText.getPosition().x, tLaptimeText.getPosition().y);
		return temp;
}
// function to check if the car has gone past halfway/starting position
void HUD::LapCheck(car* p1)
{
	// if the car has passed one of the checkpoints
	if (p1->DetectingLapCollisions(&fr_LapStart))
	{
		
		// if the car is about to start
		if (bGameStart == true && !bHalfway)
		{
			c_Laptimer.restart();
			bGameStart = false;

			tLaptimeText.setString( to_string(c_Laptimer.getElapsedTime().asSeconds()));

		}
		// if the car is pass the start, and halfway (ends the lap)
		else if (!bGameStart && bHalfway)
		{
			c_Laptimer.restart();

			fFirstTime = fLaptime;
			tFirstLapText.setString("Previous Lap: " + to_string(fFirstTime));

			if (fFirstTime < fBestTime)
			{
				fBestTime = fFirstTime;
				tBestLapText.setString("Best Time: " + to_string(fBestTime) );
			}

			bHalfway = false;

		}
	}
	// if the car is halfway
	else if (p1->DetectingLapCollisions(&fr_Halfway))
	{
		if (!bHalfway)
		{
			
			bHalfway = true;
		}
	}
}