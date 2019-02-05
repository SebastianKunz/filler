# Filler - AI fights visualized
## Preview
![](https://media.giphy.com/media/PhYmvqUril9qApPDUo/giphy.gif)
## Goal
The Filler project is part of the 42 curriculum. 

## Game Rules
Filler is an algorithmic game which consists in filling a grid of a known size in advance
with pieces of random size and shapes, without the pieces being stacked more than one
square above each other and without them exceeding the grid. If one of these conditions
is not met, the game stops.

more here

## Install - SDL2 SDL2_TTF and SDL2_Image required
### Homebrew
`brew install SDL2 SDL2_ttf SDL2_image`

### Build project
`make`

## Usage

### Run with Visualizer

`./resources/filler_vm -p1 [PLAYER1] -p2 [PLAYER2] -f [MAP] | ./skunz.visualizer`

Example:

`./resources/filler_vm -p1 ./skunz.filler -p2 ./resources/players/grati.filler -f resources/maps/map01 | ./skunz.visualizer`

### Run without Visualizer

`./resources/filler_vm -p1 [PLAYER1] -p2 [PLAYER2] -f [MAP]`

Example:

`./resources/filler_vm -p1 ./skunz.filler -p2 ./resources/players/grati.filler -f resources/maps/map01`


## My Solution
[![rsz-1screen-shot-2019-02-05-at-124412-pm.png](https://i.postimg.cc/J4dhRLWv/rsz-1screen-shot-2019-02-05-at-124412-pm.png)](https://postimg.cc/ZCpmLXnx)

[![rsz-1screen-shot-2019-02-05-at-124422-pm.png](https://i.postimg.cc/HWvmy9P7/rsz-1screen-shot-2019-02-05-at-124422-pm.png)](https://postimg.cc/WtZxRgV2)
