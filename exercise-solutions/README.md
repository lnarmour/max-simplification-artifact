# Exercise solutions

This directory contains C code with the solutions to the exercises given in the paper.
Each source file has two functions:
* `r0`: computes the input reduction as given in the paper
* `r1`: computes the simplified version with reduced asymptotic complexity

To compile the files, simply run `make`.
Then you can run each program specifying the problem size as the first parameter (N):
```
$ ./ex3 
usage: ./ex3 N [seed]

$ ./ex3 100
(seed=0)
N = 100
count0 = 4421275
count1 = 69408
errors = 0
```
In the output, `count0` displays the number of operations performed by the input reduction (from function `r0`), and `count1` shows the same for the simplified version (from function `r1`).

The performance improvement of each can be seen below:

![alt text](https://github.com/lnarmour/max-simplification-artifact/blob/main/exercise-solutions/plot.png?raw=true)

This plot is the plot that appears in Figure 17 of the paper, and can be regenerated with the provided script:
```
./scripts/gen-plot.sh
```
