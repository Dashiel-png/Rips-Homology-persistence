# Rips-Homology-persistence
This is for generating a persistence diagram using .off files and GHUDI in C++
can compile noisy circle generator and has the following flags:
./program numpoints radius noise level
.off file is used for GHUDI persistence

to generate a .off file go to build and do ./circle_generator numpoints radius noise
then do ./main for persistence info

if you want to change main.cpp to alter parameters as you should do so then go to build and do something like cmake .. make