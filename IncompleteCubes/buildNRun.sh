## This simple script basically just does 2 things:
# 1 - Compile and run the C++ file to generate
# the CSV file of edge data
# 2 - Set up the Python virtual environment and run
# the python script that plots the cubes

# C++: Let's copy the same compiler options from Project Euler
WarningFlags="-std=c++14 -Wall -Wextra -Werror -pedantic-errors"

g++ $WarningFlags findCubes.cpp -o findCubes.out

STATUS=$?
if [ $STATUS -eq 0 ]; then
	./findCubes.out
fi

# Python: Set up python venv
python3 -m venv .venv

source .venv/bin/activate

pip install matplotlib numpy PyQt5

# Run python plotting script
python3 graphCubes.py

# Shut down virtual env
deactivate
