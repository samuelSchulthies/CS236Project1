#!/bin/bash

# script for project 1 example tests

program="project1"
numbers="10 11 12 13 14 15 16 17 61 62"
testdir="project1-tests"

g++ -Wall -Werror -std=c++17 -g *.cpp -o $program

for number in $numbers ; do
 
    echo "Running input" $number

    inputfile=$testdir/in$number.txt
    answerfile=$testdir/out$number.txt
    outputfile=actual$number.txt

    ./$program $inputfile > $outputfile

    diff $answerfile $outputfile || echo "diff failed on test" $number

    rm $outputfile

done

rm $program

