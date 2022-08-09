# Pong Clone Ray Lib

A pong clone made in RayLib to learn the library.

## Build Instructions

### Requirements

* CMake 3.23 or newer
* A C++ Compiler such as Visual Studio on Windows
* On Linux you need: libx11-dev, libxrandr-dev, libxinerama-dev, libxcursor-dev, libxi-dev, libgl1-mesa-dev

### Instructions

```bash
git clone https://github.com/HumanGamer/PongCloneRayLib
cd PongCloneRayLib
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

The output file should be in the game folder.