/** \file tyre.h
* Header file for Tyre class.
* * instantiates the values and functions needed to create the Tyre class
*/

#ifndef TYRES_H
#define TYRES_h

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "AABB.h"

//! The Tyre Class
/*!
This class will instantiate the variables needed to create and maintain the Tyres
*/
class Tyres : public AABB
{

public: 
	
	Tyres(); //!<default constructor
	/**
	The overloaded constructor availible
	\param Position is the X,Y co-ord position of the tyre	
	\param inverseMass is the Inverse Mass of the tyre
	*/
	Tyres(Vector2f Position, float inverseMass);

	Sprite m_TyreSprite;//!< sprite for the tyre

	float radius; //!< radius for the tyre

	/**
	Virtual function collides
	\param *other. used for double dispatch - base class
	*/
	bool collides(Collidable *other);
	/**
	Virtual function collides
	\param *other. used for double dispatch - Tyre Class
	*/
	bool collides(Tyres *other);
	void update(float timepassed);
	void draw(RenderTarget &target, RenderStates states) const; //!< draw function
	void setTyreTexture(vector<Texture>::iterator Texture); //!< function that sets the Tyres texture
	
};


#endif