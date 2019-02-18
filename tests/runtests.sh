#!/bin/bash

set -e

TARGETS="test_move testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack"

for TEST in $TARGETS
do
    echo --------------------------
    echo $TEST
    ./$TEST
done
