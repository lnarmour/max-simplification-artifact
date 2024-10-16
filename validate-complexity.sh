#!/bin/bash

# This script generates a plot for each input program showing
# the improvement in asymptotic complexity.

BASE_DIR=`dirname $0`
BASE_NAME=`basename $0`

NUM_RUNS=3

cd $BASE_DIR

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


function run_single() {
    binary=$1
    N=$2
    $binary $N | cut -d ' ' -f 4
}

function average_single() {
    binary=$1
    N=$2
    times=`run_single $binary $N`
    for i in $(seq 2 $num_runs)
    do
        times="$times + $(run_single $binary $N)"
    done
    python3 -c "print('{:E}'.format(($times)/$NUM_RUNS))"
}

function collect() {
    system_name=$1
    shift
    # generate the data
    mkdir -p logs
    results_file="logs/${system_name}_results.csv"
    echo '# version, N, execution_time' > $results_file

    for prog in `ls generated/bin/${system_name}_* | grep -v verify`
    do
        for N in $@
        do
            version=`echo $prog | sed 's~.*_\([^_]*\)$~\1~'`
        
            time=`average_single $prog $N`
            echo "$version,$N,$time ($system_name)"
            echo "$version,$N,$time" >> $results_file
        done
    done
}

# collect data
if [[ ! -d logs || -n "$FORCE" ]]; then
    collect prefix_sum $(seq 10000 10000 100000)
    collect prefix_max $(seq 50000 50000 500000)
    collect increasing_max_filter $(seq 50000 50000 500000)
fi

# plot data
python3 lib/plot.py logs/prefix_sum_results.csv prefix_sum 2 1
python3 lib/plot.py logs/prefix_max_results.csv prefix_max 2 1
python3 lib/plot.py logs/increasing_max_filter_results.csv increasing_max_filter 2 1