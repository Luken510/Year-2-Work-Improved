/** \file tyre.cpp
* cpp file for Tyre class.
* * instantiates the values and functions needed to create the Tyre class
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/window.hpp>
#include "tyre.h"

using namespace std;
using namespace sf;

Tyres::Tyres()
{

}



Tyres::Tyres(Vector2f position, float inverseMass)
{

	m_TyreSprite.setOrigin(((m_TyreSprite.getLocalBounds().width) / 2.0f), ((m_TyreSprite.getLocalBounds().height) / 2.0f));
	m_TyreSprite.setScale(1, 1);
	m_fInverseMass = inverseMass;
	m_vAcceleration = Vector2f(0, 0);
	m_vVel = Vector2f(0, 0);
	radius = 21;
	m_TyreSprite.setPosition(position);
	m_vPos = position;
	
};
// draw function
void Tyres::draw(RenderTarget &target, RenderStates states) const
{

	target.draw(m_TyreSprite);
	
}

/**
Virtual function collides
\param *other. used for double dispatch - base class
allows us to exploit ploymorphism, this is the base class function that will call the other collides function
*/
void Tyres::collides(Collidable *other)
{
	return other->collides(this);
}
/**
Virtual function collides
\param *other. used for double dispatch - Tyre Class
*/
void Tyres::collides(Tyres *other)
{
	// create tyre positions
	Vector2f TyreA(m_TyreSprite.getPosition().x, m_TyreSprite.getPosition().y);
	Vector2f TyreB(other->m_TyreSprite.getPosition().x, other->m_TyreSprite.getPosition().y);

	//stores the Tyres radius
	float RadiusA = radius;
	float RadiusB = other->radius;
	//total of the radii
	float SumOfRadii = RadiusA + RadiusB;
	//calculating the distance between the two points - used to find the magnitude
	Vector2f Distance = subtractVectors(TyreB,TyreA);

	// magnitude of the distance, - used to find the finaldistance
	float DistMagnitude = magnitudeOfVector(Distance);

	float FinalDistance = DistMagnitude - SumOfRadii; // Final distance is the magitude of the distance - sum of radii

	if (FinalDistance <= 0) // a collision has occured
	{
		Vector2f CollisionNorm = normaliseVectors(Distance);
		
		float newVel;
		//New Velocity 
		newVel = (-(1 + 0.5) * ( fDotProduct(subtractVectors(m_vVel, other->m_vVel), CollisionNorm))) / (m_fInverseMass + other->m_fInverseMass);

		m_vVel = addVectors(m_vVel, multiplyVectors(multiplyVectors(CollisionNorm, newVel), m_fInverseMass));
		other->m_vVel = addVectors(other->m_vVel, multiplyVectors(multiplyVectors(CollisionNorm, -newVel), other->m_fInverseMass));

		// correcting the position
		m_vPos = addVectors(m_vPos, multiplyVectors(CollisionNorm, FinalDistance));
	}

}

void Tyres::update(float timepassed)
{
	m_vAcceleration = subtractVectors(Vector2f(0, 0), getFriction());

	//Euler collisions
	m_vVel = addVectors(m_vVel, multiplyVectors(m_vAcceleration, timepassed));
	m_vPos = addVectors(m_vPos, multiplyVectors(m_vVel, timepassed));
	m_TyreSprite.setPosition(m_vPos);
}
void Tyres::setTyreTexture(vector<Texture>::iterator Texture) //!< function that sets the Tyres texture
{
	m_TyreSprite.setTexture(*Texture);
	m_TyreSprite.setOrigin(m_TyreSprite.getLocalBounds().width / 2.0f, m_TyreSprite.getLocalBounds().height / 2.0f);
	m_TyreSprite.setScale(2, 2);
}