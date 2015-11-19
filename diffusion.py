#!/usr/bin/python
import numpy as np
import math

dS = 10
rsize = dS+2
arraySize = np.power(rsize,3)
print(arraySize)
room = np.zeros(arraySize).reshape(rsize,rsize,rsize)
mask = np.zeros(arraySize).reshape(rsize,rsize,rsize)

for i in xrange(1,rsize-1):
	for j in xrange(1,rsize-1):
		for k in xrange(1,rsize-1):
			mask[i,j,k] = 1

#print(room)

diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules) / dS
distance_between_blocks = room_dimension / dS
print(diffusion_coefficent, timestep, distance_between_blocks)
DTerm = diffusion_coefficent * timestep / (distance_between_blocks*distance_between_blocks)
diffused = 0

room[1,1,1] = 1.0e21

lpass = 0
time = 0.0
ratio = 0.0

while ratio<.99:
	for i in xrange(1,rsize-1):
		for j in xrange(1,rsize-1):
			for k in xrange(1,rsize-1):
				change = (room[i,j,k] - room[i+1,j,k])*DTerm*mask[i+1,j,k]
				room[i,j,k]-= change
				room[i+1,j,k]+=change	
				
				change = (room[i,j,k] - room[i-1,j,k])*DTerm*mask[i-1,j,k]
				room[i,j,k]-=change
				room[i-1,j,k]+=change	
				
				change = (room[i,j,k] - room[i,j+1,k])*DTerm*mask[i,j+1,k]
				room[i,j,k]-=change
				room[i,j+1,k]+=change	
				
				change = (room[i,j,k] - room[i,j-1,k])*DTerm*mask[i,j-1,k]
				room[i,j,k]-=change
				room[i,j-1,k]+=change	
				
				change = (room[i,j,k] - room[i,j,k+1])*DTerm*mask[i,j,k+1]
				room[i,j,k]-=change
				room[i,j,k+1]+=change	
				
				change = (room[i,j,k] - room[i,j,k-1])*DTerm*mask[i,j,k-1]
				room[i,j,k]-=change
				room[i,j,k-1]+=change	
	time = time + timestep
	maxval = room[1][1][1]
	minval = room[1][1][1]

	for i in xrange(1,rsize-1):
		for j in xrange(1,rsize-1):
			for k in xrange(1,rsize-1):
				maxval = max(room[i][j][k], maxval)
				minval = min(room[i][j][k], minval)

	ratio = minval/maxval

	print ratio, time 

print "Box equilibrated in "
print time
print " seconds of simulated time."
