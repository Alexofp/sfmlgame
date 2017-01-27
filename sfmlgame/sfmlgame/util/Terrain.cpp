#include "Terrain.h"
#include "GameWindow.h"
#include "TextureManager.h"

Terrain::Terrain()
{
	TextureManager::load("tex1", "resources/grass01.png");
	TextureManager::load("tex2", "resources/MossyCLiff_diffuse_2.png");
	TextureManager::load("tex3", "resources/mulch-tiled.jpg");
	TextureManager::load("tex1z", "resources/grass01_h.jpg");
	TextureManager::load("tex2z", "resources/MossyCLiff_Height.png");
	TextureManager::load("tex3z", "resources/mulch-heightmap.png");

	TextureManager::load("blend", "resources/blendmap.png");

	ground.setSize(sf::Vector2f(800, 800));
	ground.setPosition(0, 0);

	TextureManager::get("tex1")->setRepeated(true);
	TextureManager::get("tex2")->setRepeated(true);
	TextureManager::get("tex3")->setRepeated(true);
	TextureManager::get("tex1z")->setRepeated(true);
	TextureManager::get("tex2z")->setRepeated(true);
	TextureManager::get("tex3z")->setRepeated(true);
	ground.setTexture(TextureManager::get("tex1"));

	shader.loadFromFile("resources/groundShader.frag", sf::Shader::Fragment);
	shader.setUniform("scale", 0.2f);

	shader.setUniform("texture1", *TextureManager::get("tex1"));
	shader.setUniform("texture2", *TextureManager::get("tex2"));
	shader.setUniform("texture3", *TextureManager::get("tex3"));
	shader.setUniform("texture1z", *TextureManager::get("tex1z"));
	shader.setUniform("texture2z", *TextureManager::get("tex2z"));
	shader.setUniform("texture3z", *TextureManager::get("tex3z"));
	shader.setUniform("blendtexture", *TextureManager::get("blend"));
}


Terrain::~Terrain()
{
}

void Terrain::draw()
{


	GameWindow::getInternalHandle().draw(ground, &shader);
}
