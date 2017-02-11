#!/bin/bash

set -e

echo --------------------------
echo testThreadSafeQueue
./testThreadSafeQueue &
pid=$!
sleep 5
kill $pid
