# Sudoku
## Brandon Knieriem

### Description
This is my term project for OOP at UNH. I'm a pretty average C++ programmer and this is an advanced course so I will be tackling
new concepts. See the documentation folder for more about each assignment.

### DONE
## Homework Assignments
- State
- Square
- Board
- Cluster?

## Functionality
- Git source control.
- State Unit Test
- Square Unit Test
- Board Unit Test with Cluster functionality.
- Fixed Square toggle. Was the square read from a file? Can't be modified! No? Modifiable.
- Possibilities list is based on a short integer with bit ops to toggle on/off possibilities. Ex. If '3' is on/1 it can still be written.
- Cluster construction. Finds appropriate Squares, creates a Cluster, let's each Square know what Cluster it's a part of.

### TODO

## Homework Assignments
- Game
- Exceptions
- Diagonal
- Interface
- Undo
- Restore
- Details & Documents

## Functionality
- shoop(): Toggling possibilities for each Square in the Cluster based on changes to any given Square.

### Questions
- I'm having trouble implementing shoop(). I probably just need to think about it for awhile.
- I'm having trouble printing Cluster participation. I can't use the existing print functions because they come online and may be used before the clusters are created. I know the relationships exist but there isn't an obvious, printable way to demonstrate this.
