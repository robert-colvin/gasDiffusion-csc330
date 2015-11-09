program diffusion
real room_dimension, speed_of_gas_molecules, diffusion_coefficent, timestep, distance_between_blocks, DTerm
integer i,j,z
integer,parameter ::  ds= 10 
real lpass, time, ratio 
real*4, Dimension(ds,ds,ds) :: room
diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules)/ds
distance_between_blocks = room_dimension / ds
DTerm = diffusion_coefficent * timestep /&
(distance_between_blocks*distance_between_blocks)

do i=1, ds
        do j=1, ds
                do z=1, ds
                        room(i,j,z) = 0.0
                enddo
        enddo
enddo

print *, room

lpass = 0
time = 0.0
ratio = 0.0


end
