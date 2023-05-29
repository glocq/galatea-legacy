#include "InputHandler.h"

#include <iostream> // for debugging purposes; should be deleted
#include <libinput.h>

InputHandler::InputHandler()
{
    udev = udev_new();

    li = libinput_udev_create_context(&interface, NULL, udev);
    libinput_udev_assign_seat(li, "seat0");

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

    // This is where libinput events are processed.
    // If you are modifying this, in addition to the API documentation
    // ( https://wayland.freedesktop.org/libinput/doc/latest/api/ ),
    // I recommend using the command `libinput debug-events`
    // to see what events get triggered when you do a gesture

    libinput_event_type type;
    libinput_event_tablet_tool* tabletevent;

    while(!quit)
    {
        libinput_dispatch(li);
        while ((event = libinput_get_event(li)) != NULL) {

            type = libinput_event_get_type(event);

            if ((type == LIBINPUT_EVENT_TABLET_TOOL_PROXIMITY) ||
                (type == LIBINPUT_EVENT_TABLET_TOOL_TIP      ) ||
                (type == LIBINPUT_EVENT_TABLET_TOOL_AXIS     ) ) {

                tabletevent = libinput_event_get_tablet_tool_event(event);


                // Update bool state values: near/not near, touching/not touching

                if (type == LIBINPUT_EVENT_TABLET_TOOL_PROXIMITY) {
                    if (libinput_event_tablet_tool_get_proximity_state(tabletevent) == LIBINPUT_TABLET_TOOL_PROXIMITY_STATE_IN) {
                        near = true;
                    } else if (libinput_event_tablet_tool_get_proximity_state(tabletevent) == LIBINPUT_TABLET_TOOL_PROXIMITY_STATE_OUT) {
                        near = false;
                    }
                } else if (type == LIBINPUT_EVENT_TABLET_TOOL_TIP) {
                    if (libinput_event_tablet_tool_get_tip_state(tabletevent) == LIBINPUT_TABLET_TOOL_TIP_DOWN) {
                        contact = true;
                    } else if (libinput_event_tablet_tool_get_tip_state(tabletevent) == LIBINPUT_TABLET_TOOL_TIP_UP) {
                        contact = false;
                    }
                }

                // Update axes values

                if (libinput_event_tablet_tool_x_has_changed(tabletevent)) {
                    x = libinput_event_tablet_tool_get_x(tabletevent);
                }
                if (libinput_event_tablet_tool_y_has_changed(tabletevent)) {
                    y = libinput_event_tablet_tool_get_y(tabletevent);
                }
                if (libinput_event_tablet_tool_distance_has_changed(tabletevent)) {
                    distance = libinput_event_tablet_tool_get_distance(tabletevent);
                }
                if (libinput_event_tablet_tool_pressure_has_changed(tabletevent)) {
                    pressure = libinput_event_tablet_tool_get_pressure(tabletevent);
                }
            }
        }
        libinput_event_destroy(event);
    }
}


double InputHandler::getX() {
    return x;
}

double InputHandler::getY() {
    return y;
}

double InputHandler::getPressure() {
    return pressure;
}

double InputHandler::getDistance() {
    return distance;
}

bool InputHandler::isNear() {
    return near;
}

bool InputHandler::isPenDown() {
    return contact;
}
