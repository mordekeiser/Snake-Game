# Snake-Game
A simple snake game in mac-os using c++ and no external libraries play-able on terminal. Grow in length while avoiding collisions with the walls and itself.

=> Features:
  - Classic Snake Mechanics: Move the snake in four directions, eat food, and avoid collisions.
  - Super Fruit : spawns randomly and provides more points and 3x growth.
  - High Score: Tracks the highest score achieved during gameplay.
  - Simple Menu System: Options to start the game, view the high score, or exit.

=>How to run:

  1)Download the c++ file
  
  2)To compile and run the game, use a C++ compiler
  
  3)Enter the command -g++ -o snek snekgame.cpp
  
                      - ./snek
=>How to Play
1. Run the program.
2. Select an option from the menu:
   - 1: Start Game  
   - 2: View High Score  
   - 3: Exit  
3. Use `W`, `A`, `S`, `D` keys to control the snake.
4. Eat fruits (`F`) to increase your score and length.
5. Super Fruits (`S`) appear randomly and provide extra points.
6. The game ends if you hit the walls or your own tail.

=> The following C++ standard libraries are used:

1)#include  <iostream> :-Used for input/output operations (printing game board, taking user input)

2)#include <unistd.h> :- Provides usleep() function for controlling game speed (Linux/macOS)

3)#include <termios.h> :- Used for handling non-blocking keyboard input without pressing Enter

4)#include <cstdlib> :- Includes rand(), srand() for generating random fruit positions

5)#include <ctime> :- Provides time(0) for seeding rand() to ensure different fruit positions each run

6)#include <fcntl.h> :- Used for setting non-blocking input mode in getInput() function


