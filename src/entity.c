#include "simple_logger.h"

#include "camera.h"
#include "entity.h"

typedef struct
{
	Entity* entity_list;
	Uint32	entity_max;

}EntityManager;

void entity_system_close();

static EntityManager _entity_manager = { 0 }; /*Initialize a local global entity manager*/

void entity_system_initialize(Uint32 max)
{
	if (_entity_manager.entity_list)
	{
		slog("cannot have 2 instances of entity manager");
		return;
	}
	if (!max)
	{
		slog("cannot allocate 0 entities!");
		return;
	}
	_entity_manager.entity_list = gfc_allocate_array(sizeof(Entity), max);
	if (!_entity_manager.entity_list)
	{	
		slog("failed to allocate global entity list");
		return;
	}
	_entity_manager.entity_max = max;
	atexit(entity_system_close);
}

void entity_system_close()
{
	entity_clear_all(NULL);
	if(_entity_manager.entity_list)free(_entity_manager.entity_list);
	memset(&_entity_manager, 0, sizeof(EntityManager));
}

void entity_clear_all(Entity* ignore)
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (&_entity_manager.entity_list[i] == ignore)continue;
		if (!_entity_manager.entity_list[i]._inuse)continue;	/*Skips this iteration of the loop*/
		entity_free(&_entity_manager.entity_list[i]);
	}
}

Entity* entity_new()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (_entity_manager.entity_list[i]._inuse)continue;	/*Skips any active entities*/
		memset(&_entity_manager.entity_list[i], 0, sizeof(Entity));
		_entity_manager.entity_list[i]._inuse = 1;
		//setting default color
		//setting default scale
		return &_entity_manager.entity_list[i];
	}
	slog("No more available entities");
	return NULL;
}

void entity_free(Entity* self)
{
	if (!self)return; //Cant do work on nothing
		gf2d_sprite_free(self->sprite);
		//Anything else we allocate for entity gets cleaned up here
		if (self->free)self->free(self->data);
}

void entity_think(Entity* self)
{
	if (!self)return;
	//Any boilerplate think stuff here
	if (self->think)self->think(self);
}

void entity_system_think()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;	/*Skips any inactive entities*/
		entity_think(&_entity_manager.entity_list[i]);
	}
}

void entity_update(Entity* self)
{
	if (!self)return;
	//Any boilerplate update stuff here
	if (self->update)self->update(self);
}

void entity_system_update()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;	/*Skips any inactive entities*/
		entity_update(&_entity_manager.entity_list[i]);
	}
}

void entity_draw(Entity* self)
{
	Vector2D offset,position;
	if (!self)return;
	offset = camera_get_offset();
	vector2d_add(position, self->position, offset);
	if (self->sprite)
	{
		gf2d_sprite_render(
			self->sprite,
			position,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			(Uint32)self->frame);
	}
}

void entity_system_draw()
{
	int i;
	for (i = 0; i < _entity_manager.entity_max; i++)
	{
		if (!_entity_manager.entity_list[i]._inuse)continue;	/*Skips any inactive entities*/
		entity_draw(&_entity_manager.entity_list[i]);
	}
}

/*eol@eof*/