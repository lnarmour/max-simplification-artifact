# Manual simplification of the 4d example

The source file has two functions:
* `r0`: computes the input reduction as given in the paper
* `r1`: computes the simplified version with reduced asymptotic complexity

## Compile and run

To compile the files, simply run `make`.
Then you can run each program specifying the problem size as the first parameter (N):
```
$ ./example_4d
usage: ./example_4d N [seed]

$ ./example_4d 100
(seed=0)
N = 100
count0 = 4421275
count1 = 69408
errors = 0

$ ./example_4d 200
(seed=0)
N = 200
count0 = 68685050
count1 = 278041
errors = 0
```
In the output, `count0` displays the number of operations performed by the input reduction (from function `r0`), and `count1` shows the same for the simplified version (from function `r1`).

## Note on asymptotic complexity

The defining characteristic of a linear complexity program is that the execution time scales linearly with the size of the input. Therefore doubling the size of the input should incur roughly twice as many operations. For a program with $O(N^4)$ complexity, doubling the size of the input should incur roughly 16x as many operations ($2^4 = 16$). 

We can conclude that `r0` is quartic because:
```
68685050 / 4421275 = 15.5351 ~= 16x
```
And similary, `r1` is quadratic because:
```
278041 / 69408 = 4.0058 ~= 4x
```