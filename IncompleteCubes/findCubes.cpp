// Finding incomplete cubes
// See the README for problem and algorithm details

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<char>> generateNEdgeSets(unsigned short n);
void recursiveAddEdges(std::vector<std::vector<char>> * fullSet, std::vector<char> currSet,\
	unsigned short currEdgeNum, unsigned short n);
bool isConnected(std::vector<char> n);
bool recursiveFindNeighbors(std::vector<char> * edgeSet, std::vector<bool> * currFound,\
		 char currIdx, std::vector<std::vector<char>> * neighborDB);
bool is3D(std::vector<char> n);
bool isRotUnique(std::vector<char> n, std::vector<std::vector<char>> compareSet);

// ANSI Color Codes
const std::string brightCyan = "\033[96m";
const std::string brightGreen = "\033[92m";
const std::string brightRed = "\033[91m";
const std::string resetColor = "\033[0m";

int main() {
	// Let's time the operation of this
	const std::chrono::time_point<std::chrono::high_resolution_clock> startTime = \
		std::chrono::high_resolution_clock::now();

	////////////////////////////////////////

	// STEP 1 - GENERATE ALL EDGE COMBOS FOR N = 3 TO 11
	std::vector<std::vector<char>> allEdgeSets;
	for (unsigned short i = 3; i < 12; i++) {
		std::vector<std::vector<char>> nEdgeSet = generateNEdgeSets(i);
		std::cout << "n: " << i << " | size: " << nEdgeSet.size() << std::endl;
		for (std::vector<char> j : nEdgeSet)
			allEdgeSets.push_back(j);
	}
	std::cout << "Total edge sets: " << brightCyan << \
		allEdgeSets.size() << resetColor << std::endl;
	/*
	std::cout << "All edge sets:" << std::endl;
	for (std::vector<char> i : allEdgeSets) {
		std::cout << "[";
		for (char j : i)
			std::cout << (int)j << ", ";
		std::cout << "]" << std::endl;
	}
	*/

	// STEP 2 - CHECK OUR 3 RULES AGAINST THEM AND ADD TO ANSWER SET
	std::vector<std::vector<char>> answerSet;

	for (std::vector<char> i : allEdgeSets)
		if ( isConnected(i) && is3D(i) && isRotUnique(i, answerSet) )
			answerSet.push_back(i);

	std::cout << "Number of incomplete open cubes: " << brightCyan << \
		answerSet.size() << resetColor << std::endl;

	std::cout << "Answer set:" << std::endl;
	for (std::vector<char> i : answerSet) {
		std::cout << "[";
		for (char j : i)
			std::cout << (int)j << ", ";
		std::cout << "]" << std::endl;
	}

	////////////////////////////////////////

	const std::chrono::time_point<std::chrono::high_resolution_clock> stopTime = \
		std::chrono::high_resolution_clock::now();

	double duration_ns = std::chrono::nanoseconds(stopTime - startTime).count();

	// How many times we need to divide by 1000 to get in the range of 0-999
	short timeFactor = std::floor(std::log(duration_ns) / (3 * std::log(10)));
	int timerScaled = duration_ns / std::pow(1000, timeFactor);

	std::string timerUnitScaled;
	switch(timeFactor) {
		case 0:
			timerUnitScaled = "nanoseconds";
			break;
		case 1:
			timerUnitScaled = "microseconds";
			break;
		case 2:
			timerUnitScaled = "milliseconds";
			break;
		default:
			// Technically this will break for times over 1000 seconds
			// But we aren't measuring that long of a time scale :)
			timerUnitScaled = "seconds";
			break;
	}

	if ( ( (timeFactor == 2) && (timerScaled >= 500)) || (timeFactor > 2) )
		// 500 ms or larger runtime gets highlighted red
		std::cout << "Time taken: " << brightRed << timerScaled << " " << \
			timerUnitScaled << resetColor << std::endl;
	else
		std::cout << "Time taken: " << timerScaled << " " << timerUnitScaled << std::endl;

	// Write output to file
	std::ofstream outputFile("incompeteCubes.csv");
	if (!outputFile.is_open()) {
		std::cerr << "Error: Could not open file 'incompleteCubes.csv'" << std::endl;
		return 1;
	}

	for (std::vector<char> i : answerSet) {
		for (unsigned int j = 0; j < (i.size() - 1); j++)
			outputFile << (short)i[j] << ",";
		outputFile << (short)i[i.size()-1] << std::endl;
	}

	outputFile.close();

	std::cout << "Data written to 'incompleteCubes.csv'" << std::endl;
	return 0;
}

std::vector<std::vector<char>> generateNEdgeSets(unsigned short n) {
	std::vector<std::vector<char>> out;
	std::vector<char> currSet;
	recursiveAddEdges(&out, currSet, 1, n);
	return out;
}

void recursiveAddEdges(std::vector<std::vector<char>> * fullSet, std::vector<char> currSet,\
	unsigned short currEdgeNum, unsigned short n) {
	std::vector<char> testSet;
	for (int i = currEdgeNum; i <= 12; i++) {
		testSet = currSet;
		testSet.push_back(i);
		if (testSet.size() < n) {
			recursiveAddEdges(fullSet, testSet, i+1, n);
		} else if (testSet.size() == n) {
			fullSet->push_back(testSet);
		}
	}
}

