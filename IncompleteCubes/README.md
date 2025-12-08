# Incomplete Open Cubes

![Incomplete cube plots](CubePlot.png)

## Background

This was inspired by [this 3Blue1Brown video](https://www.youtube.com/watch?v=_BrFKp-U8GI).

Admittedly, I did not watch the whole video but just seeing the problem setup inspired me to pursue this. 

The problem setup is as follows:

How many incomplete open cubes are there?

An incomplete cube has the following properties:

- Connected (no floating edges or points)
- 3-dimensional
- Rotationally unique

In 1974, Sol LeWitt created an art piece representing all of the open cubes -- "variations of incomplete open cubes"

In the video it's mentioned that he manually had to draw out all 122 of the incomplete cubes. That's a lot of work!
Being the lazy bugger that I am, I immediately thought it'd be neat to programatically generate these open cubes.
Surely it's possible, but how would it even be done?

## Method for finding cubes

A method for finding these cubes is proposed below. Now, I've done enough Project Euler problems to know
that there's probably a faster, better method for finding these. But-- sometimes you just want something
that works reasonably quickly! And unlike a tricky PE problem, the scale we're dealing with here turns out to
not be too large-- brute force is a reasonable way to approach this.

### How to encode the cubes

A cube has 6 faces, 8 vertexes, and 12 edges. We should express the incomplete cubes in terms of edges, because if
we do vertexes there are possible ways we can miss. For example consider the following cube:
```
  O---X
O---X
| O-|-X
X---X
```
Let's say the 'X' vertexes are in our set. There's multiple incomplete cubes we can get from this. We can 
fully connect all the vertexes, or we can remove one of the edges between the 4 vertexes on the right face. 

A bit hard to convey in ASCII but overall-- it's more thorough to map our edges, and have each incomplete
cube be an array of edges (1-12). 

Additionally, we know we'll have between 3 and 11 edges. 12 would be complete, and 2 or 1 connected edges 
can't make a 3-D shape.

### Edge numbering

Let's number the edges like so (this is purely arbitrary):
```
   O----12-----O
  9|         11|
 / 8         / 7
O----10-----O  |
|  |        |  |
5  O----4---6--O
| 1         | 3
|/          |/
O-----2-----O 
```

### How many possible edge sets?

Well, for a set of N edges there are 12 choose N (12_C_N) possible combos. This gives us:

| N | # of sets |
|--:|----------:|
| 3 |    220    |
| 4 |    495    |
| 5 |    792    |
| 6 |    924    |
| 7 |    792    |
| 8 |    495    |
| 9 |    220    |
|10 |     66    |
|11 |     12    |
|Tot|   4016    |

Now, many of these will not satisfy our 3 rules (connected, 3D, rotationally unique). 
We know intuitively that for N=11, all of the 12 possible sets (removing a different edge)
are rotationally identical. So there's only one set there. But 4016 is low enough that we could
'brute force' generate all the sets and then just check our 3 rules on it. 

### Rule 1 - Connected

To be connected means that we can get to every edge in our set starting from any edge and going only
through neighboring edges in our set. Note that each edge has 4 neighbors.

Ex: 1 is connected to 2, 4, 5, and 8. 

So the process can be as follows:

1. Start with the first edge in the set
2. Identify all neighboring edges in our set and cross them off our list
3. For all of those neighbors, identify _their_ neighbors in our set and cross them off.
4. If we have crossed off all the edges in our set, congrats! We're fully connected
5. If there are no more unique neighbor edges left to cross off, but we still haven't gotten
all the edges in our set-- bad news. We ain't connected.

From Step (3) one can see that this is a recursive process. 

### Rule 2 - 3D

This one's pretty straightforward. From our diagram above, our 6 faces are comprised of these edge sets:

```
[1, 2, 3, 4]
[1, 5, 8, 9]
[2, 5, 6, 10]
[3, 6, 7, 11]
[4, 7, 8, 12]
[9, 10, 11, 12]
```

For our edge set to be 3D it has to span multiple faces, meaning it can't be a subset of any of the sets above.

From this we can take away that any set of 5 edges or more will always be 3D. We only need to check 
N = 3 and 4 for this rule.

### Rule 3 - Rotationally unique

For this we'll have to check our current set against our growing list of incomplete cubes. 
That is, for each N the first set we generate will always be counted as 'unique'. 

This one is interesting-- how do we check? Simple way-- we just rotate our current set every possible way and
check to see if it matches with something already in our set. How many possible rotations are there?

Think of a 6-sided die, and imagine you are looking directly at one of the faces. There are 6 numbers that could
be on that face, and for each one of those there are 4 possible rotations. For example, if 6 is facing us:

```
o--4--o    o--5--o    o--3--o    o--2--o
|     |    |     |    |     |    |     |
5  6  2 -> 3  6  4 -> 2  6  5 -> 4  6  3
|     |    |     |    |     |    |     |
o--3--o    o--2--o    o--4--o    o--5--o    
```

So, 24 possible rotations. Now how do we actually generate those from an edge set?

If we consider face [2,5,6,10] our front face, rotating 90 degrees counter-clockwise (as in the above example)
just requires changing the edge numbers according to this cycle:

```
10 -> 5 -> 2 -> 6 -> 10
9 -> 1 -> 3 -> 11 -> 9
12 -> 8 -> 4 -> 7 -> 12
```

This gives us our 4 final rotations. Then the 6 rotations to get each 'face' facing us:

```
Face 1:
No rotation
(Face [2,5,6,10])

Face 2:
Counter-clockwise 90 degrees about vertical axis
(Face [1,5,8,9])
5 -> 6 -> 7 -> 8 -> 5
1 -> 2 -> 3 -> 4 -> 1
9 -> 10 -> 11 -> 12 -> 9

Face 3: 
Counter-clockwise 180 degrees about vertical
(Face [4,7,8,12])
Apply above rotation twice

Face 4:
Clockwise 90 degrees about vertical
(Face [3,6,7,11])
Apply above rotation three times

Face 5: Counter-clockwise 90 degrees about horizontal axis
(Face [9,10,11,12])
1 -> 8 -> 9 -> 5 -> 1
2 -> 4 -> 12 -> 10 -> 2
3 -> 7 -> 11 -> 6 -> 3

Face 6: Clockwise 90 degrees about horizontal
(Face [1,2,3,4])
Apply above rotation three times

```

It's possible that encoding the cube differently would make these rotations a little more intuitive.
Or at least give us an equation to generate them.

Oh well! With only 3 rotations (one for each axis) we can get every rotation needed to express all 24 orientations.

## Displaying the cubes

The above section will get us a nice array of edge arrays, but a list of numbers 1-12 isn't exactly as 
satisfying as the original art piece. It'd be nice to graph these!

My 2 options are to do this in Python (easier, gets me some Python practice) *or* do this in C/C++ 
(gets me some C GUI practice, more of a pain in the ass).

I decided to use Python and matplotlib. It's a pretty simple script, but it does increase the overall 'footprint' 
of this folder since you need to create a virtual env (~350Mb). I mean, you don't have to but I like the consistency.

The C++ file creates a .csv of all the edge numbers. Then, we create a 3-D plot of all the cubes given a mapping of
edge number to 2 3-D points. Each cube is a unit cube.

## How to run the scripts

Just execute the shell script 'buildNRun.sh'. This will compile and run the C++ code 'findCubes.cpp'.

