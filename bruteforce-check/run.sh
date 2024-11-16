#! /bin/bash

compiler="g++"
flags="-std=c++14 -Wall -Wextra -O2"
compile="${compiler} ${flags}"
find_different="git diff --no-index ./output.txt ./output_brute.txt"

RED='\033[0;31m'
YEL='\033[1;33m'
NC='\033[0m' # No Color

for i in {1..100}
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

    # clear compiled file
    rm program_gen program program_brute

    # loop number
    printf "\n"
    printf "\n"
    printf "Case: $i\n"

    # compare outputs
    diff=$($find_different)
    if [[ -n $diff ]]; then
        printf "${RED}Input${NC}\n"
        cat input.txt
        printf "\n"
        printf "${YEL}Different${NC}\n"
        $find_different
        break  # Break the loop if there is a difference
    fi
done
