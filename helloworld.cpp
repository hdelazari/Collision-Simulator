#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>
#include <vector>

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

struct Bounds {
    float x_limit;
    float y_limit;
};

Vector updateBounds(Point p, Vector vel, Bounds b) {
    Vector new_vel = vel;

    if (p.x < 0 || p.x > b.x_limit) {
        new_vel.x = -new_vel.x;
    }

    if (p.y < 0 || p.y > b.y_limit) {
        new_vel.y = -new_vel.y;
    }
    return new_vel;
}

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

  void drawScreen(std::vector<Circle> c);

private:
  Display *display_;
  int screen_;
  Window window_;
};

GameDisplay::GameDisplay() {
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
  XSetForeground(display_, DefaultGC(display_, screen_), col);
  XFillArc(display_, window_, DefaultGC(display_, screen_), int(c.position.x), int(c.position.y), int(2*c.radius),int(2*c.radius) ,
           0 * 64, 360 * 64);
}

void updateCircle(Circle &c, Vector gravity, Bounds b) {
        c.velocity = addVec2Vec(c.velocity, gravity);
        c.position = addVector(c.position, c.velocity);
        c.velocity = updateBounds(c.position, c.velocity, b);
}

class Game {
public:
  Game();

  void run(std::vector<Circle> c, Vector gravity, Bounds b);

private:
  GameDisplay gamedisplay_;
  XEvent event_;
  bool is_running_ = true;

  bool getEvent();
};

Game::Game() {}

void Game::run(std::vector<Circle> circles, Vector gravity, Bounds b) {
  int i=0;
  while (is_running_) {
    if (i==10000){
        gamedisplay_.drawScreen(circles);
        for (Circle &c : circles) {
            updateCircle(c, gravity, b);
        }
        i=0;
    }
    i++;
    if (getEvent()) {
      gamedisplay_.drawScreen(circles);
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

void GameDisplay::drawScreen(std::vector<Circle> circles) {
    XClearWindow(display_, window_);
    for (Circle c : circles) {
        drawCircle(c);
    }
}

} // namespace mygame

int main() {
  mygame::Game g;

  mygame::Vector gravity = {0,0.1};
  std::vector<mygame::Circle> c = {
      {{10, 10}, {1, 0}, 50 },
      {{900, 10}, {-1, 0}, 50 },
  };
  mygame::Bounds b = {1000,1000};

  g.run(c, gravity, b);

  return 0;
}
