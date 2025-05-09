#include "../../include/Game/collision.h"

// bool checkColision(GameObject &one, GameObject &two) {  // AABB
//     glm::vec2 posOne = one.Position;
//     glm::vec2 posTwo = two.Position;
    
//     bool collisionX = posOne.x <= posTwo.x + two.Size.y && posTwo.x <= posOne.x + one.Size.x;
//     bool colllisionY = posOne.y <= posTwo.y + two.Size.y && posTwo.y <= posOne.y + one.Size.y;

//     return collisionX && colllisionY;
// }

bool checkCollision(ProjectileObject &one, GameObject &two){  // Circle Collision
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(
        two.Position.x + aabb_half_extents.x, 
        two.Position.y + aabb_half_extents.y
    );
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    return glm::length(difference) < one.Radius;
}
