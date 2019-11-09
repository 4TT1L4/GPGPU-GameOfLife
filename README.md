# GPGPU-GameOfLife
[OpenGL Shading Language](https://en.wikipedia.org/wiki/OpenGL_Shading_Language) implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) as demonstartion of general purpose GPU programming, enabling massively paralel computation of the steps of the simulation on any compatible graphic card.

# Preview

![Animation-Of-The-Simulation](https://github.com/BujakiAttila/GPGPU-GameOfLife/blob/master/doc/simulation.gif?raw=true)

Slowed down, zoomed in:

![Animation-Of-The-Simulation](https://github.com/BujakiAttila/GPGPU-GameOfLife/blob/master/doc/simulation-slow-motion.gif?raw=true)

#  Description for cell colors:

White cells were just born in the current cycle.
Red ones are living.
Blue are dead due to overcrowding,
Green are dead by under-population
