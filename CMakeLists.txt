cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(GALATEA VERSION 0.0.1)

option(TRY_USING_LIBINPUT "Try using libinput if on Linux. If this is unchecked, or if not on Linux, or if libinput was not found, Galatea will fall back to using JUCE event detection, which does not seem to detect tablet pen pressure on Linux." TRUE)

add_subdirectory(JUCE)

# This was originally going to be a plugin, so we add the target using `juce_add_plugin`,
# but the only format we build is standalone.
juce_add_plugin(Galatea
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT TRUE
    FORMATS Standalone
    PRODUCT_NAME "Galatea")

# Allow use of `#include <JuceHeader.h>` every time we need to use JUCE symbols,
# instead of wondering about which JUCE module we need every time.
# juce_generate_juce_header(Galatea)

if(TRY_USING_LIBINPUT AND UNIX AND NOT APPLE)
    message("-- Looking for libinput...")
    find_package(Libinput)
    if(Libinput_FOUND)
        message("-- libinput found!")
    else()
        message("-- libinput not found. Relying on JUCE event detection instead.")
    endif()
endif()

if(Libinput_FOUND)
    target_link_libraries(Galatea PRIVATE Libinput::Libinput)
endif()

# Specify which files are source files
target_sources(Galatea
    PRIVATE
        src/ControlSurface.cpp
        src/SettingsWindow.cpp
        src/MidiSender.cpp
        src/MainGUI.cpp
        src/Processor.cpp)

if(Libinput_FOUND)
    target_sources(Galatea PRIVATE src/LibinputManager.cpp)
endif()

# Preprocessor definitions
target_compile_definitions(Galatea
    PUBLIC
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

if(Libinput_FOUND)
    target_compile_definitions(Galatea PUBLIC LIBINPUT)
endif()

target_link_libraries(Galatea
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

if(Libinput_FOUND)
    target_link_libraries(Galatea PRIVATE udev)
endif()
