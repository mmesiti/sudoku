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

## Algorithm 

The search tree is represented as a 9x9x9 cube of booleans. The "x" and "y"
directions map to the two axes of the puzzle. The "z" direction is used to
contain the possibilities: the element `(i,j,k)` of the array being `true`
means that the digit `k+1` is a candidate for position `(i,j)`.

If in the column `(i,j, _ )` only one value is `true`, then this 
information is used to set to `false` the right elements of the cube, 
according to the Sudoku rules. Similar considerations apply for x-rows
`(_,j,k)` and y-rows `(i,_,k)`.

### Algorithm 1
This algorithm consists of propagating all the consequences of 
the "certain" information,
i.e. when there is only one possiblity for a number in a certain position
all the consequences of that piece of knowledge are applied and the "search space" is pruned 
accordingly. 
This is not enough to solve all Puzzles (see, e.g., `example_tables/hard.txt'). 

### Algorithm 2

This algorithm adds additional assumptions to what is already known
in order to get to the point where a single digit is possible in any cell.
Of course there are many different ways to do so. It will try first 
to add assumptions to the cases allowing the least amount of mutually 
exclusive assumptions. If it is possible to always find a case where the 
number of mutually esclusive assumptions is 1, this is equivalent to 
Algorithm 1. 
This generates a tree of assumptions, which is explored with multiple
recursion in a depth-first fashion. Once a solution is found or deemed
impossible, the recursion returns.

