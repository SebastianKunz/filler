# Filler - AI Fights Visualized
## Preview
![](https://media.giphy.com/media/PhYmvqUril9qApPDUo/giphy.gif)
## Goal
The Filler project is part of the 42 curriculum. It's part of the algorithm branch and teached me:
- pathfinding
- reading output of a ruby script
- Visualization with SDL2 and C++

## Game Rules
Filler is an algorithmic game which consists in filling a grid of a known size in advance
with pieces of random size and shapes, without the pieces being stacked more than one
square above each other and without them exceeding the grid. If one of these conditions
is not met, the game stops.

## Install - SDL2 SDL2_TTF and SDL2_Image required
### Homebrew
`brew install SDL2 SDL2_ttf SDL2_image`

### Build project
`make`

## Usage

### Run with Visualizer

`./resources/filler_vm -p1 [PLAYER1] -p2 [PLAYER2] -f [MAP] | ./skunz.visualizer`

Example:

`./resources/filler_vm -p1 ./skunz.filler -p2 ./resources/players/carli.filler -f resources/maps/map01 | ./skunz.visualizer`

### Run without Visualizer

`./resources/filler_vm -p1 [PLAYER1] -p2 [PLAYER2] -f [MAP]`

Example:

`./resources/filler_vm -p1 ./skunz.filler -p2 ./resources/players/carli.filler -f resources/maps/map01`


## My Solution
Generate a heat map. Gives each cell a score by its distance to the enemy.

[![](https://i.postimg.cc/J4dhRLWv/rsz-1screen-shot-2019-02-05-at-124412-pm.png)](https://postimg.cc/ZCpmLXnx)

Pick the position with the smallest score (the closest to the enemy)

[![](https://i.postimg.cc/TwZL95RV/rsz-1screen-shot-2019-02-05-at-23112-pm.png)](https://postimg.cc/S2fxQsYR)
