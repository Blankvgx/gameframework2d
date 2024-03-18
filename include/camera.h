#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "gfc_vector.h"
#include "gfc_shape.h"

Vector2D camera_get_position();

void camera_set_size(Vector2D size);

Vector2D camera_get_offset();

void camera_set_position(Vector2D position);

void camera_apply_bounds();

void camera_set_bounds(Rect bounds);

void camera_enable_binding(Bool bindCamera);

void camera_center_on(Vector2D target);

#endif // !__CAMERA_H_