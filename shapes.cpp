#ifndef SHAPES_CPP
#define SHAPES_CPP

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

Point addVector(Point p, Vector v) {
    Point new_p = {p.x+v.x, p.y+v.y};
    return new_p;
}

Vector addVec2Vec(Vector v1, Vector v2) {
    Vector v = {v1.x+v2.x, v1.y+v2.y};
    return v;
}
#endif /* SHAPES_CPP */
