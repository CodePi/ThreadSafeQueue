#!/bin/bash

set -e

echo --------------------------
echo testThreadSafeQueue
./testThreadSafeQueue &
pid=$!
sleep 3
kill $pid
echo --------------------------
echo testThreadSafeQueue2
./testThreadSafeQueue2 &
pid=$!
sleep 3
kill $pid
