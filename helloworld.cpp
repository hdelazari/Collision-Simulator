#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>

namespace mygame {

class GameDisplay {
public:
	GameDisplay();
	~GameDisplay();

	Display *getDisplay();

	void drawRect(unsigned long col, int x, int y, int width, int height);
	void drawCircle();

private:
	Display *display_;
	int screen_;
	Window window_;
};

GameDisplay::GameDisplay()
{
	display_ = XOpenDisplay(NULL);
	if (display_ == NULL)
	{
		throw std::runtime_error("Unable to open the display");
	}

	screen_ = DefaultScreen(display_);

	window_ = XCreateSimpleWindow(display_, RootWindow(display_,screen_), 0, 0, 1000, 1000, 1,
                             BlackPixel(display_,screen_), WhitePixel(display_,screen_));

	XSelectInput(display_, window_, KeyPressMask | ExposureMask );
	XMapWindow(display_, window_);
}

GameDisplay::~GameDisplay() {
	XCloseDisplay(display_);
}

Display *GameDisplay::getDisplay() {
	return display_;
}

void GameDisplay::drawRect(unsigned long col, int x, int y, int width, int height) {
	XSetForeground(display_, DefaultGC(display_,screen_), col);
	XFillRectangle(display_, window_, DefaultGC(display_,screen_), x,y, width, height);
}

void GameDisplay::drawCircle() {
	long col = 0xff0000;
	int x = 20;
	int y = 20;
	int width = 100;
	int height = 100;
	XSetForeground(display_, DefaultGC(display_,screen_), col);
	XFillArc(display_, window_, DefaultGC(display_, screen_), x, y,width,height,0*64, 360*64);
}

class Game {
public:
	Game();

	void run();

private:
	GameDisplay gamedisplay_;
	XEvent event_;
	bool is_running_ = true;

	bool getEvent();
	void handleEvent();
};

Game::Game(){}

void Game::run() {
	while (is_running_) {
		if (getEvent()) {
			handleEvent();
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

void Game::handleEvent() {
	if (event_.type == Expose) {
		//gamedisplay_.drawRect(0x6091ab, 10,10, 20,40);
		gamedisplay_.drawCircle();
	}
}

}

int main() {
	mygame::Game g;

	g.run();

	return 0;
}

