#ifndef PHYSICS_CPP
#define PHYSICS_CPP

#include "shapes.cpp"

Vector updateBounds(Point p, Vector vel, Bounds b) {
    Vector new_vel = vel;

    if (p.x < 0 || p.x > b.x_limit) {
        new_vel.x = -new_vel.x;
    }

    if (p.y < 0 || p.y > b.y_limit) {
        new_vel.y = -new_vel.y;
    }
    return new_vel;
}


void updateCircle(Circle &c, Vector gravity, Bounds b) {
        c.velocity = addVec2Vec(c.velocity, gravity);
        c.position = addVector(c.position, c.velocity);
        c.velocity = updateBounds(c.position, c.velocity, b);
}

#endif /* PHYSICS_CPP */
