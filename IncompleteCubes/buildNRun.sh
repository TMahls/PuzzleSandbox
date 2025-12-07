
# Let's copy the same compiler options from Project Euler
WarningFlags="-std=c++14 -Wall -Wextra -Werror -pedantic-errors"

g++ $WarningFlags findCubes.cpp -o findCubes.out

STATUS=$?
if [ $STATUS -eq 0 ]; then
	./findCubes.out
fi

# Set up python venv

# Run python plotting script
python3 -m venv .venv

source .venv/bin/activate

pip install matplotlib numpy PyQt5

python3 graphCubes.py
