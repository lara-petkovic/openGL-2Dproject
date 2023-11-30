# Air defense game

## Overview
This project is a simple air defense game in OpenGL that involves defending the city of Novi Sad from enemy helicopters. The player controls a drone and must destroy incoming enemy helicopters.

## Prerequisites
Make sure you have the following NuGet packages installed before running the project:

- glew-2.2.0
- glfw
- glm

## Controls
- **Arrow Keys:** Move the drone
- **Space Key:** Activate the dron or reset its position
- **X Key:** Destroy the drone (limited number of uses)
- **1 Key:** Hide the map
- **2 Key:** Unhide the map
- **Esc Key:** Escape

## How to Play
1. Launch the game and hit the Space key to activate the drone.
2. Use arrow keys to move the drone.
3. Press the space key to reset the drone position if needed.
4. Use the X key to destroy the drone (limited uses).
5. Defend the city by destroying incoming enemy helicopters.
6. The game ends when all enemy helicopters are destroyed or the player runs out of drone lives.

## Shader Files
The project uses vertex and fragment shader files for rendering. Make sure these files are present and correctly written:

- `texture.vert`
- `texture.frag`
- `base.vert`
- `base.frag`
- `dron.vert`
- `dron.frag`

## Additional Notes
- The game includes a map texture of Novi Sad, loaded from the file `res/novi-sad.png`.
- The number of remaining drones is displayed using green indicators in the right window corner.
- As the helicopters draw closer to the city center, their pulsations intensify progressively.

## Acknowledgments
- This project uses the [STB Image](https://github.com/nothings/stb) library for image loading.
- The game window is created using GLFW, and GLEW is used for OpenGL extensions.