bool isConnected(std::vector<char> n) {
// Determine is the edge set is connected
// We can navigate to every edge in the set from our first edge

	std::vector<std::vector<char>> neighborList =  {
		{2,4,5,8},{1,3,5,6},{2,4,6,7},
		{1,3,7,8},{1,2,9,10},{2,3,10,11},
		{3,4,11,12},{1,4,9,12},{5,8,10,12},
		{5,6,9,11},{6,7,10,12},{7,8,9,11},
	};

	std::vector<bool> found(n.size());
	std::fill(found.begin(), found.end(), false);
	/*
	std::cout << "Edge set: [";
	for (char i : n)
		std::cout << (int)i << ", ";
	std::cout << "]" << std::endl;

	std::cout << "Connected = " << recursiveFindNeighbors(&n, &found, 0, &neighborList) << std::endl;
	*/
	return recursiveFindNeighbors(&n, &found, 0, &neighborList);
}

bool recursiveFindNeighbors(std::vector<char> * edgeSet, std::vector<bool> * currFound,\
		 char currIdx, std::vector<std::vector<char>> * neighborDB) {
	/*
	std::cout << "Edge set: [";
	for (char i : *edgeSet)
		std::cout << (int)i << ", ";
	std::cout << "]" << std::endl;
	std::cout << "Curr found: [";
	for (bool i : *currFound)
		std::cout << i << ", ";
	std::cout << "]" << std::endl;
	std::cout << "Curr idx: " << (int)currIdx << std::endl;
	*/
	// Base case
	bool connected = true;
	for (bool i : *currFound)
		if (!i)
			connected = false;
	if (connected)
		return true;

	std::vector<char> currNeighbors = neighborDB->at(edgeSet->at((short)currIdx) - 1);
	for (unsigned short i = 0; i < edgeSet->size(); i++) {
		//std::cout << "i = " << i << std::endl;
		if ( (i != currIdx) && \
			(std::find(currNeighbors.begin(), currNeighbors.end(),\
			 edgeSet->at(i)) != currNeighbors.end()) && (!currFound->at(i)) ) {
			currFound->at(i) = true;
			connected = recursiveFindNeighbors(edgeSet, currFound, i, neighborDB);
			if (connected)
				return true;
		}
	}

	return false;
}

bool is3D(std::vector<char> n) {
// Determine if the edge set n is 3-Dimensional
// That is, 'n' cannot be a subset of any of the 6 face sets.
	if (n.size() > 4)
		return true;

	std::vector<std::vector<char>> allFaces = {
		{1,2,3,4},{1,5,8,9},{2,5,6,10},
		{3,6,7,11},{4,7,8,12},{9,10,11,12},
	};
	std::vector<char> faceSet;
	for (int face = 0; face < 6; face++) {
		faceSet = allFaces[face];
		if (std::includes(faceSet.begin(), faceSet.end(), n.begin(), n.end()))
			return false;
	}

	return true;
}

bool isRotUnique(std::vector<char> n, std::vector<std::vector<char>> compareSet) {
// Determine if the edge set n is rotationally unique among our current set of incomplete cubes
// We iterate through all 24 rotations of 'n' and compare it to every element in our compare set.

	std::vector<char> currRot = n;

	// Each of our 3 rotation axes has an edge map
	char vertRotMap[] = {2,3,4,1,6,7,8,5,10,11,12,9};
	char horzRotMap[] = {8,4,7,12,1,3,11,9,5,2,6,10};
	char depthRotMap[] = {3,6,11,7,2,10,12,4,1,5,9,8};
	/*
	std::cout << "Original set: [";
	for (char i : n)
		std::cout << (int)i << ", ";
	std::cout << "]" << std::endl;
	*/
	for (int faceN = 0; faceN < 6; faceN++) {

		if ( (faceN > 0) && (faceN < 4) ) {
			// Rotate 90 degrees clockwise about vert axis
			for (unsigned int i = 0; i < currRot.size(); i++)
				currRot[i] = vertRotMap[currRot[i] - 1];
		} else if (faceN == 4) {
			currRot = n;
			// Rotate 90 degrees clockwise about horz axis
			for (unsigned int i = 0; i < currRot.size(); i++)
				currRot[i] = horzRotMap[currRot[i] - 1];

		} else if (faceN == 5) {
			// Rotate 180 degrees clockwise about horz axis
			for (unsigned int i = 0; i < currRot.size(); i++)
				currRot[i] = horzRotMap[currRot[i] - 1];
			for (unsigned int i = 0; i < currRot.size(); i++)
				currRot[i] = horzRotMap[currRot[i] - 1];
		}

		std::sort(currRot.begin(), currRot.end());
		/*
		std::cout << "Face #" << faceN+1 << ": [";
		for (char i : currRot)
			std::cout << (int)i << ", ";
		std::cout << "]" << std::endl;
		*/
		for (int rotN = 0; rotN < 4; rotN++) {
			// Compare to set
			for (std::vector<char> comp : compareSet)
				if (currRot == comp)
					return false;

			// Rotate 90 degrees clockwise about depth axis
			for (unsigned int i = 0; i < currRot.size(); i++)
				currRot[i] = depthRotMap[currRot[i] - 1];
			std::sort(currRot.begin(), currRot.end());
			/*
			std::cout << "Rotated: [";
			for (char i : currRot)
				std::cout << (int)i << ", ";
			std::cout << "]" << std::endl;
			*/
		}
	}

	return true;
}
