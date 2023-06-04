# gameboy

A Gameboy DMG emulator written in C++.
</br>
</br>

<p align="center">
  <img src="https://github.com/siddha20/gameboy/blob/main/docs/gifs/demo.gif" />
</p>

## Usage
Run the emulator on the command line: 

`gameboy <path to game rom>`

## Dependecies
ImGui: https://github.com/ocornut/imgui \
SDL2: https://github.com/libsdl-org/SDL/releases/tag/release-2.26.5

In order to build the project, create a `lib` directory in the project root. Then download ImGui from the Github link above and place it in the `lib` folder. 
For MSVC users only, place the SDL2 library folders into the `lib` and name it SDL2. For Unix and Apple users, CMake should automatically find the SDL library.

## Building
Create a build directory and use cmake to build the project.

```
mkdir build
cd build
cmake ..
```

## To-Do List
- Currently, there is no memory bank controller implemented, so only 32KB ROMs are supported. I plan to implement MBC1 at the very least.
- Improve the cycle accuracy of the CPU. Not really needed, but is something to do.
