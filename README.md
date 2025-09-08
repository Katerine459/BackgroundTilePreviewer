# Background Tile Previewer

## Dependencies:
C++ 17+
SFML 3.0

## About:
This simple utility takes a "spritesheet" of possible repeating background tiles, and allows you to scroll through them (using the mouse or spacebar), previewing what each of them look like when displayed as a tiled background.

It also shows information indicating the tile in the spritesheet you're looking at.

Example render, previewing a tile from the "Grasses32x32_resized128x128.png" file (it looks blocky because the textures in that png file are meant to have an 8-bit feel. Your textures may be very different):
<img width="1280" height="749" alt="image" src="https://github.com/user-attachments/assets/6e751e3e-9e54-4cfd-9b56-3ef0e45ecefc" />

There are two constructors: a simple one (for spritesheets that don't have any margins or spacing between tiles):

`BackgroundTilePreviewer preview("tileGrasses128x128.png", 128, 128);`

^This takes 3 arguments: the file address, the width (size-x) (in pixels) and the height (size-y) (in pixels).

There's also a more complicated constructor, for situations where you have a tileset with margins and/or spacing in-between the tiles:

`BackgroundTilePreviewer preview("Grasses32x32_resized128x128.png", 128, 128, 4, 4, 12, 12);`

^The two 4's in the above line indicate the margins in that tileset (x, y). The two 12's indicate how many pixels are between the tiles (x, y).

It's provided as-is; it's something I made for my own use, and am just sharing in case anybody else finds it useful.

Please feel free to use, but do not distribute and pass it off as your own.
