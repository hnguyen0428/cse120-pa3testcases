#!/bin/sh
#
#

make test

tests=(1 2 3 4 5 6 7 8 9 10 11)
for i in "${tests[@]}"
do
  ./runTests $i > "$i.OUTPUT"
done
