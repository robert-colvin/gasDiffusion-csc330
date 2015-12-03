#!/usr/bin/python
import numpy as np
import math
#Establish the variables needed 
#DS is the size variable 
dS = 20
rsize = dS+2
arraySize = np.power(rsize,3)
print(arraySize)
room = np.zeros(arraySize).reshape(rsize,rsize,rsize)
mask = np.zeros(arraySize).reshape(rsize,rsize,rsize)
#Populate the mask
for i in xrange(1,rsize-1):
	for j in xrange(1,rsize-1):
		for k in xrange(1,rsize-1):
			mask[i,j,k] = 1

#Code for wall
#for i in xrange(rsize/2, rsize-1)
#	for j in xrange(rsize/2, rsize-1)
#		mask[i,j,rsize/2] = 0

#Calculate the necessary variables for the problem
diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules) / dS
distance_between_blocks = room_dimension / dS
print(diffusion_coefficent, timestep, distance_between_blocks)
DTerm = diffusion_coefficent * timestep / (distance_between_blocks*distance_between_blocks)
diffused = 0
#Add the gas into the room
room[1,1,1] = 1.0e21
#Zero the following variables for saftey
lpass = 0
time = 0.0
ratio = 0.0
#Run until the equilibration point of .99 is reached across the cubes of the room
while ratio<.99:
	#Three loops one for each dimension
	for i in xrange(1,rsize-1):
		for j in xrange(1,rsize-1):
			for k in xrange(1,rsize-1):
				#Do the calculations for all of the six possible side of the cube that gas could diffuse from
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
	#Step the time variable and give min and max a value
	time = time + timestep
	maxval = room[1,1,1]
	minval = room[1,1,1]
	#Find the min and max for the whole matrix
	for i in xrange(1,rsize-1):
		for j in xrange(1,rsize-1):
			for k in xrange(1,rsize-1):
				maxval = max(room[i,j,k], maxval)
				minval = min(room[i,j,k], minval)
	#Calculate the ratio
	ratio = minval/maxval

#	print ratio, time 
#Print the time taken to equilibrate
print "Box equilibrated in "
print time
print " seconds of simulated time."
