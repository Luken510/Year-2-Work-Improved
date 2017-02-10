
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


//! The TextureLoader Class
/*!
 The Texture Loader makes loading in textures far more efficient as a
 new texture doesn't need to be loaded in everytime a new instance of something
 is created.
*/

class TextureLoader
{
private:

	vector<Texture> textures;///< A vector of textures - all textures used in the program should be loaded into this.
	string m_sBaseDirectory;///< base directory to find textures
	Texture m_Holder; ///< A temp m_Holder of a texture before it is added to the vector of textures;

public:
	TextureLoader();


	void setBaseDirectory(string dir);//!< sets the base directory to be used

	/**
	Load function that loads all the used textures
	*/
	void load();

	/**
	Allows textures from the Texture Loader to be used for sprite in other classes	
	\param index which is the position of the texture i.e 1 = car texture
	\returns The texture from the index
	*/

	vector<Texture>::iterator getTextureIterator(int index);
};

#endif

