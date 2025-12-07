
# Let's copy the same compiler options from Project Euler
WarningFlags="-std=c++14 -Wall -Wextra -Werror -pedantic-errors"

g++ $WarningFlags findCubes.cpp -o findCubes.out

STATUS=$?
if [ $STATUS -eq 0 ]; then
	./findCubes.out
fi
