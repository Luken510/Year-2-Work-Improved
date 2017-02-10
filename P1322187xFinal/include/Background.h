/** \file Background.h
* Header file for the background class.
* * Sets up the background of the game
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include "textureLoader.h"
using namespace sf;

//! The background Class
/*!
	This class will be used to set the texture of the background in the game and apply it to the screen
*/

class background : public Sprite
{
private:
	Texture m_Texture; //!< instantiate m_Texture
public:
	/**
	The only constructor availible, takes one variables.
	\param btrack is the true or false statement instantiated above

	*/
	
	background(vector<Texture>::iterator GameBGTexture, Vector2f Pos); // include textureloader.h
};

#endif