#include "InputHandler.h"


InputHandler::InputHandler()
{
    udev = udev_new();

    li = libinput_udev_create_context(&interface, NULL, udev);
    libinput_udev_assign_seat(li, "seat0");
    libinput_dispatch(li);

    inputThread = std::thread(&InputHandler::inputLoop, this);
}

InputHandler::~InputHandler()
{
    // Tell loop it should stop
    quit = true;
    // Wait for it to stop
    inputThread.join();
    // Do the deallocation
    libinput_unref(li);
    udev_unref(udev);
}

int InputHandler::open_restricted(const char *path, int flags, void*)
{
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}
 
void InputHandler::close_restricted(int fd, void*)
{
    close(fd);
}

void InputHandler::inputLoop() {
    while(!quit)
    {
        while ((event = libinput_get_event(li)) != NULL) {
            // handle the event here
            libinput_event_destroy(event);
            libinput_dispatch(li);
        }
    }
}


double InputHandler::getX()
{
    return this->x;
}

double InputHandler::getY()
{
    return this->y;
}

double InputHandler::getPressure()
{
    return this->pressure;
}

