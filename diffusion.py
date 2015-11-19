#!/usr/bin/python
import numpy as np
import math

dS = 10
arraySize = np.power(dS,3)
print(arraySize)
room = 
#room = np.zeros(arraySize).reshape(dS,dS,dS)
#print(room)

diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules) / dS
distance_between_blocks = room_dimension / dS
print(diffusion_coefficent, timestep, distance_between_blocks)
DTerm = diffusion_coefficent * timestep / (distance_between_blocks*distance_between_blocks)
diffused = 0

room[0][0][0] = 1.0e21

lpass = 0
time = 0.0
ratio = 0.0

while ratio<.99:
	for i in range(0,dS):
		for j in range(0,dS):
			for k in range(0,dS):
				for l in range(0,dS):
					for m in range(0,dS):
						for n in range(0,dS):
							if i == l and j == m and k == n+1 or i == l and j == m and k == n-1 or i == l and j == m+1 and k == n or i == l and j == m-1 and k == n or i == l+1 and j == m and k == n or i == l-1 and j == m and k == n :
								change = (room[i][j][k] - room[l][m][n]) * DTerm
								room[i][j][k] = room[i][j][k] - change
								room[l][m][n] = room[l][m][n]+change

	time = time + timestep
	maxval = room[0][0][0]
	minval = room[0][0][0]

	for i in range(0,dS):
		for j in range(0,dS):
			for k in range(0,dS):
				maxval = max(room[i][j][k], maxval)
				minval = min(room[i][j][k], minval)

	ratio = minval/maxval

	print ratio, time 

print "Box equilibrated in "
print time
print " seconds of simulated time."
