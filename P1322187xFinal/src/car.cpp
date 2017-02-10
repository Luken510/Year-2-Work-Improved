/** \file car.cpp
* cpp file for the car class.
* * The Player class
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/window.hpp>
#include "car.h"
#include "AABB.h"
#include "tyre.h"
#include <iostream>

using namespace std;
using namespace sf;
/*!
Create the car object
sets the texture(loads image from file)
sets the sprite to the texture
sets the origin of the sprite
sets the position of the car
sets the velocity of the car
sets the mass of the car
calls the minMax function
*/
car::car()
{
	//m_Sprite.setOrigin(m_Sprite.getLocalBounds().width / 2.0f, m_Sprite.getLocalBounds().height / 2.0f); move to set texture
}

car::car(Vector2f vPos, Vector2f vAcce, float InvMass, Vector2f Velo)
{
	m_vPos = vPos;
	m_vAcceleration = vAcce;
	m_fInverseMass = InvMass;
	m_vVel = Velo;
	m_fRotationAngle = 0;

	m_Sprite.setPosition(m_vPos);
	m_Sprite.scale(1, 1);



	for (int i = 0; i < 2; i ++ )
	{
		m_FrontWheel[i].setSize(Vector2f(10, 4));
		m_RearWheel[i].setSize(Vector2f(10, 4));
		m_FrontWheel[i].setOrigin(m_FrontWheel[i].getSize() / 2.f);
		m_RearWheel[i].setOrigin(m_RearWheel[i].getSize() / 2.f);
		m_FrontWheel[i].setFillColor(Color::Black);
		m_RearWheel[i].setFillColor(Color::Black);
	}

}
// draw function
void car::draw(RenderTarget &target, RenderStates states) const
{
	
	for (int i = 0; i < 2; i++) // Draws wheels to screen
	{
		target.draw(m_FrontWheel[i]);
		target.draw(m_RearWheel[i]);
	}
	
	target.draw(m_Sprite);
	
}
// function for getting the value of Rotation vector
Vector2f car::getRotatVector()
{
	Vector2f RotatVector;
	RotatVector.x = cosf(m_fRotationAngle * (3.14159f / 180.0f));
	RotatVector.y = sinf(m_fRotationAngle * (3.14159f / 180.0f));
	
	return RotatVector;
}
// Update function for the car, it updates all values, position, and speed
void car::Update(float fTimePassed)
{

	Vector2f Friction = getFriction();
	// sets the accerlation
	m_vAcceleration = fSpeed * getRotatVector() * fTimePassed * fDirection - friction;
	// sets the velocity
	m_Velocity += m_Accerlation * fTimePassed;
	//check if collision was succesful
	if (bCollisionsucessful == 1)
	{
		if (bBottomSideColli == 1)
		{
			m_Position.y += 30.0f;
			bCollisionsucessful = 0;
			bBottomSideColli = 0;
			bTopSideColli = 0;
			bLeftSideColli = 0;
			bRightSideColli = 0;
		}

		else if (bLeftSideColli == 1)
		{
			m_Position.x += 30.0f;
			bCollisionsucessful = 0;
			bBottomSideColli = 0;
			bTopSideColli = 0;
			bLeftSideColli = 0;
			bRightSideColli = 0;
		}

	}
	else
	{
		// move the car
		m_Position += m_Velocity;
	}
	

	// Left rotation
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && magnitude(m_Velocity) > 0.1f)
	{
		Rotate(-2.9f, fTimePassed);
	}
	// right rotation
	if (Keyboard::isKeyPressed(Keyboard::Key::Right) && magnitude(m_Velocity) > 0.1f)
	{
		Rotate(2.9f, fTimePassed);
	}


	

	// update the sprites position
	m_Sprite.setPosition(m_Position);
	// update the sprites rotation
	m_Sprite.setRotation(m_fRotationAngle);
	//reset all bools
	bCollisionsucessful = 0;
	bBottomSideColli = 0;
	bTopSideColli = 0;
	bLeftSideColli = 0;
	bRightSideColli = 0;
	//set the min/max of the current x and y values
	setMinMax();

}
// rotates the car
void car::Rotate(float dir, float fTimePassed)
{

	m_fRotationAngle += 50.0f * dir * fTimePassed;

	m_Sprite.setRotation(m_fRotationAngle);
}
// retuns car position
Vector2f car::getPosition()
{
	return  m_Position;
}
// function that sets the minimum and maximum of current X and Y Values
void car::setMinMax()
{
	// x co-ord + width/2 to get the min X
	fMinX = m_Sprite.getLocalBounds().left + (m_Sprite.getLocalBounds().width / 2.0f);
	// x co_ord + width to get the max X
	fMaxX = m_Sprite.getLocalBounds().left + m_Sprite.getLocalBounds().width;
	// y co-ord + height/2 to get min
	fMinY = m_Sprite.getLocalBounds().top + (m_Sprite.getLocalBounds().height / 2.0f);
	// y co-ord + height to get max
	fMaxY = m_Sprite.getLocalBounds().top + m_Sprite.getLocalBounds().height;

	sf::Vector2f MTemp;
	MTemp.x = fMaxX;

	MTemp.y = fMaxY;
	// set the max x and y
	setMax(MTemp);

	sf::Vector2f mTemp2;

	mTemp2.x = fMinX;

	mTemp2.y = fMinY;
	// set the min x and y
	setMin(mTemp2);

}
// returns the current magnitude
float car::magnitude(Vector2f v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}
/**
instantiates the virtual function collides
\param *other. used for double dispatch - base class
allows us to exploit ploymorphism, this is the base class function that will call the other collides function
*/
bool car::collides(Collidable *other)
{
	// calls the other function, allows for multiple possible calls
	return this->collides(other);
}
/**
instantiates the virtual function collides
\param *other. used for double dispatch - Tyre class
this function will check all the possible points of interception
it will set the bools of collision to either true or false
it will check to se how far it has intercepted
*/
bool car::collides(Tyres *other)
{
	
	// the intercept
	v_InterceptDiff = other->Rectangle.getPosition() - this->m_Sprite.getPosition();
	// extent of the objects X co-ords
		float f_bXExtent = (other->getMax().x - other->getMin().x) / 2.0f;
		float f_aXExtent = (this->getMax().x - this->getMin().x) / 2.0f;

		// checking all possible x collisions
		if ((this->getPosition().x + f_aXExtent) < (other->Rectangle.getOrigin().x - f_bXExtent) || (this->getPosition().x - f_aXExtent) > (other->Rectangle.getOrigin().x + f_bXExtent))
		{

			// extent of the objects Y co-ords
			float f_aYExtent = (this->getMax().y - this->getMin().y) / 2.0f;
			float f_bYExtent = (other->getMax().y - other->getMin().y) / 2.0f;

			// check all possible y collisions
			if ((this->getPosition().y + f_aYExtent) < (other->Rectangle.getOrigin().y - f_bYExtent) || (this->getPosition().y - f_aYExtent) > (other->Rectangle.getOrigin().y + f_bYExtent))
			{

				// testing how they collided, bottom of the car
				if (v_InterceptDiff.x >= 0)
				{
					bBottomSideColli = 1;
					
					Vector2f v_TestWhatTyre(other->Rectangle.getPosition());
					cout << v_TestWhatTyre.x << " " << v_TestWhatTyre.y << endl;
					cout << "Collision 1" << endl;
					return true;
				}
				// top of the car
				else if ( v_InterceptDiff.x < 0)
				{

					bTopSideColli = 1;
					;
					cout << "collision 2" << endl;
					Vector2f v_TestWhatTyre(other->Rectangle.getPosition());
					cout << v_TestWhatTyre.x << " " << v_TestWhatTyre.y << endl;
					return true;
				}

				// left of the car
				if (v_InterceptDiff.y >= 0) 
				{

					bLeftSideColli = 1;
					
					Vector2f v_TestWhatTyre(other->Rectangle.getPosition());
					cout << v_TestWhatTyre.x << " " << v_TestWhatTyre.y << endl;
					cout << "Collision 3" << endl;
					return true;
				}
				else if (v_InterceptDiff.y < 0)
				// right of the car
				{
					bRightSideColli = 1;
				
					cout << "collision 4" << endl;
					Vector2f v_TestWhatTyre(other->Rectangle.getPosition());
					cout << v_TestWhatTyre.x << " " << v_TestWhatTyre.y << endl;
					return true;
				}





			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	
}
// function that does a wide scope intercept check
bool car::DetectingCollisions(Tyres *other)

{


	if (this->m_Sprite.getGlobalBounds().intersects(other->frm_Tyrewall))
	{
		this->bCollisionsucessful = 1;
		return true;
	}
	return false;

}
// function used to check where the car is on the lap
bool car::DetectingLapCollisions(sf::FloatRect *other)
{

	if (this->m_Sprite.getGlobalBounds().intersects(*other))
	{
		return true;
	}
	return false;

} 
// set the value of the car's velocity
void car::setVelocity(Vector2f m_newVel)
{
	m_Velocity = m_newVel;
}
// set the direction of the car
void car::setDirection(float fnewDire)
{
	fDirection = fnewDire;
}
// get the current direction of the car
float car::getDirection()
{
	return fDirection;
}
// get the current value of velocity
Vector2f car::getVelocity()
{
	return m_Velocity;
}
// set the position of the car
void car::setPosition(Vector2f newPos)
{
	m_Sprite.setPosition(newPos);
}
