#include "BackgroundTilePreviewer.h"

void BackgroundTilePreviewer::initWindow()
{
	windowSize.x = 1280;
	windowSize.y = 720;
	title = "Background tile previewer";
	vm = sf::VideoMode(sf::Vector2u(windowSize));
	window.create(vm, title);
	window.setFramerateLimit(60);
	window.clear();
}

void BackgroundTilePreviewer::pollEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>() ||
			(event->is<sf::Event::KeyPressed>() &&
				event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
			window.close();
		else if ((event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) ||
			(event->is<sf::Event::KeyPressed>() &&
				event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Space)) //go to next image if left mouse button clicked or Spacebar
		{
			moveNext();
		}

	}
}

void BackgroundTilePreviewer::initFullTexture(std::string file_addr)
{
	if (!fullImageTexture.loadFromFile(file_addr)) {
		std::cerr << "ERROR::BACKGROUNDTILEPREVIEWER::initTexture::COULD NOT LOAD FILE::" << file_addr << std::endl;
	}
}

void BackgroundTilePreviewer::setTileTexture()
{
	sf::IntRect tileRect(texCoord, tileSize);
	if (!tileTexture.loadFromImage(fullImageTexture.copyToImage(), false, tileRect)) {
		std::cerr << "ERROR::BACKGROUNDTILEPREVIEWER::setTileTexture::COULD NOT COPY RECT TO IMAGE" << std::endl;
	}
	tileTexture.setRepeated(true);
}

void BackgroundTilePreviewer::initSprite()
{
	int windowSizeX = static_cast<int>(windowSize.x), windowSizeY = static_cast<int>(windowSize.y);
	tileSprite.setTexture(tileTexture);
	tileSprite.setTextureRect(sf::IntRect({ 0,0 }, { windowSizeX, windowSizeY }));

}

void BackgroundTilePreviewer::initAboutText()
{
	if (!aboutFont.openFromFile(fontFileAddr)) {
		std::cerr << "ERROR::BACKGROUNDTILEPREVIEWER::initAboutText::COULD NOT LOAD FONT FILE::" << fontFileAddr << std::endl;
	}
	aboutText.setFont(aboutFont);
	aboutText.setFillColor(sf::Color::Yellow);
	aboutText.setCharacterSize(20);
	setAboutText();
}

void BackgroundTilePreviewer::initAll(std::string file_addr, int x_tile_size, int y_tile_size, int x_offset, int y_offset, int x_offset_between, int y_offset_between)
{
	tileSize = { x_tile_size, y_tile_size };
	xOffset = x_offset;
	xOffsetBetween = x_offset_between;
	yOffset = y_offset;
	yOffsetBetween = y_offset_between;

	texCoord = { xOffset, yOffset };

	initWindow();

	initFullTexture(file_addr);
	setTileTexture();
	initSprite();
	initAboutText();
}

void BackgroundTilePreviewer::setAboutText()
{
	std::string about, xIdxS, yIdxS, nIdxS, xCoordS, yCoordS;
	float textWidth;

	xCoordS = std::to_string(texCoord.x);
	yCoordS = std::to_string(texCoord.y);
	xIdxS = std::to_string(xIndex + 1);
	yIdxS = std::to_string(yIndex + 1);

	about = "Image, Row " + yIdxS + ", Col " + xIdxS + ". Coords: {" + xCoordS + ", " + yCoordS + "}";
	aboutText.setString(about);
	
	textWidth = aboutText.getLocalBounds().size.x;
	aboutText.setPosition({ static_cast<float>(windowSize.x) - (textWidth + 20.0f), 20.0f });
}

void BackgroundTilePreviewer::moveNext()
{
	sf::Vector2u imgSize;

	imgSize = fullImageTexture.getSize();
	texCoord.x += tileSize.x + xOffsetBetween;
	xIndex++;

	if ((texCoord.x + tileSize.x) > (imgSize.x - xOffset))
	{
		texCoord.x = xOffset; //go back to the beginning (after any left margin)
		xIndex = 0;

		// added: allow for multirow sheets (if at the end of a row, go to beginning of next row. If below the bottom of the image, go back to the beginning)
		texCoord.y += tileSize.y + yOffsetBetween;
		yIndex++;
		if ((texCoord.y + tileSize.y) > (imgSize.y - yOffset))
		{
			texCoord.y = yOffset;
			yIndex = 0;
		}
	}

	setTileTexture();
	setAboutText();
}

void BackgroundTilePreviewer::updating()
{
	pollEvents();
}

void BackgroundTilePreviewer::rendering()
{
	//render
	window.clear();

	//draw here!!
	window.draw(tileSprite);
	window.draw(aboutText);

	//show window
	window.display();
}

BackgroundTilePreviewer::BackgroundTilePreviewer(std::string file_addr, int x_tile_size, int y_tile_size) 
	: fullImageTexture(file_addr), tileSprite(tileTexture), aboutFont(fontFileAddr), aboutText(aboutFont, "")
{
	initAll(file_addr, x_tile_size, y_tile_size, 0, 0, 0, 0);
}

BackgroundTilePreviewer::BackgroundTilePreviewer(std::string file_addr, int x_tile_size, int y_tile_size, int x_offset, int y_offset, int x_offset_between, int y_offset_between) 
	: fullImageTexture(file_addr), tileSprite(tileTexture), aboutFont(fontFileAddr), aboutText(aboutFont, "")
{
	initAll(file_addr, x_tile_size, y_tile_size, x_offset, y_offset, x_offset_between, y_offset_between);
	
}

BackgroundTilePreviewer::~BackgroundTilePreviewer()
{
}

void BackgroundTilePreviewer::running()
{
	while (window.isOpen())
	{
		updating();
		rendering();
	}
}

