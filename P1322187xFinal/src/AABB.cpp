/** \file AABB.cpp
* cpp file for the AABB class.
* contains all the parameters to create the AABB object and maintain it
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/window.hpp>
#include "AABB.h"


using namespace std;
using namespace sf;


AABB::AABB()
{

}

// return the dotproduct of two vectors, the parameters are both vectors
float AABB::fDotProduct(Vector2f V1, Vector2f V2)
{
	return V1.x * V2.x + V2.y * V1.y; 
}
Vector2f  AABB::subtractVectors(Vector2f V1, Vector2f V2)
{
	float i;
	float j;
	
	i = V1.x - V2.x;
	j = V1.y - V2.y;

	return Vector2f(i, j);

}

Vector2f  AABB::addVectors(Vector2f V1, Vector2f V2)
{
	float i;
	float j;

	i = V1.x + V2.x;
	j = V1.y + V2.y;

	return Vector2f(i, j);
}
Vector2f  AABB::multiplyVectors(Vector2f V1, Vector2f V2)
{
	float i;
	float j;

	i = V2.x * V1.x;
	j = V2.y * V1.y;

	return Vector2f(i, j);



}
Vector2f  AABB::multiplyVectors(Vector2f V1, float Scalar)
{

	float i;
	float j;

	i = Scalar * V1.x;
	j = Scalar * V1.y;

	return Vector2f(i, j);
}

float  AABB::magnitudeOfVector(Vector2f V1)
{
	float i;
	float j;

	i = V1.x * V1.x;
	j = V1.y * V1.y;
	
	return sqrt(i + j);
}

Vector2f  AABB::normaliseVectors(Vector2f V1)
{
	float i = magnitudeOfVector(V1);

	return multiplyVectors(V1, (1.0f / i));

}


Vector2f AABB::getFriction()
{
	// Velocity multiplied by reasononable coefficent of rubber against concreate mutiplied by earths gravity
	float A = m_vVel.x * fCoefficient * fGravity;
	float B = m_vVel.y * fCoefficient * fGravity;

	Vector2f friction(A, B);

	return friction; // Returns a reasonable friction vector
}

Vector2f AABB::RotateVectors(Vector2f V1, float angle)
{
	angle = angle * (3.1415 / 180);

	Vector2f newRotatedVec;
	newRotatedVec.x = ((V1.x * cosf(angle)) + (V1.y * -sinf(angle)));
	newRotatedVec.y = ((V1.x * sinf(angle)) + (V1.y * cosf(angle)));

	return newRotatedVec;
}