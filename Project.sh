#!/bin/bash

mkdir ./Data

g++ -O3 Geometry.cpp Functions.cpp Boundary_Condition.cpp File_Dealing.cpp Tools.cpp Main.cpp -o Project && chmod +x Project

./Project
