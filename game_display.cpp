#ifndef GAME_DISPLAY
#define GAME_DISPLAY

#include <X11/Xlib.h>
#include <vector>
#include <stdexcept>

#include "shapes.cpp"

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
  XSetForeground(display_, DefaultGC(display_, screen_), c.color);
  XFillArc(display_, window_, DefaultGC(display_, screen_), int(c.position.x), int(c.position.y), int(2*c.radius),int(2*c.radius) ,
           0 * 64, 360 * 64);
}

void GameDisplay::drawScreen(std::vector<Circle> circles) {
    XClearWindow(display_, window_);
    for (Circle c : circles) {
        drawCircle(c);
    }
}

#endif /* GAME_DISPLAY */
