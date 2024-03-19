# gameframework2d-MarkCedrickVillanueva

Arcane Golf - A 2d golf styled puzzle game

## Table of Contents

- [Getting Started](#getting-started)

## Getting Started

Welcome to the gameframework2d-MarkCedrickVillanueva project! 
This is the start of Arcane Golf project, a 2d puzzle golf style game in the works.

Deliverables:
- Functioning Entity System
- Fully interact-able environment
- User Interface (HUD, Stats, Messages, menus)
- File read / write access (high score list, saved games, saved songs, etc)
- README for how to play and see all game features (this should be in the git repo)
- Basic Mini Golf Mechanics with a the ball moving and bouncing off of walls and obstacles
- At least 5 puzzle elements to add to the levels
- At least 5 obstacles to add to the levels
- At least (you guessed it) 5 spells to unlock to assist in the completion of the game
- A pro shop / equipment / high score screen



# gameframework2d (GF2D)
a collection of utlitity functions designed to facilitate creating 2D games with SDL2
This project is specifically intended to function as an educational tool for my students taking 2D Game Programming.

FOR FULL FEATURES CHECKOUT THE MASTER BRANCH
Students: Don't do that.  You are not ready.... yet.

The main branch is kept deliberately minimal to allow students to build out systems as they are learning.
Other branches have more complete system: Collisions, Windows, Armatures, Entities, Particles...

# Build Process

Before you can build the example code we are providing for you, you will need to obtain the libraries required
by the source code
 - SDL2
 - SDL2_image
 - SDL2_mixer
 - SDL2_ttf
There are additional sub modules that are needed for this project to work as well, but they can be pulled right from within the project.
Performable from the following steps from the root of the cloned git repository within a terminal. 

Make sure you fetch submodules: `git submodule update --init --recursive`
Go into each submodule's src directory and type:
`make`
`make static`

Once each submodule has been made you can go into the base project src folder anre simply type:
`make`

You should now have a `gf2d` binary within the root of your git repository. Executing this will start your game.

# video overviews and tutorials
Overview: https://www.youtube.com/watch?v=nvVQ_n6ycC4

Linux Setup: https://www.youtube.com/watch?v=0Znnv5C4mCo

Windows Setup: https://www.youtube.com/watch?v=zj_egJ4sw3I

