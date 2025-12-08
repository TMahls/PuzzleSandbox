import csv
import matplotlib.pyplot as plt
import numpy as np

# Read input data file
data = []
with open('incompleteCubes.csv','r') as file:
	csv_reader = csv.reader(file)
	for row in csv_reader:
		data.append(row)

# Create figure
ax = plt.figure().add_subplot(projection='3d')

# Edge number to point
pointMapping = np.array([[0,0,0],[0,1,0],
			[0,0,0],[1,0,0],
			[1,0,0],[1,1,0],
			[0,1,0],[1,1,0],
			[0,0,0],[0,0,1],
			[1,0,0],[1,0,1],
			[1,1,0],[1,1,1],
			[0,1,0],[0,1,1],
			[0,0,1],[0,1,1],
			[0,0,1],[1,0,1],
			[1,0,1],[1,1,1],
			[0,1,1],[1,1,1]])

# Plot a cube
origin = [0,0,0]
lastLength = 0
for row in data:
	data = np.array(row)
	data = data.astype(int)

	if lastLength == 0:
		lastLength = len(data)
	elif len(data) != lastLength:
		lastLength = len(data)
		origin[0] = 0
		origin[1] = origin[1] + 1.5

	for i in data:
		x = origin[0]+np.array([pointMapping[2*i-2][0], pointMapping[2*i-1][0]])
		y = origin[1]+np.array([pointMapping[2*i-2][1], pointMapping[2*i-1][1]])
		z = origin[2]+np.array([pointMapping[2*i-2][2], pointMapping[2*i-1][2]])
		ax.plot(x,y,z,'-b')
	origin[0] = origin[0] + 1.5

# Set axes limits and labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.axis('equal')

plt.show()
