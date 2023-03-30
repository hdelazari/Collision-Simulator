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

void rungeKutta(Point &p, Vector &v, Vector gravity, float time) {
  Vector k1, k2, k3, k4;
  k1 = v + 0 * gravity;
  k2 = v + (time / 2) * gravity;
  k3 = v + (time / 2) * gravity;
  k4 = v + time * gravity;
  p = p + (time / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
  v = k4;
}

void updateCircle(Circle &c, Vector gravity, Bounds b) {
  rungeKutta(c.position, c.velocity, gravity, 1);
  c.velocity = updateBounds(c.position, c.velocity, b);
}

#endif /* PHYSICS_CPP */
