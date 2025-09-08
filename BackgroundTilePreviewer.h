#pragma once
#ifndef	BACKGROUNDTILEPREVIEWER_H
#define BACKGROUNDTILEPREVIEWER_H

// Author: https://github.com/Katerine459 (K McKelvey)
#include <iostream>
#include <string.h>

#include <SFML/Graphics.hpp>

class BackgroundTilePreviewer
{
private:
	inline static const std::string fontFileAddr = "resources/fonts/SourceSerifPro-Semibold.otf";
	sf::Vector2u windowSize;
	std::string title;
	sf::VideoMode vm;
	sf::RenderWindow window;

	short xIndex = 0, yIndex = 0; // = 0 for the first tile in a row/column, 1 for the second tile, and so forth.
	short xOffset = 0, yOffset = 0, xOffsetBetween = 0, yOffsetBetween = 0; //Untested. Numbers are in pixels. For things like https://donitz.itch.io/procedural-tileset-generator, which has downloads where the tiles are separated by a few pixels. 0 is default. Use the more complicated constructor if this needs to change. (or just do a Zealous crop in the Gimp :) )
	sf::Vector2i tileSize;
	sf::Vector2i texCoord;

	sf::Texture fullImageTexture;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

	sf::Font aboutFont;
	sf::Text aboutText;

	void initWindow();
	void pollEvents();

	void initFullTexture(std::string file_addr);
	void setTileTexture();
	void initSprite();
	void initAboutText();
	void initAll(std::string file_addr, int x_tile_size, int y_tile_size, int x_offset, int y_offset, int x_offset_between, int y_offset_between);

	void setAboutText();

	void moveNext(); //Moves to the next tile, or goes back to the beginning

	void updating();
	void rendering();

public:
	BackgroundTilePreviewer(std::string file_addr, int x_tile_size, int y_tile_size);
	BackgroundTilePreviewer(std::string file_addr, int x_tile_size, int y_tile_size, int x_offset, int y_offset, int x_offset_between, int y_offset_between);
	~BackgroundTilePreviewer();

	void running();
};

#endif // BACKGROUNDTILEPREVIEWER_H