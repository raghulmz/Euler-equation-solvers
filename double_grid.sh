#!/bin/bash

mkdir ./Data

g++ -O3 Geometry.cpp Functions.cpp Boundary_Condition.cpp File_Dealing.cpp Tools.cpp double_grid.cpp -o double_grid #&& chmod +x Project

./double_grid
