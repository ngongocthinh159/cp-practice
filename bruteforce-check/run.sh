#! /bin/bash

compiler="g++"
flags="-std=c++14 -Wall -Wextra -O2"
compile="${compiler} ${flags}"

for i in {1..2}
do
    # gen input -> input.txt
    $compile ./program_gen.cpp -o ./program_gen
    ./program_gen

    # run optimized program -> output.txt
    $compile ./program.cpp -o ./program
    ./program

    # run brute program -> output_brute.txt
    $compile ./program_brute.cpp -o ./program_brute
    ./program_brute

    # compare outputs
    result=$(git diff --no-index ./output.txt ./output_brute.txt)
    echo result
    # diff ./output.txt ./output_brute.txt
    # comm -23 <(sort ./output.txt) <(sort ./output_brute.txt)
    # sdiff -s ./output.txt ./output_brute.txt

    rm program_gen program program_brute

    echo "$i"
done
