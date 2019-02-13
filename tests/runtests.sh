#!/bin/bash

set -e

TARGETS="test_move testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack"

TAG="$1"

for TEST in $TARGETS
do
    echo --------------------------
    echo $TAG$TEST
    ./$TAG$TEST
done
