# ☕ CoffeeInvaders

> “When the aliens attack, make sure you have coffee.”  

CoffeeInvaders is an indie retro-style arcade game built around one mission: **break the blocks, collect the coffee, and survive through the levels.**  
It mixes nostalgia from classic brick-breaker / invader games with a unique twist — every block hides drops of precious coffee. The more you smash, the more you sip!  

---

## Table of Contents

1. [About](#about)  
2. [Features](#features)  
3. [Gameplay](#gameplay)  
4. [Installation & Build](#installation--build)  
5. [Project Structure](#project-structure)  
6. [Contributing](#contributing)  
7. [Dependencies & Tech Stack](#dependencies--tech-stack)  
8. [Roadmap](#roadmap)  
9. [License](#license)  
10. [Credits](#credits)  

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
- Score system based on speed, precision, and coffee collected  
- Catchy and energetic sound effects  

---

## Gameplay

- **Levels**: Each stage consists of a number of blocks that must be destroyed.  
- **Blocks**: When hit, blocks may release **coffee drops** that can be collected for score and bonuses.  
- **Objective**: Clear all blocks on the screen to complete the level.  
- **Power-ups**: Some blocks may contain boosts like extra speed, extra lives, or stronger shots.  
- **Lives**: Losing all lives ends the game — but collected coffee might grant you extra chances.  

**Controls** *(example, adjust to your actual implementation)*:  
- Move: Arrow keys / WASD  
- Shoot / Action: Spacebar  

---

## Installation & Build

1. Make sure you have a C/C++ compiler (C99/C11 or higher).  
2. Install any required libraries (e.g., SDL, SFML, OpenGL, etc.).  
3. Clone the repository:  

   ```bash
   git clone https://github.com/cafeluta/CoffeeInvaders.git
   cd CoffeeInvaders
