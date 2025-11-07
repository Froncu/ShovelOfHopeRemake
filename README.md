# Shovel Knight: Shovel of Hope - First Level Remake

This is my first attempt at creating a bigger game: an *almost* complete remake of the first level of [Shovel Knight: Shovel of Hope](https://store.steampowered.com/app/589500/Shovel_Knight_Shovel_of_Hope/), which was the final assignment of the Programming 2 course at [Howest - Digital Arts and Entertainment](https://www.digitalartsandentertainment.be/). The goal was to individually recreate the first level of a 2D game of your choice using the provided [framework](https://github.com/samynk/GameDevEngine2).

## Goal of the project

The assignment's main focus was providing a fun way of utilising the covered basic C++ functionalities by creating a game. The goal was simple: implement as much of the chosen level as possible and make it **work**.

## Changes to my final version

This project was originally finished around June of 2023. All the changes made to the project since submitting for the final can be seen in the commit history of this repository, but the two main things are:

1. Switched from Visual Studio Solutions to CMake

2. Uncommented the code responsible for initialising `SDL_Mixer`

## Build prerequisites

In order to build the project, you'll need:

1. A compiler with support for C++14

2. CMake

3. Internet connection for the initial project generation (`FetchContent`)

At the moment, CMake is throwing some errors at the end of project generation, however the project still builds and runs fine - at least on my machine. This will be looked into later.
