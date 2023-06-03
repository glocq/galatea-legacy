#pragma once

#include <thread>
#include <libudev.h>
#include <libinput.h>


class PressureDetector
{
public:
    PressureDetector();
    ~PressureDetector();

    float getPressure();

private:
    struct udev* udev; // udev context
    struct libinput* li; // libinput context
    struct libinput_event* event; // we'll store each new event in there

    // Tell libinput how to open/close devices:
    static int openDevice(const char* path, int flags, void* user_data);
    static void closeDevice(int fd, void* user_data);

    constexpr static struct libinput_interface deviceInterface = {
        .open_restricted  = openDevice,
        .close_restricted = closeDevice
    };

    // Input loop, which will listen for new events
    std::thread inputThread;
    void inputLoop();
    bool quit = false; // raised whenever we're done and the thread should quit

    float pressure; // pressure of the stylus on the tablet; most important member of this class!
};
