/** \file HUD.h
* Header file for HUD class.
* * creates the HUD for the game
*/


#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
// pre declare class car
class car;
//! The HUD Class
/*!
This class will instantiate the variables needed to create and maintain the HUD
*/
using namespace sf;
class HUD : public Drawable
{
private:
	Text tLaptimeText; //!< instantiate the text object laptime
	float fLaptime;
	Font font;//!< instantiate the font for manipulation
	Clock c_Laptimer; //!< instantiate the clock for the game
	Text tFirstLapText; //!< instantiate the Text object for other laps
	float fFirstTime;
	Text tBestLapText; //!< instantiate the Text object for other laps
	float fBestTime;
	RectangleShape r_LapTimerBG; //!< instantiate the background of the timers
	
	bool bGameStart = true; //!< instantiate the bool value to check to see if the car just started
	bool bHalfway = false; //!< instantiate the bool value to check to see if the car has gone halfway
public:
	FloatRect fr_LapStart; //!< instantiate the point of starting the lap
	FloatRect fr_Halfway; //!< instantiate the halfway point of the lap

	HUD(); //!< defualt constructor 
	void draw(RenderTarget &target, RenderStates states) const; //!< draw function
	void Update(); //!< updates all variables to maintain the HUD
	void setTime1Position(float x, float y); //!< set the position of the first timer
	void setTime2Position(float x, float y); //!< set the position of the second timer
	void setTime3Position(float x, float y); //!< set the position of the third timer
	void setRectPosition(float x, float y); //!< set the position of the Background
	Vector2f getPosition(); //!< gets the position of the first laptimer
	void LapCheck(car* p1); //!< function to check if the car has gone past halfway/starting position
};

#endif