# ☕ CoffeeInvaders

> “When the aliens attack, make sure you have coffee.”  

CoffeeInvaders is an indie retro-style arcade game built around one mission: **break the blocks, collect the coffee, and survive through the levels.**  
It mixes nostalgia from classic brick-breaker / invader games with a unique twist — every block hides drops of precious coffee. The more you smash, the more you sip!  

---

## Table of Contents

- [☕ CoffeeInvaders](#-coffeeinvaders)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Features](#features)
  - [Gameplay](#gameplay)
  - [Installation \& Build](#installation--build)
  - [Dependencies \& Tech Stack](#dependencies--tech-stack)


---

## About

CoffeeInvaders combines the feel of old-school block breakers with a caffeine-fueled theme.  
Each level challenges you with a grid of blocks. Destroy them, dodge obstacles, and collect the coffee that pours out. Progressing through levels gets tougher, faster, and more rewarding.  

The goal: **clear all blocks in a level, collect as much coffee as possible, and move on to the next challenge.**  

---

## Features

- Level-based progression with increasing difficulty  
- Blocks that drop **coffee pickups** when destroyed  
- Smooth 2D retro-style graphics and animations  
- Power-ups hidden inside blocks  
- Score system based on speed, precision, and coffee collected  w
- Catchy and energetic sound effects  

---

## Gameplay

- **Game**: ./game

- **Levels**: Each stage consists of a number of blocks that must be destroyed.  
- **Blocks**: When hit, blocks may release **coffee drops** that can be collected for score and bonuses.  
- **Objective**: Clear all blocks on the screen to complete the level.  
- **Power-ups**: Some blocks may contain boosts like extra speed, extra lives, or stronger shots.  
- **Lives**: Losing all lives ends the game — but collected coffee might grant you extra chances.  

**Controls** *(example, adjust to your actual implementation)*:  
- Move: WASD / Arrow Keys Rotate  
- Shoot / Action: Spacebar  

---

## Installation & Build

1. Make sure you have a C/C++ compiler (C99/C11 or higher).  
2. Install any required libraries (e.g., SDL, SFML, OpenGL, etc.).  
3. Clone the repository:  

   ```bash
   git clone https://github.com/cafeluta/CoffeeInvaders.git
   cd CoffeeInvaders

## Project Structure
```
.
├── Makefile
├── README.md
├── assets
├── build
├── cfi.cpp
├── game
├── include
│   ├── Engine
│   ├── Game
│   └── config.h
├── levels
│   ├── one.lvl
│   └── two.lvl
├── lib
│   ├── dlg
│   ├── freetype
│   ├── ft2build.h
│   ├── glad
│   ├── linmath.h
│   ├── stb_easy_font.h
│   └── stb_image.h
├── shaders
│   ├── shader.fs
│   ├── shader.vs
│   ├── text.fs
│   └── text.vs
└── src
    ├── Engine
    ├── Game
    └── stb_image.cpp
```
## Dependencies & Tech Stack

- **Language**: C / C++ (C11 recommended)
- **Graphics**: GLFW 3.x (for window creation and input handling)
- **Rendering**: OpenGL (3.x or higher)
- **Build system**: Makefile (or CMake if preferred)
- **Other libraries**: 
  - `libglfw3` (runtime library for GLFW)
  - `libglfw3-dev` (headers and development files for compiling)
- **Supported OS**: Linux, (Windows/macOS if you provide builds)