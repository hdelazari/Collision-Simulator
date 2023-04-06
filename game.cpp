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
  while (is_running_) {
    if (i == 100000) {
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
