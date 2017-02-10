/** \file game.cpp
* cpp file for the game class.
* * Sets global parameters for the game
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game.h"

using namespace std;
using namespace sf;

Game::Game()
{
	m_TextureLoader.load(); // loads all in use textures
	SetBackground();
	m_Player1Car.setTexture(m_TextureLoader.getTextureIterator(3));
	m_bStartGame = false;

}

void Game::KeyPress(Keyboard::Key Key)
{
	if (Key == Keyboard::Up) // If 'Up' pressed then accelerate
	{
		m_Player1Car.setDirection(1);
	}

	if (Key == Keyboard::Right) // If  'Right' pressed then rotate clockwise
	{
		//m_Player1Car.m_bRotatingRight = true;
		//m_Player1Car.m_bRotatingLeft = false;
	}

	if ( Key == Keyboard::Left) //If  'Left' pressed then rotate anti-clockwise
	{
		//m_Player1Car.m_bRotatingRight = false;
		//m_Player1Car.m_bRotatingLeft = true;
	}

	if (Key == Keyboard::Down) // If 'Down' pressed then reverse
	{
		m_Player1Car.setDirection(-1);
	}



}



void Game::KeyRelease(Keyboard::Key Key)
{
	if (Key == Keyboard::Up) // If 'Up' Released then deacellerate
	{
		m_Player1Car.setDirection(0);
	}

	if (Key == Keyboard::Right) // If  'Right' Released then stop rotating clockwise
	{
		//m_Player1Car.m_bRotatingRight = true;
		//m_Player1Car.m_bRotatingLeft = false;
	}

	if (Key == Keyboard::Left) //If  'Left' Released then stop rotating anti-clockwise
	{
		//m_Player1Car.m_bRotatingRight = false;
		//m_Player1Car.m_bRotatingLeft = true;
	}

	if (Key == Keyboard::Down) // If 'Down'  Released then deacellerate
	{
		m_Player1Car.setDirection(0);
	}

	if (Key == Keyboard::Return) // starting the game
	{
		m_bStartGame = true;
		SetBackground();
	}
	if (Key == Keyboard::Num1) // starting the game
	{
		CreateTyreFile();
	}


}
void Game::SetBackground()
{
	if (m_bStartGame == true)
	{
		m_Background = background(m_TextureLoader.getTextureIterator(2), Vector2f(400,400));
	}
	else { m_Background = background(m_TextureLoader.getTextureIterator(0), Vector2f(514, 385)); }

}
void Game::CreateTyreFile()
{
	//Open file
	ofstream file;
	file.open("\\assets\\tyres.txt");

	//Write to file;
	for (int i = 0; i < m_TyreWall.size(); i++)
	{
		file << m_TyreWall.at(i)->m_vPos.x << " " << m_TyreWall.at(i)->m_vPos.y << endl;
	}
	//Close file
	file.close();

}

void Game::ReadTyreFile()
{
	ifstream TempFileHandle;
	string sLine;

	float fX;
	float fY;

	//Open file
	TempFileHandle.open("\\assets\\tyrepos.txt");
	if (TempFileHandle.is_open())
	{
		while (TempFileHandle >> fX >> fY) // While 2 floats with a space inbetween exist on each line
		{
			m_TyreWall.push_back(new Tyres(Vector2f(fX, fY), 0.1)); // Pushback new tyre with these X,Y positions
			m_TyreWall.back()->setTyreTexture(m_TextureLoader.getTextureIterator(1));// Set tyre texture
		}
	}
	// Close file
	TempFileHandle.close();
}

//Vector2f Game::getCarPos()

void Game::SpawnTyre(Vector2f Pos)
{
	m_TyreWall.push_back(new Tyres(Vector2f(Pos), 0.1)); // Pushback new tyre with these X,Y positions
	m_TyreWall.back()->setTyreTexture(m_TextureLoader.getTextureIterator(1));// Set tyre texture

}
void Game::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(m_Background);
	target.draw(m_Player1Car);

	for (int i = 0; i < m_TyreWall.size(); i++)
	{
		target.draw(*m_TyreWall.at(i));
	}

}
void Game::update(float timePass)
{
	m_Player1Car.Update(timePass);

	for (int i = 0; i < m_TyreWall.size(); i++)
	{
		m_TyreWall.at(i)->update(timePass);
	}


	for (int i = 0; i < m_TyreWall.size(); i++) // Looking for collisions
	{
		m_Player1Car.collides(m_TyreWall.at(i)); // Car colliding with tyres

		for (int j = 0; j < m_TyreWall.size(); j++)
		{
			if (i != j) // Stops Tyres from colliding with themselves
			{
				m_TyreWall.at(i)->collides(m_TyreWall.at(j)); // tyres colliding with tyres
			}
		}

	}


	m_HUD.Update();

	m_HUD.setTime1Position(m_Player1Car.getPosition().x - 300, m_Player1Car.getPosition().y + 70);  //!< set position of the first timer
	m_HUD.setTime2Position(m_Player1Car.getPosition().x - 300, m_Player1Car.getPosition().y + 95);  //!< set position of the second timer
	m_HUD.setTime3Position(m_Player1Car.getPosition().x - 300, m_Player1Car.getPosition().y + 120); //!< set position of the third timer
	m_HUD.setRectPosition(m_HUD.getPosition().x, m_HUD.getPosition().y); //!< set the background of the timers position

	m_HUD.LapCheck(m_Player1Car);

}

