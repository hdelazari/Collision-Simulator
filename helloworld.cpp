#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>

namespace mygame {

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
};

Point addVector(Point p, Vector v) {
    Point new_p = {p.x+v.x, p.y+v.y};
    return new_p;
}

Vector addVec2Vec(Vector v1, Vector v2) {
    Vector v = {v1.x+v2.x, v1.y+v2.y};
    return v;
}

    
class GameDisplay {
public:
  GameDisplay();
  ~GameDisplay();

  Display *getDisplay();

  void drawRect(unsigned long col, int x, int y, int width, int height);
  void drawCircle(Circle c);

private:
  Display *display_;
  int screen_;
  Window window_;
  int ball_x, ball_y;
};

GameDisplay::GameDisplay() {
  ball_x = 100;
  ball_y = 10;

  display_ = XOpenDisplay(NULL);
  if (display_ == NULL) {
    throw std::runtime_error("Unable to open the display");
  }

  screen_ = DefaultScreen(display_);

  window_ = XCreateSimpleWindow(display_, RootWindow(display_, screen_), 0, 0,
                                1000, 1000, 1, BlackPixel(display_, screen_),
                                WhitePixel(display_, screen_));

  XSelectInput(display_, window_, KeyPressMask | ExposureMask);
  XMapWindow(display_, window_);
}

GameDisplay::~GameDisplay() { XCloseDisplay(display_); }

Display *GameDisplay::getDisplay() { return display_; }

void GameDisplay::drawRect(unsigned long col, int x, int y, int width,
                           int height) {
  XSetForeground(display_, DefaultGC(display_, screen_), col);
  XFillRectangle(display_, window_, DefaultGC(display_, screen_), x, y, width,
                 height);
}

void GameDisplay::drawCircle(Circle c) {
  long col = 0xff0000;
  XClearWindow(display_, window_);
  XSetForeground(display_, DefaultGC(display_, screen_), col);
  XFillArc(display_, window_, DefaultGC(display_, screen_), int(c.position.x), int(c.position.y), int(2*c.radius),int(2*c.radius) ,
           0 * 64, 360 * 64);
}

class Game {
public:
  Game();

  void run(Circle c, Vector gravity);

private:
  GameDisplay gamedisplay_;
  XEvent event_;
  bool is_running_ = true;

  bool getEvent();
  void handleEvent(Circle c);
};

Game::Game() {}

void Game::run(Circle c, Vector gravity) {
  int i=0;
  while (is_running_) {
    if (i==10000){
        handleEvent(c);
        c.velocity = addVec2Vec(c.velocity, gravity);
        c.position = addVector(c.position, c.velocity);
        i=0;
    }
    i++;
    if (getEvent()) {
      handleEvent(c);
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

void Game::handleEvent(Circle c) {
    gamedisplay_.drawCircle(c);
}

} // namespace mygame

int main() {
  mygame::Game g;

  mygame::Vector gravity = {0,0.1};
  mygame::Circle c = {{10, 10}, {0, 0}, 50 };

  g.run(c, gravity);

  return 0;
}
