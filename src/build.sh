#!/bin/sh

std="-std=c++17"

CFLAGS=`pkg-config SDL2 --cflags`
LIBS=`pkg-config SDL2_ttf --libs`

MODS="Game.cpp Board.cpp Paddle.cpp Ball.cpp"
COMP="-o2"

set -xe

clang++ $COMP $std $CFLAGS $LIBS $MODS main.cpp -o Pong
