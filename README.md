# conways-game-of-life
C implementation of Conway's Game of Life

This program requires ncurses to run- to install, in your terminal of choice:


    sudo apt-get install libncurses5-dev
    sudo apt-get install libncursesw5-dev


To compile, navigate to the diriectory the files were downloaded to in your favorite terminal, and run:


    make -f mk
If, when compiling, you get a warning about universal character names not being valid, feel free to ignore. This is a byproduct of working with C and has no effect on running.
To run, type: 


    ./conway < ./example.grid
where 'example' is the name of the .grid file you intend of feeding the program.
  
  
  By default, the program will pause for 2 seconds on the initial layout, run through the specified number of generations, and then paused for 5 seconds on the final generation.
  Additionally, each generation takes 0.625s to elapse.
  
  Pending the implementation of a configuration file, these values are unchanagable unless you edit the source- the positions of which should be fairly evident(as they are commented), but listed here nevertheless-
  lines: 209(time between generations, in microseconds), 361(initial pause, in seconds), and 396(end pause, in seconds).
  
  I hope to implement some kind of config file, but until then, please bear with me.
  
  
  Finally, regarding the layout of input files:
  There are four major parts to an input file for this program.
  The first line should contain a number(ex. 100) indicating the desired number of generations to run the simulation on.
  The second line should contain the height of the field(ex. 20)
  The third line should contain the width of the field(ex. 30)
  The rest of the file should contain a visual representation of the grid, where 0 represents dead cells and 1 represents live cells. For example:
  
  
          11000
          10000
          00100
          01100
          00000
The above sample grid contains a beacon pattern- the 1s are live, and the 0s dead- the sample input file for this would look like:


          20
          5
          5
          11000
          10000
          00100
          01100
          00000  

While this representation is somewhat inconvinient- copy and paste are your friend. This kind of format is simpler to use to design your pattern visually(as opposed to just using coordinates), and makes for simpler handling in the code- it's a win win!

Also please note that if your input file is not formatted in the specidied way, correct behavior(a correct simulation) is not guaranteed.

Included are three sample grids, titled: glider.grid, glider2.grid, and gliderbeacon.grid. Please look at these if the above was confusing.


The final thing to mention is that edges wrap around- so if something goes off screen on the right, it will come back on the left. Please keep this in mind when designing your grid.


Thank you.




--Andrew Braunlich
