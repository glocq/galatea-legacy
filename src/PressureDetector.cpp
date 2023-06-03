#include "PressureDetector.h"

#include <fcntl.h>


PressureDetector::PressureDetector()
{
    udev = udev_new();
    li = libinput_udev_create_context(&deviceInterface, NULL, udev);
    libinput_udev_assign_seat(li, "seat0");

    inputThread = std::thread(&PressureDetector::inputLoop, this);
}

PressureDetector::~PressureDetector()
{
    // Tell loop it should stop
    quit = true;
    // Wait for it to stop
    inputThread.join();
    // Do the deallocation
    libinput_unref(li);
    udev_unref(udev);
}

float PressureDetector::getPressure()
{
    return pressure;
}

int PressureDetector::openDevice(const char* path, int flags, void* /* user_data */)
{
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}

void PressureDetector::closeDevice(int fd, void* /* user_data */)
{
    close(fd);
}

void PressureDetector::inputLoop()
{
    libinput_event_type type;
    libinput_event_tablet_tool* tabletevent;

    while(!quit)
    {
        libinput_dispatch(li);
        while ((event = libinput_get_event(li)) != NULL) {

            type = libinput_event_get_type(event);

            if (type == LIBINPUT_EVENT_TABLET_TOOL_TIP || type == LIBINPUT_EVENT_TABLET_TOOL_AXIS) {
                tabletevent = libinput_event_get_tablet_tool_event(event);
                pressure = libinput_event_tablet_tool_get_pressure(tabletevent);
            }
        }
        libinput_event_destroy(event);
    }
}
