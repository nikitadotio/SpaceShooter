# MyFirstGame — Space Shooter

## Overview
A 2D space shooter built in C++ using SFML 2.6.1. The player controls a spacecraft at the bottom of the screen and must shoot asteroids that fall from the top. Built as a learning project to practice OOP, inheritance, and game loop fundamentals in C++.

## Tech Stack
- **Language:** C++20
- **Graphics:** SFML 2.6.1
- **Build System:** CMake 3.16+

## Project Structure
```
MyFirstGame/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── assets/
│   ├── textures/
│   ├── fonts/
│   ├── sounds/
│   └── music/
├── include/        ← header files (.h)
├── src/            ← source files (.cpp)
└── build/          ← cmake/make output, gitignored
```

## How to Build
```bash
cd build
cmake ..
make
./game
```

## Architecture
All game objects inherit from a base `Entity` class:
```
Entity          ← base class (position, velocity, update, draw)
├── Player      ← moves left/right via arrow keys
├── Bullet      ← fires upward from player
└── Asteroid    ← spawns at top, moves downward
```

## Basic Version Scope
- Player ship moves left/right along the bottom
- Player shoots bullets upward with spacebar
- Asteroids spawn at top at random positions and speeds, move downward
- Bullet hits asteroid — both disappear
- Game over if asteroid reaches player

## Out of Scope (Basic Version)
- Sprite artwork (using shapes for now)
- Sound
- XP or progression

## TODO
- [ ] Point counter — earn 5 points for every 5 asteroids that fall off screen
- [ ] Game over screen — display when health reaches 0, show final score
- [ ] Score display — render live score on screen using sf::Text + font file
