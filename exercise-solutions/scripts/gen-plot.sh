#!/bin/bash

# This script generates a plot for each exercise solution showing
# the improvement in asymptotic complexity.

# Attempts to check that python3 is installed
which python3 > /dev/null 2>&1
if [[ $? != 0 ]]; then
  echo "error: python3 does not seem to be installed, exiting"
  exit 1
fi

# Attempts to check that matplotlib is installed
python3 -mmatplotlib.pyplot > /dev/null 2>&1
if [[ $? != 0 ]]; then
  echo "error: python's matplotlib does not seem to be installed, exiting"
  exit 1
fi

# Attempts to check that numpy is installed
python3 -mnumpy.version > /dev/null 2>&1
if [[ $? != 0 ]]; then
  echo "error: python's numpy does not seem to be installed, exiting"
  exit 1
fi

# build the programs
make

# generate the data

results_file=results.csv
echo '# exercise_num, N, num_ops_input, num_ops_simplified' > $results_file

for ex_num in 1 2
do
  echo running exercise $ex_num
  for N in 10 30 100 300 1000 3000 10000
  do 
    result=`./ex$ex_num $N`
    num_ops_input=`echo $result | cut -d' ' -f7`
    num_ops_simplified=`echo $result | cut -d' ' -f10`
    echo "$ex_num,$N,$num_ops_input,$num_ops_simplified" >> $results_file
  done
done

echo running exercise 3
for N in 10 30 50 100 130 300 500 1000
do
  result=`./ex3 $N`
  num_ops_input=`echo $result | cut -d' ' -f7`
  num_ops_simplified=`echo $result | cut -d' ' -f10`
  echo "3,$N,$num_ops_input,$num_ops_simplified" >> $results_file
done


# generate the plots
echo generating plot
python3 scripts/plot.py $results_file
rm -f $results_file

if [[ -f plot.png ]]; then
    echo 'created plot.png'
fi
