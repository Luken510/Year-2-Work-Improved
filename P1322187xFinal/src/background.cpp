/** \file Background.cpp
* cpp file for the background class.
* * Sets up the background of the game
*/


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "background.h"

using namespace std;
using namespace sf;

/*!
set the background image depending on which part of the game it is currently at
sets the texture(loads image from file)
sets the origin of the texture
sets the position of the texture
*/
background::background(vector<Texture>::iterator GameBGTexture, Vector2f Pos)
{
	setTexture(*GameBGTexture);
	setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
	setPosition(Pos);
}