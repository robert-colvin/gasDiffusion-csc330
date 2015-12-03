program diffusion
!Initialize all parameters and variables that are necessary
real room_dimension, speed_of_gas_molecules, diffusion_coefficent, timestep, distance_between_blocks, DTerm
integer i,j,k,l,m,n,z
!Parameter for number of cubes is ds
integer,parameter ::  ds= 50
integer, parameter :: rsize = ds+2 
integer, parameter :: hsize = rsize/2
real lpass, time, ratio 
real*4 change, mval, mival
real*4, Dimension(rsize,rsize,rsize) :: room
integer, Dimension(rsize,rsize,rsize) :: mask
logical, Dimension(rsize,rsize,rsize) :: lmask
!Complete the calculations required for the diffusing of the gas and proper time
!stepping
diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules)/ds
distance_between_blocks = room_dimension / ds
        DTerm = diffusion_coefficent * timestep /&
(distance_between_blocks*distance_between_blocks)
!Zero the mask, room, and logical mask arrays
        do i=1, rsize
        do j=1, rsize
        do k=1, rsize
                room(k,j,i) = 0.0
                mask(k,j,i) = 0
                lmask(k,j,i) = .false.
        enddo
        enddo
        enddo

!        print *, room
!        print *, mask
!Correctly populate the mask defining the outside and inside
        do i=2, rsize-1
        do j=2, rsize-1
        do k=2, rsize-1
                mask(k,j,i) = 1
                lmask(k,j,i) = .true.
        enddo
        enddo
        enddo

!Code to make the wall in the logical and normal mask
!        do i=rsize/2, rsize-1
!        do j=rsize/2, rsize-1
!                lmask(j,i,hsize) = .false.
!                mask(j,i,hsize) = 0
!        enddo
!        enddo  

!Place the gas into the room        
        room(2,2,2) = 1.0e21
!Zero the time ratio and lpass variables for saftey
        lpass = 0
        time = 0.0
        ratio = 0.0
!Run until the gas has properly diffused
do while( ratio< .99)
        !Three loops one for each dimension
        do i=2, rsize-1
        do j=2, rsize-1
        do k=2, rsize-1
                !Do the calculation for diffusion for each of the six cubes that
                !may or may not be in contact with the selected cube.
                !Secondarilay reverse the use of the loops from inner to outer
                !for effiency.
                change = (room(k,j,i)-room(k+1,j,i))*DTerm*mask(k+1,j,i)
                room(k,j,i) = room(k,j,i)-change
                room(k+1,j,i) = room(k+1,j,i)+change        
                
                change = (room(k,j,i)-room(k-1,j,i))*DTerm*mask(k-1,j,i)
                room(k,j,i) = room(k,j,i)-change
                room(k-1,j,i) = room(k-1,j,i)+change        
                
                change = (room(k,j,i)-room(k,j+1,i))*DTerm*mask(k,j+1,i)
                room(k,j,i) = room(k,j,i)-change
                room(k,j+1,i) = room(k,j+1,i)+change        
                
                change = (room(k,j,i)-room(k,j-1,i))*DTerm*mask(k,j-1,i)
                room(k,j,i) = room(k,j,i)-change
                room(k,j-1,i) = room(k,j-1,i)+change        
                
                change = (room(k,j,i)-room(k,j,i+1))*DTerm*mask(k,j,i+1)
                room(k,j,i) = room(k,j,i)-change
                room(k,j,i+1) = room(k,j,i+1)+change        
                
                change = (room(k,j,i)-room(k,j,i-1))*DTerm*mask(k,j,i-1)
                room(k,j,i) = room(k,j,i)-change
                room(k,j,i-1) = room(k,j,i-1)+change        
        enddo
        enddo
        enddo 
        !Increment the time
        time = time + timestep
        !Give max and min a value
        mval = room(2,2,2)
        mival = room(2,2,2)
        !Find the max and min of the matrix using the built in function and
        !utilising the logical mask to make such an operation possible
        mval = MAXVAL(room, lmask)
        mival = MINVAL(room, lmask)
        !Find the current ratio of diffusion
        ratio = mival/mval

        !print *, ratio, time
        enddo
        !State the amount of time it took to equilibrate the room
        print *, "Box equilibrated in "
        print *, time
        print *, " seconds of Simulated Time."

        end
