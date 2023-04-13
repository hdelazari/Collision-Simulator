#ifndef PHYSICS_CPP
#define PHYSICS_CPP

#include "shapes.cpp"
#include <cstdlib>
#include <vector>

void updateBounds(Circle &circle, Bounds b, Vector gravity) {
  // Check if the circle is out of bounds along the x-axis
  if (circle.position.x - circle.radius < 0) {
    float extra_distance = (circle.radius - circle.position.x);
    circle.velocity.x = -circle.velocity.x;
    //circle.position.x = circle.radius;
    circle.position.x += 2*extra_distance;
    //circle.position.x = extra_distance;
  } else if (circle.position.x + circle.radius > b.x_limit) {
    float extra_distance = (circle.radius + circle.position.x - b.x_limit);
    circle.velocity.x = -circle.velocity.x;
    //circle.position.x = b.x_limit - circle.radius;
    circle.position.x -= 2*extra_distance;
    // circle.position.x = b.x_limit - extra_distance;
  }

  // Check if the circle is out of bounds along the y-axis
  if (circle.position.y - circle.radius < 0) {
    float extra_distance = (circle.radius - circle.position.y);
    printf("Extra time %f\n", extra_distance/circle.velocity.y);
    circle.velocity.y = -circle.velocity.y-2*gravity.y*extra_distance/circle.velocity.y;
    //circle.position.y = circle.radius;
    circle.position.y += 2*extra_distance;
    //circle.position.y = extra_distance;
  } else if (circle.position.y + circle.radius > b.y_limit) {
    float extra_distance = (circle.radius + circle.position.y - b.y_limit);
    printf("Extra time: %f\n", extra_distance/circle.velocity.y);
    circle.velocity.y = -circle.velocity.y+2*gravity.y*extra_distance/circle.velocity.y;
    //circle.position.y = b.y_limit - circle.radius;
    circle.position.y -= 2*extra_distance;
    //circle.position.y = b.y_limit - extra_distance;
  }
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
  updateBounds(c, b,gravity);
}

void collide(Circle &circle1, Circle &circle2) {
  float d = distance(circle1.position, circle2.position);

  if (d <= circle1.radius + circle2.radius) {
    // Calculate the normal unit vector
    Vector normal = (circle2.position - circle1.position) / d;

    // Calculate the tangent unit vector
    Vector tangent = {-normal.y, normal.x};

    // Calculate the normal and tangential components of the velocity vectors
    // for both circles
    float dp1n = dot(circle1.velocity, normal);
    float dp1t = dot(circle1.velocity, tangent);
    float dp2n = dot(circle2.velocity, normal);
    float dp2t = dot(circle2.velocity, tangent);

    // Swap the normal components of the velocities for the two circles
    // (assuming perfectly elastic collision)
    std::swap(dp1n, dp2n);

    // Recompose the velocity vectors by adding the swapped normal components
    // and the unchanged tangential components
    circle1.velocity = tangent * dp1t + normal * dp1n;
    circle2.velocity = tangent * dp2t + normal * dp2n;
  }
}

void updateWorldState(WorldState &ws) {
  for (int i = 0; i < ws.circles.size(); i++) {
    updateCircle(ws.circles[i], ws.gravity, ws.bounds);
  }

  for (int i = 0; i < ws.circles.size(); i++) {
    for (int j = i + 1; j < ws.circles.size(); j++) {
      collide(ws.circles[i], ws.circles[j]);
    }
  }
}
#endif /* PHYSICS_CPP */
