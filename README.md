# Shovel Knight: Shovel of Hope - First Level Remake

This is my first attempt at creating a bigger game: an *almost* complete remake of the first level of [Shovel Knight: Shovel of Hope](https://store.steampowered.com/app/589500/Shovel_Knight_Shovel_of_Hope/), which was the final assignment of the Programming 2 course at [Howest - Digital Arts and Entertainment](https://www.digitalartsandentertainment.be/). The goal was to individually recreate the first level of a 2D game of your choice using the provided [framework](https://github.com/samynk/GameDevEngine2).

![alt text](InGame.png)

## Goal

This assignment focused on applying and solidifying foundational C++ programming skills by developing a fun and playable game level. The objective was to implement as much of the original level's gameplay and feel as possible, resulting in a fully functioning prototype.

## Project Evolution

Originally completed in June 2023, this project marks a significant milestone in my programming journey. All the changes made to the project since submitting for the final can be seen in the commit history of this repository, with the two main things being:
1. Switched from Visual Studio Solutions to a CMake/vcpkg setup
2. Uncommented the code responsible for initialising SDL Mixer

## Dependencies

- [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2) - Core functionality (entry point, system events, input, windowing, etc.)
- [SDL_image](https://github.com/libsdl-org/SDL_image/tree/SDL2) - Image loading support
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf/tree/SDL2) - Font rendering and text support
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/tree/SDL2) - Audio loading and playing support

Those are managed through my custom [vcpkg](https://github.com/microsoft/vcpkg) fork and will be automatically installed during the configuration process.

## Quickstart

### Prerequisites

- C++14 compatible compiler
- CMake 3.15 or higher

### Cloning

Clone the repository **with** the `--recursive` flag. This will cause the vcpkg submodule to also be pulled:

```bash
git clone https://github.com/Froncu/ShovelOfHopeRemake --recursive
```

### Configuring & Building

The project includes CMake presets (`CMakePresets.json`) that configure vcpkg integration automatically. You can configure and build using your preferred IDE or command line.

**Note:** If creating custom configurations, ensure they inherit from the provided `Base`, `DefaultDebug` and/or `DefaultRelease` preset to maintain proper vcpkg integration.

### Usage

Press **I** to bring up the controls pop-up and enjoy the game!