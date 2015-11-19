program diffusion
real room_dimension, speed_of_gas_molecules, diffusion_coefficent, timestep, distance_between_blocks, DTerm
integer i,j,k,l,m,n,z
integer,parameter ::  ds= 10
integer, parameter :: rsize = ds+2 
real lpass, time, ratio 
real*4 change, mval, mival
real*4, Dimension(rsize,rsize,rsize) :: room
integer, Dimension(rsize,rsize,rsize) :: mask
diffusion_coefficent = 0.175
room_dimension = 5.0
speed_of_gas_molecules = 250.0
timestep = (room_dimension/speed_of_gas_molecules)/ds
distance_between_blocks = room_dimension / ds
        DTerm = diffusion_coefficent * timestep /&
(distance_between_blocks*distance_between_blocks)

        do i=1, rsize
        do j=1, rsize
        do k=1, rsize
                room(k,j,i) = 0.0
                mask(k,j,i) = 0
        enddo
        enddo
        enddo

!        print *, room
!        print *, mask

        do i=2, rsize-1
        do j=2, rsize-1
        do k=2, rsize-1
                mask(k,j,i) = 1
        enddo
        enddo
        enddo

        
        room(2,2,2) = 1.0e21
        lpass = 0
        time = 0.0
        ratio = 0.0

do while( ratio< .99)
        !Go inner to outer on the loops instead of the normal outer to inner
        do i=2, rsize-1
        do j=2, rsize-1
        do k=2, rsize-1
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
        time = time + timestep

        mval = room(2,2,2)
        mival = room(2,2,2)

        do i=2, rsize-1
        do j=2, rsize-1
        do k=2, rsize-1
        mval = MAX(mval,room(k,j,i))
        mival = MIN(mival, room(k,j,i))
        enddo
        enddo
        enddo
        ratio = mival/mval

        !print *, ratio, time
        enddo
        print *, "Box equilibrated in "
        print *, time
        print *, " seconds of Simulated Time."

        end
