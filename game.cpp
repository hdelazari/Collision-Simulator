#ifndef GAME_CPP
#define GAME_CPP

#include "game_display.cpp"
#include "physics.cpp"
#include "shapes.cpp"
#include <X11/Xlib.h>

class Game {
public:
  Game();

  void run(WorldState ws);

private:
  GameDisplay gamedisplay_;
  XEvent event_;
  bool is_running_ = true;

  bool getEvent();
};

Game::Game() {}

void Game::run(WorldState ws) {
  int i = 0;
  float E;
  while (is_running_) {
    if (i == 10000) {
      for (Circle c : ws.circles) {
        E = -ws.gravity.y*c.position.y+dot(c.velocity,c.velocity)/2;
      printf("%f\t", E);
      }
      printf("\n");
      gamedisplay_.drawScreen(ws);
      updateWorldState(ws);
      i = 0;
    }
    i++;
    if (getEvent()) {
      gamedisplay_.drawScreen(ws);
    }
  }
}

bool Game::getEvent() {
  if (XPending(gamedisplay_.getDisplay())) {
    XNextEvent(gamedisplay_.getDisplay(), &event_);
    printf("EVENT: %d\n", event_.type);
    return true;
  }

  return false;
}
#endif /* GAME_CPP */
