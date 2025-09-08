# Background Tile Previewer

## Dependencies:
C++ 17+
SFML 3.0

## About:
Quite simply, this simple utility takes a "spritesheet" of possible repeating background tiles, and allows you to scroll through them (using the mouse or spacebar), previewing what each of them look like when displayed as a tiled background.

It also shows information about which tile in the spritesheet you're looking at (0-based, so the "2 image in the 0 row" is the third image in the first row).

Example render, looking at the "Grasses32x32_resized128x128.png" file:
<img width="1277" height="749" alt="image" src="https://github.com/user-attachments/assets/89c97bb0-f757-4518-8da2-f851ffab664c" />

There are two constructors: a simple one (for spritesheets that don't have any margins or spacing between tiles):

`BackgroundTilePreviewer preview("tileGrasses128x128.png", 128, 128);`

^This takes 3 arguments: the file address, the width (size-x) (in pixels) and the height (size-y) (in pixels).

There's also a more complicated constructor, for situations where you have a tileset with margins and/or spacing in-between the tiles:

`BackgroundTilePreviewer preview("Grasses32x32_resized128x128.png", 128, 128, 4, 4, 12, 12);`

^The 4s in the above line indicate the margins in that tileset (x and y, respectively). The 12s indicate the spaces between the tiles.

It's provided as-is; it's something I made for my own use, and am just sharing in case anybody else finds it useful.

Please feel free to use, but do not distribute and pass it off as your own.
