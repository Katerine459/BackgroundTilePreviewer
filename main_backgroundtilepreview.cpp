#pragma once

#include "BackgroundTilePreviewer.h"

int main()
{
	//BackgroundTilePreviewer preview("tileGrasses128x128.png", 128, 128);
	BackgroundTilePreviewer preview("Grasses32x32_resized128x128.png", 128, 128, 4, 4, 12, 12);

	preview.running();

	return 0;
}