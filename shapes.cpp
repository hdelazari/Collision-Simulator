#ifndef SHAPES_CPP
#define SHAPES_CPP

#include <cstdlib>

struct Point {
  float x, y;
};

struct Vector {
  float x, y;
};

struct Circle {
  Point position;
  Vector velocity;
  float radius;
  long color;
};

struct Bounds {
  float x_limit;
  float y_limit;
};

Circle randomCircle() {
  float x = rand() % 1000;
  float y = rand() % 1000;
  float x_vel = ((rand() % 2001) - 1000) / 100.0;
  float y_vel = ((rand() % 2001) - 1000) / 100.0;
  float radius = rand() % 100;

  int red = rand() % 256;
  int green = rand() % 256;
  int blue = rand() % 256;

  long color = (red << 16) + (green << 8) + blue;

  return {{x, y}, {x_vel, y_vel}, radius, color};
}

Point addVector(Point p, Vector v) {
  Point new_p = {p.x + v.x, p.y + v.y};
  return new_p;
}

Vector addVec2Vec(Vector v1, Vector v2) {
  Vector v = {v1.x + v2.x, v1.y + v2.y};
  return v;
}
#endif /* SHAPES_CPP */
