#ifndef COLLISION_H
#define COLLISION_H

#include "game_object.h"
#include "projectile_object.h"

bool checkCollision2GameObjects(GameObject &one, GameObject &two);  // AABB
bool checkCollisionProjGameObject(ProjectileObject &one, GameObject &two);

#endif