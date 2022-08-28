#!/bin/sh

std="-std=c++17"

CFLAGS=`pkg-config SDL2 --cflags`
LIBS=`pkg-config SDL2 --libs`

set -xe

clang++ $std $CFLAGS $LIBS main.cpp -o Pong && ./Pong
