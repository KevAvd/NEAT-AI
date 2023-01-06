#include "Mathlib.hpp"

bool circle_circle_collision(Vec2 p1, Vec2 p2, float r1, float r2){

    //Calculate distance^2 between both circles
    float length2 = (p1 - p2).length2();

    //Calculate min distance^2 for collision
    float min_dist2 = (r1 + r2)*(r1 + r2);

    //Check collision
    if(length2 < min_dist2) {
        return true;
    }

    return false;
}

// void solve_circle_circle(GameObject* obj1, GameObject* obj2){
//     Vec2 dist = obj2->position - obj1->position;
//     float length = dist.length();
//     float delta = (obj1->collider.radius + obj2->collider.radius - length) / 2;
//     dist.normalize();
//     obj2->position += (dist * delta) / obj2->mass;
//     obj1->position -= (dist * delta) / obj1->mass;
//     obj1->UpdateCollider();
//     obj2->UpdateCollider();
// }