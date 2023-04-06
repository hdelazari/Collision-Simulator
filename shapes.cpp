#ifndef SHAPES_CPP
#define SHAPES_CPP

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>


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
Vector operator*(Vector v, float s) { return s * v; }
Vector operator/(Vector v, float s) { return (1/s) * v; }

Point operator+(Point p, Vector v) {
  Point new_p = {p.x + v.x, p.y + v.y};
  return new_p;
}

Vector operator-(Vector a, Vector b) {
  Vector result = {a.x - b.x, a.y - b.y};
  return result;
}

Vector operator-(Point a, Point b) {
  Vector result = {a.x - b.x, a.y - b.y};
  return result;
}

float dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

float distance(Point a, Point b) {
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
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

struct WorldState {
  std::vector<Circle> circles;
  Bounds bounds;
  Vector gravity;
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

void printCircle(Circle c) {
  printf("Position {%f,%f}\nVelocity {%f,%f}\n", c.position.x, c.position.y, c.velocity.x, c.velocity.y);
}

#endif /* SHAPES_CPP */
