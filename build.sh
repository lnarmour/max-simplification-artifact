#!/bin/bash

BASE_DIR=`dirname $0`
BASE_NAME=`basename $0`
OUT_DIR=generated

cd $BASE_DIR

function parse_system_name {
  file_name=$1
  cat $file_name | grep affine | head -n1 | sed 's~.*affine \([^ ][^ ]*\) .*~\1~'
}

function simplify() {
    system_name=$1
    target_complexity=$2
    num_simplifications=0
    if [[ -n "$3" ]]; then
        num_simplifications=$3
    fi

    # generate simplifications 
    ./acc -o $OUT_DIR -s \
          --num-simplifications $num_simplifications \
          --try-splitting \
          --target-complexity $target_complexity \
          --data-type long \
          inputs/${system_name}.alpha
    pushd $OUT_DIR
    mkdir -p ${system_name}/baseline
    cp $system_name/$system_name.c ${system_name}/baseline/

    mkdir -p bin

    # build O(N^2) baseline implementation
    make -C $system_name plain
    mv $system_name/$system_name bin/${system_name}_baseline
    rm $system_name/$system_name.c

    # build O(N) simplified implementations
    simp_num=0
    for simplification in $system_name/simplifications/*/$system_name.c
    do
        cp $simplification $system_name/
        make -C $system_name clean
        make -C $system_name plain verify-rand
        mv $system_name/$system_name bin/${system_name}_simplified_v$simp_num
        mv $system_name/$system_name.verify-rand bin/${system_name}_simplified_v$simp_num.verify
        simp_num=$((simp_num+1))
    done
    popd
}

if [[ ! -d $OUT_DIR || -n "$FORCE" ]]; then
    #########################################
    # 1D simplifications                    #
    #########################################

    simplify prefix_sum 1
    simplify prefix_max 1
    simplify increasing_max_filter 1

    #########################################
    # 2D simplifications                    #
    #########################################

    simplify example_3d_sum 2
    simplify example_3d_max 2
    simplify working_example 1 5
    

    # Correctness tests
    echo
    echo "Running simple correctness tests (comparing outputs between input and simplified implementations)"
    num_tests=`ls $OUT_DIR/bin/*.verify | wc -l | sed 's~[^0-9]*\([0-9][0-9]*\)[^0-9]*~\1~'`
    i=1
    for f in $OUT_DIR/bin/*.verify
    do 
        passed=`$f 1103 | grep 'TEST.*PASSED'`
        result='failed, '$f'\n'
        if [[ -n "$passed" ]]; then
            result='passed'
        fi
        printf "Test $i of $num_tests $result \r"
        i=$((i+1))
    done
    echo
fi