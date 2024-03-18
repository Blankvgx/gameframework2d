#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "gfc_types.h"
#include "gf2d_sprite.h"

/*
@purpose: Entity System for game
*/

typedef struct Entity_S
{
	Uint8		_inuse; /*Keeps track of memory usage*/
	Sprite		*sprite; /*Entity Grpahic*/
	float		frame; /*Current frame of animation for sprite*/
	Vector2D	position; /*Where on the screen to draw the entity*/
	Vector2D	velocity; /*How much the entities position changes per update*/
	void (*think)(struct Entity_S *self); /*Makes decisions*/
	void (*update)(struct Entity_S* self); /*Execute decisions*/
	void (*free)(struct Entity_S* self); /*Clean up allocated data*/
	void *data;
}Entity;

/*
@breif This initializes the entity managment system and queues up cleaning on exit
@param max the maximum number of entities that can exist at the same time.
*/
void entity_system_initialize(Uint32 max);

/*
@breif Clean up all active entities
@param ignore do not clean up this entity.
*/
void entity_clear_all(Entity *ignore);

/*
@breif Blank entity for use
@param NULL on no more room or error, a blank entity otherwise
*/
Entity* entity_new();

/*
@breif Clean up an entity, free its spot for future use.
@param self the entity to free.
*/
void entity_free(Entity *self);

/*
@breif run the think functions for all active entities
*/
void entity_system_think();

/*
@breif run the update functions for all active entities
*/
void entity_system_update();

/*
@breif draw all active entities
*/
void entity_system_draw();

#endif // !__ENTITY_H_