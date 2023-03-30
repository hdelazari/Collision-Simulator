#ifndef SHAPES_CPP
#define SHAPES_CPP

#include <cstdlib>

struct Point {
  float x, y;
};

struct Vector {
  float x, y;

  Vector operator+(Vector other) {
    Vector sum = {x + other.x, y + other.y};
    return sum;
  }
};

Vector operator*(float s, Vector v) {
  Vector new_v = {s * v.x, s * v.y};
  return new_v;
}

Point operator+(Point p, Vector v) {
  Point new_p = {p.x + v.x, p.y + v.y};
  return new_p;
}

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

#endif /* SHAPES_CPP */
