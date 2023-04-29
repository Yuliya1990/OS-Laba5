#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main() {
    Display *display = XOpenDisplay(nullptr);
    Window rootWindow = DefaultRootWindow(display);

    XEvent event;
    XGrabKeyboard(display, rootWindow, true, GrabModeAsync, GrabModeAsync, CurrentTime);

    std::cout << "Keyboard input capture started. Press Esc to exit." << std::endl;

    while (true) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            KeySym keySym;
            char keyBuffer[32];
            XLookupString(&event.xkey, keyBuffer, sizeof(keyBuffer), &keySym, nullptr);
            if (keySym == XK_Escape) {
                break;
            }
            std::cout << "Key pressed: " << keyBuffer << std::endl;
        }
    }

    XUngrabKeyboard(display, CurrentTime);
    XCloseDisplay(display);

    std::cout << "Keyboard input capture stopped." << std::endl;

    return 0;
}
