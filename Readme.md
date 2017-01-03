# Sudoku
## Brandon Knieriem

### Description
This is my term project for OOP at UNH. I'm a pretty average C++ programmer and this is an advanced course so I will be tackling
new concepts; some of which may seem counter intuitive to a standard program for the sake of learning. See the documentation folder for more about each assignment.

### DONE(?)
## Class Assignments
- State
- Square
- Board

## Functionality
- Git source control. This is a larger project and I needed to get more comfortable with git so I don't trip over myself.
- State Unit Test
- Square Unit Test
- Board Unit Test
- Fixed Square toggle. Was the square read from a file? Can't be modified! No? Modifiable.

### TODO

## Class Assignments
- Cluster
- Game
- Exceptions
- Diagonal
- Interface
- Undo
- Restore
- Details & Documents

## Functionality
- State data member visibility once testing is complete. Public should be protected?
- Modifying the possibilities list (bit shifting/toggling) and the possibilities count.
- Constructing each cluster to include an appropriate amount of Squares. How do you know which squares are to be selected for each? How do they interact?

### Questions

- I'm struggling with bit shifting the possibilities list and am unsure why we need a possibilities count given the list. Is it because the user will be able to see the count, but not the list?
- Cluster: How do you know which squares to select? How do they interact? I'm having trouble visualizing this. The documentation says we need 27 clusters. Does that mean we section off 27 Squares and 'build' a cluster around them?