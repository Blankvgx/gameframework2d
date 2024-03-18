#ifndef __WORLD_H__
#define __WORLD_H__

#include "gf2d_sprite.h"

typedef struct
{
	Sprite* background;
	Sprite* tileLayer;
	Sprite* tileSet;
	Uint8* tileMap;
	Uint32 tileHeight;
	Uint32 tileWidth;
}World;

World* world_load(const char* filename);

World* world_test_new();

void world_setup_camera(World* world);

/*
@breif allocate a new empty world
@return NULL on error, or a blank world
*/
World* world_new();

/*
@breif free a previously allocated world
@param world the world to free
*/
void world_free(World* world);

/*
@breif draw the world
@param world the world to draw
*/
void world_draw(World* world);

#endif // !__WORLD_H__
