### Summary
A visualizer which can use both [simulated annealing](https://en.wikipedia.org/wiki/Simulated_annealing) and [2-opt](https://en.wikipedia.org/wiki/2-opt) to find a good solution to the TSP problem. The program can support running simulated annealing or 2-opt individually, or running them consecutively. For simulated annealing, a red bar at the bottom of the screen represents temperature. 

As a note: if you're impatient, 2opt performs much faster than SA! Try `NUM_CITIES` = 10,000 for some neat graphics.

### Demo (1000 cities, SA + 2opt)
<a href="http://www.youtube.com/watch?feature=player_embedded&v=W-aAjd8_bUc
" target="_blank"><img src="http://img.youtube.com/vi/W-aAjd8_bUc/0.jpg" 
alt="Traveling Salesman (1000 Cities): Simulated Annealing + 2-opt " width="500" height="300" border="10" /></a>

### Customizable options under `defs.h`  
`NUM_CITIES`: Number of cities  

`COOL_RATE`: Cooling rate for simulated annealing  
`TEMP`: Starting temperature for simulated annealing  

`SA`: Whether or not to use simulated annealing to solve   
`twOPT`: Whether or not to use 2-opt to solve  

`ANIMATED`: Whether or not to animated the solving process, or display to solution when found  
`SHOW_2OPT_STEPS`: Whether or not to show which two links were swapped  
`DELAY_2OPT_MS`: Millisecond delay to make it easier to follow 2opt swaps  
  


Requires SDL2 for graphics. I included all the necessary files along with the .exe to avoid the hassle of installing SDL.
