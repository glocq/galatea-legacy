#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <thread>
#include <libudev.h>
#include <libinput.h>
#include <JuceHeader.h>

//==============================================================================
class InputHandler
{
public:
    explicit InputHandler();
    ~InputHandler();

    //==============================================================================
    double getX();
    double getY();
    double getPressure();

private:

    /**
     * Visible parameters
     */
    double x = 0.;
    double y = 0.;
    double pressure = 0.;

    /**
     * Threading
     */
    std::thread inputThread;
    void inputLoop();
    bool quit = false;

    /**
     * Low-level libinput stuff
     */

    // Udev context:
    struct udev* udev;
    // Libinput context:
    struct libinput *li;
    // We'll store each new event in there:
    struct libinput_event *event;

    static int open_restricted(const char *path, int flags, void *user_data);
    static void close_restricted(int fd, void *user_data);

    constexpr static struct libinput_interface interface = {
        .open_restricted = open_restricted,
        .close_restricted = close_restricted,
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputHandler)
};
