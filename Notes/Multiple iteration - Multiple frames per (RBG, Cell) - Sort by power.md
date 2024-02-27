# Notes
- Make multiple iterations
- Order frames by power in each iteration
- Try to schedule online going through TTIs
- At each TTIs go in frames order, try to schedule with limited power (ex. 1)
- When trying to schedule another frame and share the same (RBG, Cell) then increase the power of previous frames to compensate the loss of data sent, so in each step we keep the data transmission, utilizing power to compensate
- Another stuff we can try is going instead of TTIs, try to iterates across data frames, and maybe this will be better, because we can select greedy the best initial SINR