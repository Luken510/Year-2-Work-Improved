#include <TextureLoader.h>

TextureLoader::TextureLoader()
{
	m_sBaseDirectory = "./assets/"; //Default base directory
	load();
}


void TextureLoader::setBaseDirectory(string dir) // Allows base directory to be changed if neccessary
{
	m_sBaseDirectory = dir;
}

void TextureLoader::load() // Loads in all needed textures and adds them to the textures vector
{

	vector<string>fileNames;
	fileNames.push_back("pictures/mainmenubg.png");
	fileNames.push_back("pictures/Tyre.png");
	fileNames.push_back("pictures/track.png");
	fileNames.push_back("pictures/car.png");

	for (int i = 0; i < fileNames.size(); i++)
	{
		if (!m_Holder.loadFromFile(m_sBaseDirectory + fileNames.at(i)))
		{
			cout << "Could not load " << fileNames.at(i) << endl;
		}
		textures.push_back(m_Holder);
	}
}

vector<Texture>::iterator TextureLoader::getTextureIterator(int index) //Allows the assigning of textures to sprites
{
	return vector<Texture>::iterator(textures.begin() + index);
}