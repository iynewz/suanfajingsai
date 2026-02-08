#!/bin/bash

set -e   # 出错就停

echo "Running O(n^3)..."
./bench n3 > on3.csv

echo "Running O(n^2)..."
./bench n2 > on2.csv

echo "Running O(n)..."
./bench n1 > on1.csv

echo "Done."
