Galatea
========

Control MIDI synthesizers using a graphic tablet. A (functional) proof of concept for now.

Building
---------

1. You will need to have the `libudev` and `libinput` development libraries installed, as well as the CMake meta-build system:
```
apt install libudev-dev libinput-dev cmake
```

2. Clone this repository, including the submodule:
```
git clone --recurse-submodules https://github.com/glocq/Galatea
```

3. Get into the repository, create a folder for your build and enter it:
```
cd Galatea
mkdir build
cd build
```

4. "Pre-build" with CMake, then build with :
```
cmake ..
make
```

5. The Galatea executable should now have appeared at `Galatea_artefacts/Standalone/Galatea`.

Using
------

Here is a walkthrough of how I get Galatea working in my setup. It is very detailed and specific to my workflow; you should adapt this advice to yours.
I am planning to make Galatea more configurable and this tutorial more generic.

All software here is free and open source, except for Reaper.

### Routing MIDI to your DAW
0. This assumes you have a digital audio workstation (DAW) such as [Reaper](https://www.reaper.fm/index.php) installed, as well as the [Cadence suite](https://kx.studio/Applications:Cadence).
1. Open Cadence and start the JACK server.
2. Launch your DAW.
3. From Cadence, in the "Tools" tab, launch Catia.
4. Route the output of "Midi Through" to a MIDI input of your DAW.
5. Launch Galatea.
6. In Galatea, click *Options > Audio/MIDI Settings*; select *JACK Audio Connection Kit* as the *Output*, then *Midi Through Port-0* as the *MIDI Output*.

### Playing sound in your DAW
0. This assumes you have the [Surge synthesizer](https://surge-synthesizer.github.io/) installed as a plugin in a format compatible with your DAW (most widespread format is VST3).
1. Create a new track, add the Surge VSTi to it.
2. Arm the track for recording, and in it, select the MIDI input which you connected to Galatea in a previous step.
3. In the Surge graphical interface, find where it says "Bend depth"; under it, choose how many semitones "Down" and "Up" you want the sound to vary. I choose 10 and 10, because my tablet has a 20-square wide grid printed on it.
4. In the routing panel, find "Channel AT" (for "Channel Aftertouch") and click it *twice*. Then drag the parameter whose value you want to depend on pen pressure (a natural choice is Filter 1 cutoff --- make sure that you add a filter for this to have any effect though!).
5. That's it, you should now hear sound upon writing on the tablet with your pen.
