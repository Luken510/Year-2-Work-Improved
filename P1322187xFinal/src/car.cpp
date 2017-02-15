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
extern bool bStart;
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
	m_iGear = 0;
	m_iPower = 1200;

	m_Sprite.setOrigin(30, 20);
	m_Sprite.setPosition(m_vPos);
	m_Sprite.scale(1, 1);

	//Sets rates of acceleration for each gear - more power the earlier the gear, to similate the quick change between lower gears in a car
	m_aiAccelerationPower[0] = 1600;
	m_aiAccelerationPower[1] = 1300;
	m_aiAccelerationPower[2] = 1000;
	m_aiAccelerationPower[3] = 700;
	m_aiAccelerationPower[4] = 500;

	m_afGears[0] = 0.4;
	m_afGears[1] = 0.5f;
	m_afGears[2] = 0.6f;
	m_afGears[3] = 0.7f;
	m_afGears[4] = 0.8f;
	m_afGears[5] = 1.f;


	for (int i = 0; i < 2; i ++ )
	{
		m_FrontWheel[i].setSize(Vector2f(10, 5));
		m_RearWheel[i].setSize(Vector2f(10, 5));
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
	
	

		

		///limits turning angle
		if (m_CarTurningAngle > 35)
		{
			m_CarTurningAngle = 35;
		}
		if (m_CarTurningAngle < -35)
		{
			m_CarTurningAngle = -35;
		}

		//sets the friction
		Vector2f Friction = getFriction();
		//sets the rotation vector
		m_RotationVector = getRotatVector();




		Vector2f TempTurnVector;
		TempTurnVector.x = cosf((m_fRotationAngle + m_CarTurningAngle) * (3.14159f / 180.0f));
		TempTurnVector.y = sinf((m_fRotationAngle + m_CarTurningAngle) * (3.14159f / 180.0f));

		// update the sprites rotation
		m_Sprite.setRotation(m_fRotationAngle);

		//magnitude of Velocity * the amount of time passed is the displacement
		float fDisplacement = magnitudeOfVector(m_vVel) * fTimePassed;
		float fWheelBounds = m_Sprite.getLocalBounds().width * 0.70f;


		if (fDotProduct(m_vVel, TempTurnVector) < 0)
		{
			fDisplacement = -fDisplacement;
		}

		//creating the cars tyres to set position for the wheels
		Vector2f FrontTyres;
		Vector2f BackTyres;

		Vector2f CarAngle(-m_RotationVector.y, m_RotationVector.x);

		//sets the wheels to the car
		FrontTyres = Vector2f(addVectors(m_vPos, multiplyVectors(m_RotationVector, fWheelBounds / 2)));
		BackTyres = Vector2f(subtractVectors(m_vPos, multiplyVectors(m_RotationVector, fWheelBounds / 2)));
		FrontTyres = addVectors(FrontTyres, multiplyVectors(TempTurnVector, fDisplacement));
		BackTyres = addVectors(BackTyres, multiplyVectors(m_RotationVector, fDisplacement));

		//std::cout << "Tyres: " << FrontTyres.x << "," << FrontTyres.y << std::endl;

		for (int i = 0; i < 2; i++)
		{
			m_FrontWheel[i].setRotation(m_CarTurningAngle + m_fRotationAngle);
			m_RearWheel[i].setRotation(m_fRotationAngle);
		}

		//sets position of wheels
		m_FrontWheel[0].setPosition(addVectors(FrontTyres, multiplyVectors(CarAngle, 18.0f)));
		m_FrontWheel[1].setPosition(addVectors(FrontTyres, multiplyVectors(CarAngle, -18.0f)));
		m_RearWheel[0].setPosition(addVectors(BackTyres, multiplyVectors(CarAngle, -18.0f)));
		m_RearWheel[1].setPosition(addVectors(BackTyres, multiplyVectors(CarAngle, 18.0f)));



		// sets the accerlation
		if (m_iGear >= 1)
		{
			m_vAcceleration = subtractVectors(multiplyVectors(m_RotationVector, m_iPower * m_afGears[m_iGear]), Friction);
		}

		if (m_TurningRight || m_TurningLeft)
		{
			Turning();
		}
		else // if the car is no longer turning, slightly straighten up until straight
		{
			if (m_CarTurningAngle > 0)
			{
				m_CarTurningAngle -= 1;
			}
			else if (m_CarTurningAngle < 0)
			{
				m_CarTurningAngle += 1;
			}
		}

		if (m_iGear == -1) // if the car is revsering
		{
			m_iPower = 1000;
			m_vAcceleration = subtractVectors(multiplyVectors(m_RotationVector, -m_iPower), Friction);
		}

		if (m_iGear == 0) // If gear is 0 enter neutral
		{
			m_vAcceleration = subtractVectors(multiplyVectors(m_RotationVector, m_iPower - 1000), Friction);
		}

		ChangeGear(fTimePassed);
		//Euler
		m_vVel = addVectors(m_vVel, multiplyVectors(m_vAcceleration, fTimePassed));
		//Pos of car
		m_vPos.x = ((FrontTyres.x + BackTyres.x) / 2);
		m_vPos.y = ((FrontTyres.y + BackTyres.y) / 2);

		m_fRotationAngle = atan2f(FrontTyres.y - BackTyres.y, FrontTyres.x - BackTyres.x) * (180.0f / 3.14159f); // radians to deg
		m_Sprite.setPosition(m_vPos);

		//std::cout << m_Sprite.getPosition().x << "," << m_Sprite.getPosition().y << std::endl;
		//std::cout << m_vVel.x << "," << m_vVel.y << std::endl;
	
}


