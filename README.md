# Maximal Simplification of Polyhedral Reductions

This directory contains a jupyter notebook with illustrations of the types of splits that can occur with 3D simplicial domains.
These are intended to help the reader visualize strong boundary and strong invariant cuts through (d-2)-faces (i.e., 1D edges in 3D) as discussed in Section 4 of the paper.
All that is required to use this is a linux machine with python3 (version 3.6).

A static version of this notebook can be viewed on GitHub at the following link:  
https://github.com/lnarmour/max-simplification-artifact/blob/toplas-submission/splitting-3D.ipynb

This README can be also be viewed on GitHub at the following link:  
https://github.com/lnarmour/max-simplification-artifact/tree/toplas-submission

## Set up python environment

First, verify that you are using python version 3.6.x,
```
$ python3 --version
Python 3.6.8
```
Note the `$` is the shell prompt and is not part of the command.

Create a python3 virtual environment,
```
$ python3 -mvenv virtual-islpy
```
Then source the environment and install the dependencies,
```
$ source virtual-islpy/bin/activate
(virtual-islpy) $ pip install --upgrade pip
(virtual-islpy) $ pip install -r requirements.txt
```
Note that the shell prompt changes to ` (virtual-islpy) $` after sourcing the environment.

## Run the notebook

From the sourced environment, run jupyter notebook from the repo root directory
```
(virtual-islpy) $ jupyter notebook
```

This will launch the notebook web interface in a new tab in your default web browser.
Then do the following:

1. click the `splitting-3D.ipynb` file to open the notebook
2. click Kernel > Restart & Run All > confirm the dialogue, Restart and Run All Cells

This will regenerate the domain plot objects.
The plots can be dragged and panned to better visualize the domains.

## Exercise Solutions

Complete solutions to the exercises given in the paper can be found under the `exercise-solutions` directory.
Each source file contains a function `r0` that executes the original naive reduction and another function `r1` with the corresponding simplified version.
The resulting number of reduction operations are printed for each to illustrate the complexity improvement.
Simple error checking between the original reduction and simplified versions are carried out as sanity checks.

## Acknowledgements

The code under the `islplot` directory comes from:  
https://github.com/tobiasgrosser/islplot
