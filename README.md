# Sudoku solver project

Will we get to the end of this? Who knows.
EDIT: We did it!

## Compiling instructions

Tentative compilation instructions:
```
bash$ mkdir build
bash$ cd build
bash$ cmake .. -DCMAKE_INSTALL_PREFIX=. 
bash$ make
```

## Run

Once the project has been built, the program `sudoku_solver` should be in the
selected install path (the `build` directory). 
It can be launched with the commmand
```
bash$ sudoku_solver input.txt
```

where `input.txt` is a text file of the format

```
5**67*9**
*4*8*****
8**5**613
*624***7*
1****3*2*
3749*8***
*961*78*2
218**6*45
*5**8**9*
```

where `*` stands for an empty space.
The ouput will be given in the same format.

## Algorithm and Disclaimer

Remember: All is WIP!

The only algorithm that is used now is to propagate all the "certain" 
assumptions, i.e. when a number in a certain position is known all the 
consequences of that are applied and the "search space" is pruned 
accordingly. 

The search tree is represented as a 9x9x9 cube of booleans. When in the 
column (i,j) only one value is `true`, then this information is used to
set to `false` the right elements of the cube, according to the Sudoku
rules.

This is not enough to solve any Puzzle (see, e.g., 
`example_tables/hard.txt'), but slightly more advanced algorithms 
are possible with the current framework.




