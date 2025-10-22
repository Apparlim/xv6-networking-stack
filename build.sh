#!/bin/bash

echo "Building xv6 Networking Stack..."
echo

echo "Compiling kernel modules..."
gcc -Wall -Wextra -std=c99 -O2 -g -c kernel/*.c
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Linking test program..."
gcc -Wall -Wextra -std=c99 -O2 -g -I. test_networking.c kernel/*.o -o test_networking
if [ $? -ne 0 ]; then
    echo "Linking failed!"
    exit 1
fi

echo
echo "Build successful! Running tests..."
echo
./test_networking

echo
echo "Build complete!"
