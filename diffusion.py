#!/usr/bin/python
import numpy as np
import math

dS = 10
arraySize = np.power(dS,3)
print(arraySize)
room = np.zeros(arraySize).reshape(dS,dS,dS)
#print(room)

diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules) / dS
distance_between_blocks = room_dimension / dS
print(diffusion_coefficent, timestep, distance_between_blocks)
DTerm = diffusion_coefficent * timestep / (distance_between_blocks*distance_between_blocks)

room[0][0][0] = 1.0e21

lpass = 0
time = 0.0
ratio = 0.0


