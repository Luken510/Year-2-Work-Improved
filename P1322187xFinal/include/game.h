/** \file game.h
* Header file for the game class.
* * Sets global parameters for the game
*/

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "car.h"
#include "background.h"
#include "collidable.h"
#include "tyre.h"
#include "AABB.h"
#include "textureLoader.h"
//! The Game Class
/*!
This class sets 
*/

class Game : public Drawable

{
	private:
		car m_Player1Car; //!< player1 aka our car
		TextureLoader m_TextureLoader; //!< instance to load our textures
		Sprite m_Background; //!<  holds the current texture needed for the background
		vector<Tyres*> m_TyreWall;
		bool m_bStartGame;
		bool check = false;
	public:
		HUD m_HUD; //!< HUD for the game



		  Game(); //!<default constructor

		  void KeyPress(Keyboard::Key Key);
		  void KeyRelease(Keyboard::Key Key);
		  void SetBackground();
		  void CreateTyreFile();
		  void ReadTyreFile();
		  Vector2f getCarPos();
		  void SpawnTyre(Vector2f Pos);
		  void draw(RenderTarget &target, RenderStates states) const;
		  void update(float timePass);
		  bool DetectingLapCollisions(FloatRect *other);
		  void ViewLimits(View* View, Vector2f CarPos);
		  




};
#endif