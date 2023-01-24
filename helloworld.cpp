#include <X11/Xlib.h>
#include <iostream>

int main() {
  Display *d = XOpenDisplay(NULL);
  if (d == NULL) {
    std::cout << "Unable to open the display\n";
  }

  int s = DefaultScreen(d);

  Window w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, 100, 100, 1,
                                 BlackPixel(d, s), WhitePixel(d, s));

  XMapWindow(d, w);


  XPending(d);


  getchar();

  std::cout << "Exiting!!\n";
  return 0;
}
