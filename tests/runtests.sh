#!/bin/bash

set -e

echo --------------------------
echo testThreadSafeQueue
./testThreadSafeQueue &
pid=$!
disown
sleep 3
kill $pid
echo --------------------------
echo testThreadSafeQueue2
./testThreadSafeQueue2 &
pid=$!
disown
sleep 3
kill $pid
