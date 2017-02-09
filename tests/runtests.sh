#!/bin/bash

echo --------------------------
echo testThreadedQueue
./testThreadedQueue &
pid=$!
sleep 5
kill $pid
