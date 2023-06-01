cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(GALATEA VERSION 0.0.1)

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
juce_generate_juce_header(Galatea)

# Specify which files are source files
target_sources(Galatea
    PRIVATE
        src/ControlSurface.cpp
        src/PluginEditor.cpp
        src/PluginProcessor.cpp)

# Preprocessor definitions
target_compile_definitions(Galatea
    PUBLIC
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(Galatea
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
