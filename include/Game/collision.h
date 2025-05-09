#ifndef COLLISION_H
#define COLLISION_H

#include "game_object.h"
#include "projectile_object.h"

// bool checkCollision(GameObject &one, GameObject &two);  // AABB
bool checkCollision(ProjectileObject &one, GameObject &two);

#endif