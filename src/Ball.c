#include "simple_logger.h"

#include "camera.h"
#include "Ball.h"


void ball_think(Entity* self);
void ball_update(Entity* self);
void ball_free(Entity* self);

Entity *ball_new()
{
	Entity *self;
	self = entity_new();
	if (!self)
	{
		slog("Failed to spawn a ball entity");
		return NULL;
	}
	self->sprite = gf2d_sprite_load_all(
		"images/ball.png",
		16,
		16,
		1,
		0);
	self->frame = 0;
	self->position = vector2d(100,100);

	self->think = ball_think;	
	self->update = ball_update;
	self->free = ball_free;

	return self;
}


void ball_think(Entity* self)
{
	Vector2D screen;
	Vector2D dir = { 0 };
	Sint32 mx = 0, my = 0;
	if (!self) return;
	screen = camera_get_position();
	Uint32 mouseState = SDL_GetMouseState(&mx, &my);
	mx += screen.x;
	my += screen.y;
	if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		dir.x = self->position.x - mx;
		dir.y = self->position.y - my;
		vector2d_normalize(&dir);
		vector2d_scale(self->velocity, dir, 3);
	}
	vector2d_scale(self->velocity, self->velocity, 1.0f - 0.005f); //Apply deceleration to slow down the ball
}

/*
void ball_think(Entity* self)
{
	Vector2D screen;
	Vector2D dir = { 0 };
	Sint32 mx = 0, my = 0;
	if (!self) return;
	screen = camera_get_position();
	SDL_GetMouseState(&mx, &my);
	mx += screen.x;
	my += screen.y;
	if (self->position.x < mx) dir.x = 1;
	if (self->position.y < my) dir.y = 1;
	if (self->position.x > mx) dir.x = -1;
	if (self->position.y > my) dir.y = -1;
	vector2d_normalize(&dir);
	vector2d_scale(self->velocity, dir, 3);
}*/


void ball_update(Entity* self)
{
	if (!self)return;
	self->frame += 0.1;
	if (self->frame >= 1)self->frame = 0;

	vector2d_add(self->position, self->position, self->velocity);
	camera_center_on(self->position);
}

void ball_free(Entity* self)
{
	if (!self)return;
}

/*eol@eof*/