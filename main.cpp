#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include "game.cpp"
#include "game_display.cpp"
#include "shapes.cpp"
#include "physics.cpp"
#include <cstdlib>
#include <time.h>


int main() {
  srand(time(0));

  Game g;
  WorldState ws = {};
  ws.gravity = {0, 0.1};
  ws.circles = {};

  int N = 1;
  for (int i = 0; i < N; i++) {
    ws.circles.push_back(randomCircle());
  }
  ws.bounds = {1000, 1000};

  g.run(ws);

  return 0;
}
