# General Purpose GPU Proframming
# Conway's Game of Life
[OpenGL Shading Language](https://en.wikipedia.org/wiki/OpenGL_Shading_Language) implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) as demonstartion of general purpose GPU programming, enabling massively paralel computation of the steps of the simulation on any compatible graphic card.

The Game of Life, also known simply as "Life", is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.

# Preview of the evolution on full speed

The simulation of the evolution of the cells is executec on full spped by default. On my configuration this means the execution of the simulation for more than 700 steps per second:

![Animation-Of-The-Simulation](https://github.com/BujakiAttila/GPGPU-GameOfLife/blob/master/doc/simulation.gif?raw=true)

# Preview of the evolution on reduced speed, zoomed in

On order to make the evolution of the cell configuration more visible and followable, the player may zoom in and slow down the speed on the simulation:

![Animation-Of-The-Simulation](https://github.com/BujakiAttila/GPGPU-GameOfLife/blob/master/doc/simulation-slow-motion.gif?raw=true)

# Preview of the interactive mode

The player may create cells be clicking on the screen, where the new cell should be created:

![Animation-Of-The-Simulation](https://github.com/BujakiAttila/GPGPU-GameOfLife/blob/master/doc/simulation-slow-motion-interactive.gif?raw=true)

#  Description for cell colors:

White cells were just born in the current cycle.
Red ones are living.
Blue are dead due to overcrowding,
Green are dead by under-population