void car::ChangeGear(float timestep)
{
	// Changes gears and RPM so simulate realistic car acceleration

	if (m_iGear > 0) // If accelerating
	{

		m_iPower += timestep * m_aiAccelerationPower[m_iGear - 1]; // RPM increases by timestep multiplied by the accelerlation rates for each gear

		if (m_iGear == 1)
		{
			if (m_iPower > 4000) // 1st gear
			{

				m_iGear++;
				m_iPower = 2500;
			}
		}
		if (m_iGear == 2) //2nd gear
		{
			if (m_iPower > 5000)
			{
				m_iGear++;
				m_iPower = 3000;
			}
		}
		if (m_iGear == 3) // 3rd gear
		{
			if (m_iPower > 5500)
			{
				m_iGear++;
				m_iPower = 3500;
			}
		}
		if (m_iGear == 4) // 4th gear
		{
			if (m_iPower > 6000)
			{
				m_iGear++;
				m_iPower = 4000;
			}
		}
		if (m_iGear == 5)
		{
			if (m_iPower > 6500) // 5th gear limits the cars speed
			{
				m_iPower = 6500;
			}
		}
	}

	else // If not accelerating and not moving slow down car
	{
		if (m_iPower > 2000)
		{

			m_iPower -= timestep * m_aiAccelerationPower[1];
		}
	}


}

void car::Turning()
{
	if (m_TurningLeft)
	{
		m_CarTurningAngle -= 1;
	}
	else if (m_TurningRight)
	{
		m_CarTurningAngle += 1;
	}

}

// retuns car position
sf::Vector2f car::getPosition()
{
	return  m_Sprite.getPosition();
}

/**
instantiates the virtual function collides
\param *other. used for double dispatch - base class
allows us to exploit ploymorphism, this is the base class function that will call the other collides function
*/
void car::collides(Collidable *other)
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
void car::collides(Tyres *other)
{
	// temp new pos of a tyre - the car
	sf::Vector2f TempTyrePos(other->m_TyreSprite.getPosition().x - m_Sprite.getPosition().x, other->m_TyreSprite.getPosition().y - m_Sprite.getPosition().y);
	sf::Vector2f ClosestPoint;

	sf::Vector2f HalfExtents(m_Sprite.getLocalBounds().width / 2, m_Sprite.getLocalBounds().width / 2);

	//Rotate the tyre around by the car's rotation
	TempTyrePos = RotateVectors(TempTyrePos, m_Sprite.getRotation());

	//Sets up Clamp of car against the LocalTyrePos
	if (TempTyrePos.x >= 0)
	{
		ClosestPoint.x = (fmin(TempTyrePos.x, HalfExtents.x));
	}
	if (TempTyrePos.x < 0)
	{
		ClosestPoint.x = (fmax(TempTyrePos.x, -HalfExtents.x));
	}
	if (TempTyrePos.y >= 0)
	{
		ClosestPoint.y = (fmin(TempTyrePos.y, HalfExtents.y));
	}
	if (TempTyrePos.y < 0)
	{
		ClosestPoint.y = (fmax(TempTyrePos.y, -HalfExtents.y));
	}
	
	sf::Vector2f DifferenceTyreClosest(subtractVectors(TempTyrePos, ClosestPoint));

	float FinalDistance = magnitudeOfVector(DifferenceTyreClosest) - other->radius;

	if (FinalDistance <= -0.1) // collided
	{
		sf::Vector2f Norm(FinalDistance, 0);
		Norm = RotateVectors(Norm, m_Sprite.getRotation());
		sf::Vector2f newVel;
		newVel = (multiplyVectors(multiplyVectors(Norm, -(1 + 0.2)), fDotProduct(Norm, m_vVel)));

		// Limits new velocity to avoid overflow errors
		if (newVel.x >= 0)
		{
			newVel.x = (fmin(newVel.x, 600));
		}
		if (newVel.x < 0)
		{ 
			newVel.x = (fmax(newVel.x, -600));
		}
		if (newVel.y >= 0)
		{
			newVel.y = (fmin(newVel.y, 600));
		}
		if (newVel.y < 0)
		{
			newVel.y = (fmax(newVel.y, -600));
		}

		m_iPower = 1200;

		m_vVel = addVectors(m_vVel, newVel);

		other->m_vVel = addVectors(m_vVel, sf::Vector2f(-newVel.x, -newVel.y));
	}
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

// set the position of the car
void car::setPosition(Vector2f newPos)
{
	m_Sprite.setPosition(newPos);
}


void car::SetTexture(std::vector<Texture>::iterator Texture)
{
	m_Sprite.setTexture(*Texture);
}