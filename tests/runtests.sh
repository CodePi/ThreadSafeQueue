#!/bin/bash

set -e

echo --------------------------
echo testThreadSafeQueue
timeout 3 ./testThreadSafeQueue
echo --------------------------
echo testThreadSafeQueue2
timeout 3 ./testThreadSafeQueue2
