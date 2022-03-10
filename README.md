# Cluster
## The game made by Clusterfuck
@jaberkro, @tbouma, @okruitho and @pde-bakk.
###### Every team has built a clusterfuck of a codebase, we are the only ones who actually own up to it!

### Playing
Start playing by running `./cluster`.<br>
If you want to play with 1 or 2 bots, please run:<br>
`./cluster [bot1_pathname] [bot2_pathname]`.<br>
To change the grid size (default is 5), add the flag `--size=X`.<br>
To change the winning condition (default is connect 4), add the flag `--connect=X`.<br>
Example: `./cluster --size=7`.<br>

### Compiling
Compile the game by running `make`.<br>
List of compilation options:
```shell script
VANILLA=1 # Turns 'blocked tiles' mode off 
TIME_OUT=t # t is the time out in milliseconds
ANIMATION=0 # Turns the animation off
ANIMATION_USLEEP=t # Sets the delay between printing states in milliseconds
LEAKS=1 # Abba thinks we segfault, let's help him rid this illusion!
```
Compile our standard bots by running `make bot`.<br>

Happy playing!
