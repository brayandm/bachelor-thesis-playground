# Notes:
- Try to limit the amount of power and resources that a frame can consumed
- Try to limit the ratio of TBS/power or sort by that


# Algorithm:

- Sort frames by random or maybe by (TBS)
- Try to schedule in order
- If some frame consumes more than $p$ power then put it after some frames randomly, maybe with some weighted probability (while more $p$ consumed further will be placed)
- The scheduling of the data frames is greedy, but first try to schedule on shared RBG-Cell, if not possible just use full RBG will all cells, try to only put frames on shared RBG-Cell only if it does not interferes so much
	- Try to schedule first smalls frames on shared RBG-Cell, if not try to create a new one shared RBG-Cell, if it reach power $p$ threshold then just reorder that frame

- Maybe it will be good make this in two step process, first set up shared RBG-Cell, trying to schedule as much small data frames as you can