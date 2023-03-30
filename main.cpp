#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include "game.cpp"
#include "game_display.cpp"
#include "shapes.cpp"
#include <cstdlib>
#include <time.h>

int main() {
  srand(time(0));

  Game g;

  Vector gravity = {0, 0.1};
  std::vector<Circle> c = {};

  int N = 10;
  for (int i = 0; i < N; i++) {
    c.push_back(randomCircle());
  }
  Bounds b = {1000, 1000};

  g.run(c, gravity, b);

  return 0;
}
