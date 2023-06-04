#include "LibinputManager.h"

#include <fcntl.h>

#include "ControlSurface.h"


LibinputManager::LibinputManager(ControlSurface& cs) : listener(cs)
{
    udev = udev_new();
    li = libinput_udev_create_context(&deviceInterface, NULL, udev);
    libinput_udev_assign_seat(li, "seat0");

    inputThread = std::thread(&LibinputManager::inputLoop, this);
}

LibinputManager::~LibinputManager()
{
    // Tell loop it should stop
    quit = true;
    // Wait for it to stop
    inputThread.join();
    // Do the deallocation
    libinput_unref(li);
    udev_unref(udev);
}

float LibinputManager::getPressure()
{
    return pressure;
}

int LibinputManager::openDevice(const char* path, int flags, void* /* user_data */)
{
    int fd = open(path, flags);
    return fd < 0 ? -errno : fd;
}

void LibinputManager::closeDevice(int fd, void* /* user_data */)
{
    close(fd);
}

void LibinputManager::inputLoop()
{
    libinput_event_type type;
    libinput_event_tablet_tool* tabletevent;

    while(!quit)
    {
        libinput_dispatch(li);
        while ((event = libinput_get_event(li)) != NULL) {

            type = libinput_event_get_type(event);

            if ((type == LIBINPUT_EVENT_TABLET_TOOL_TIP ) ||
                (type == LIBINPUT_EVENT_TABLET_TOOL_AXIS) ) {

                tabletevent = libinput_event_get_tablet_tool_event(event);

                // Update bool state values: near/not near, touching/not touching

                if (libinput_event_tablet_tool_get_tip_state(tabletevent) == LIBINPUT_TABLET_TOOL_TIP_DOWN) {
                    if (libinput_event_tablet_tool_x_has_changed(tabletevent)) {
                        x = libinput_event_tablet_tool_get_x(tabletevent);
                    }
                    if (libinput_event_tablet_tool_y_has_changed(tabletevent)) {
                        y = libinput_event_tablet_tool_get_y(tabletevent);
                    }
                    if (libinput_event_tablet_tool_pressure_has_changed(tabletevent)) {
                        pressure = libinput_event_tablet_tool_get_pressure(tabletevent);
                    }
                    listener.libinputContact(x / 216, y / 135, pressure); // TODO make size configurable
                } else {
                    listener.libinputRelease();
                }
            }
        }
        libinput_event_destroy(event);
    }
}
