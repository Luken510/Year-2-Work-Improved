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
	RectangleShape m_FrontWheel[2]; //!< Front wheels
	RectangleShape m_RearWheel[2]; //!< Rear wheels
	float m_fWheelAngle; //!< Angle of which my wheels will be facing
	sf::Vector2f m_RotationVector; //!< The Direction of the car/sprite
	int m_aiAccelerationPower[5]; //!< Power of current Acceleration
	float m_afGears[6]; //!< Multiplys the gear by the current power, max gear = 1* accleration
	
	float m_CarTurningAngle; //!< current angle cars turns


public:
	bool m_TurningRight = 0; //!< sets the direction of turning to right
	bool m_TurningLeft = 0; //!< sets the direction of turning to left
	int m_iPower; //!< Power of the acclerator
	int m_iGear; //!< The gears of the car
	float fDirection = 0; //!< instantiate the direction of the car
	Sprite m_Sprite; //!< instantiate the sprite that will use the texture

	car(); //!< default constructor 


	car(sf::Vector2f vPos, sf::Vector2f vAcce, float InvMass, sf::Vector2f Velo);


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
	void collides(Collidable *other);


	/**
	Virtual function collides
	\param *other. used for double dispatch - Tyre Class
	*/
	void collides(Tyres *other);

	bool DetectingCollisions(Tyres *other); //!< function that does a wide scope intercept check


	void setPosition(sf::Vector2f newPos); //!< set the position of the car
	sf::Vector2f getPosition(); //!< returns the current position

	bool DetectingLapCollisions(sf::FloatRect *other); //!< function used to check where the car is on the lap


	void SetTexture(std::vector<Texture>::iterator Texture);

	void Turning();

	void ChangeGear(float timestep);
};


#endif 