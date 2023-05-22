Galatea (work in progress)
===========================

**Not functional yet!**

Galatea is a VST3 plugin which allows you to turn your graphic tablet into a MIDI controller.

As of now, it is only available on Linux and uses the [libinput](https://wayland.freedesktop.org/libinput/doc/latest/index.html) library.

Building
---------

0. You'll need to install the `libinput` development library. Depending on your package manager, installing the library will probably look like running a command such as
```
apt install libinput-dev
```
You will also need a recent enough version of CMake
```
apt install cmake
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

5. Somewhere in the `build` folder (probably inside a folder named `Galatea_artefacts`), a folder names `Galatea.vst3` should have appeared. Copy the whole folder in one of the preferred VST3 locations.

6. Open your DAW, make sure it scans the folder where you copied `Galatea.vst3`. You should now be able to add Galatea to a track in the DAW.

