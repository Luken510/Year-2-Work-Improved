/** \file car.h
* Header file for the car class.
* * The Player class
*/

#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include "collidable.h"
#include "AABB.h"
#include "HUD.h"

//! The car Class
/*!
This class will instantiate the variables needed to create and maintain 
the car class ( the player ) in the game
*/

using namespace sf;

class car : public AABB
{
private:
	
	float m_fRotationAngle; //!< instantiate the rotationAngle of which the car rotates
	float fDirection = 0; //!< instantiate the direction of the car
	float fSpeed = 600.0f; //!< instantiate the speed of the car
	RectangleShape m_FrontWheel[2]; //!< Front wheels
	RectangleShape m_RearWheel[2]; //!< Rear wheels
	float m_fWheelAngle; //!< Angle of which my wheels will be facing
	Vector2f m_RotationVector; //!< The Direction of the car/sprite

public:
	Sprite m_Sprite; //!< instantiate the sprite that will use the texture

	car(); //!< default constructor 


	car(Vector2f vPos, Vector2f vAcce, float InvMass, Vector2f Velo);


	/**
	The virtual draw function
	\param Target, is the object that will be drawn
	\Param states is how the object will be drawn
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Vector2f getRotatVector(); //!< function for getting the value of Rotation vector

	/**
	Update function for the car, it updates all values, position, and speed
	\only parameter is the Timepassed currently ingame
	*/
	void Update(float fTimePassed); 

	/**
	The Rotate function for the car
	\param direction is the direction in which it rotates
	\param Timepassed is the current timepassed ingame
	*/
	void Rotate(float direction, float fTimePassed);


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

	bool DetectingCollisions(Tyres *other); //!< function that does a wide scope intercept check


	void setPosition(sf::Vector2f newPos); //!< set the position of the car
	sf::Vector2f getPosition(); //!< returns the current position

	bool DetectingLapCollisions(sf::FloatRect *other); //!< function used to check where the car is on the lap


	void SetTexture(vector<Texture>::iterator Texture);
};


#endif 