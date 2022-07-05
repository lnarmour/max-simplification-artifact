# Maximal Simplification of Polyhedral Reductions

This directory contains a jupyter notebook with illustrations of the types of splits that can occur with 3D simplicial domains.
These are intended to complement the explanations of the 3D exercises in the paper and help the reader visualize strong boundary and strong invariant cuts through (d-2)-faces (i.e., 1D edges in 3D).

## Set up python environment

First create a python3 virtual environment,
```
$ python3 -mvenv virtual-islpy
```
Note the `$` is the shell prompt and is not part of the command.

Then source the environment and install the dependencies,
```
$ source virtual-islpy/bin/activate
(virtual-islpy) $ pip install -r requirements.txt
```
Note that the shell prompt changes to ` (virtual-islpy) $` after sourcing the environment.

## Run the notebook

From the sourced environment, run jupyter notebook from the repo root directory
```
(virtual-islpy) $ jupyter notebook
```

## acknowledgements

The code under the `islplot` directory comes from:  
https://github.com/tobiasgrosser/islplot
