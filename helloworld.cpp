#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include "shapes.cpp"
#include "game_display.cpp"
#include "game.cpp"

int main() {
  Game g;

  Vector gravity = {0,0.1};
  std::vector<Circle> c = {
      {{10, 10}, {1, 0}, 50 },
      {{900, 10}, {-1, 0}, 50 },
  };
  Bounds b = {1000,1000};

  g.run(c, gravity, b);

  return 0;
}
