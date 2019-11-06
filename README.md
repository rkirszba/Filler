# Filler
42 project Filler

## Description
Filler is a game where two players fight each other, trying to collect as many points as possible by placing the highest number of pieces on the game board.
At the beginning of each turn each player receive a game piece that he has to put on the board.
To be able to place a piece on the board, it is mandatory that one, and only one cell of the shape overs the cell of a shape placed previously.

## Solution
My program tries to surround its opponent's positions, using a heatmap.

<img src=https://github.com/rkirszba/Filler/blob/master/media/Game.gif>

## Installation
Clone the repository and launch the following command :
```make && make -C visualizer```

## Run

### Without visualizer
```resources/filler_vm -f path -p1 path -p2 path```

### With visualizer
```resources/filler_vm -f path -p1 path -p2 path | visualizer/visu```

### Visualizer features
- possibility to see the previous / following turn
- accelerate / decelerate
- start / stop

<img src=https://github.com/rkirszba/Filler/blob/master/media/Options.gif>
