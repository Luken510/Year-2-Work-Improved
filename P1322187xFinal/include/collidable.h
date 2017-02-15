/** \file collidable.h
* Header file for the virtual function class, Collisions.
* * Creates the virtual functions used to test collisions
*/

#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//pre declare class Tyres
class Tyres; 

//! The Colliable Class
/*!
This class is a virtual class, where is has no constructor and only contanis virtual functions
This class will be used for double dispatch when finding collisions in game
*/
class Collidable : public sf::Drawable
{

public:

	virtual void collides(Collidable * other) = 0; //!< virtual function used for double dispatch - base class
	virtual void collides(Tyres * other) = 0; //!< virtual function to test a collision against the tyrewall
	
};


#endif