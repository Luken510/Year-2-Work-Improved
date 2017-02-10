/** \file AABB.h
* Header file for the AABB class.
* * Allows subclasses to be manipulated
*/

#ifndef AABB_H
#define AABB_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "collidable.h"


using namespace sf;
//! The AABB Class
/*!
This Class will be used by AABB objects for future references
It Holds the vel, friction, mass, position and penetration (intercept)
*/

class AABB : public Collidable
{
protected:

	Vector2f m_vAcceleration; //!< Acceleration of a colliable object
	float m_fInverseMass;//!< inverse mass of a colliable object	
	float fPenetration; //!< instantiate the Penetration (intercept)
	float fCoefficient = 0.4f; //!< instantiate the value of coefficient
	float fGravity = 9.8f; //!< instantiate the value of gravity

	Vector2f getFriction(); //!< returns the friction of the AABB object
public:
	Vector2f m_vPos; //!< instantiate position
	Vector2f m_vVel; //!< velocity of a AABB object
	Vector2f m_vNormal; //!< instantiate the normal

	AABB(); //!< Default constructor
	//Vector2f getPos(); //!< return the position of the object
	//Vector2f getNormal(); //!< return the normal of the object
//	void setNormal(Vector2f &newNormal); //!< set the value of v_Normal
	//void setPos(float x, float y); //!< set the position, x and y
	float fDotProduct(Vector2f V1, Vector2f V2); //!< return the dotproduct of two vectors, the parameters are both vectors
	Vector2f subtractVectors(Vector2f V1, Vector2f V2);
	Vector2f addVectors(Vector2f V1, Vector2f V2);
	Vector2f multiplyVectors(Vector2f V1, Vector2f V2);
	Vector2f multiplyVectors(Vector2f V1, float Scalar);
	float magnitudeOfVector(Vector2f V1);
	Vector2f normaliseVectors(Vector2f V1);

};


#endif