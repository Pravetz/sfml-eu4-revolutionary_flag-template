#!/bin/sh

PROGRAM="eu4rvf"
SRC="main.cpp src/color_parser.cpp src/settings_parser.cpp src/readfile.cpp"
INCLUDES="-I include"
LINKS="-lsfml-window -lsfml-graphics -lsfml-system"
OPTIMIZATION="-O3"
FLAGS="-Wall"

g++ -o $PROGRAM $SRC $INCLUDES $LINKS $OPTIMIZATION $FLAGS

exit 0
