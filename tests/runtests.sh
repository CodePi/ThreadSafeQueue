#!/bin/bash

set -e

echo --------------------------
echo test_move
./test_move

TARGETS="testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack"

for TEST in $TARGETS
do
    echo --------------------------
    echo $TEST
    ./$TEST &
    pid=$!
    disown
    sleep 3
    kill $pid
done
