program diffusion
real room_dimension, speed_of_gas_molecules, diffusion_coefficent, timestep, distance_between_blocks, DTerm
integer i,j,k,l,m,n,z
integer,parameter ::  ds= 10 
real lpass, time, ratio 
real*4 change, mval, mival
real*4, Dimension(ds+1,ds+1,ds+1) :: room
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

        room(1,1,1) = 1.0e21
        lpass = 0
        time = 0.0
        ratio = 0.0

do while( ratio< .99)
        !Go inner to outer on the loops instead of the normal outer to inner
        do i=1,ds
        do j=1, ds
        do k=1, ds
        do l=1, ds
        do m=1, ds
        do n=1, ds
        if (( ( n == k ) .and.  (j ==m)   .and. ( i == l+1) ) .or.&
                        ( ( n == k )   .and. ( j == m )   .and. ( i == l-1) ) .or.&
                        ( ( n == k )   .and. ( j == m+1 ) .and. ( i == l)   ) .or.&
                        ( ( n == k )   .and. ( j == m-1 ) .and. ( i == l)   ) .or.&
                        ( ( n == k+1 ) .and. ( j == m )   .and. ( i == l)   ) .or.&
                        ( ( n == k-1 ) .and. ( j == m )   .and. ( i == l)   ) ) THEN
         change = &
(room(k,j,i)-room(n,m,l))*DTerm
        room(k,j,i) =&
        room(k,j,i)-change
        room(n,m,l) =&
        room(n,m,l) + change
        endif         
        enddo
        enddo
        enddo
        enddo
        enddo
        enddo
        time = time + timestep

        mval = room(1,1,1)
mival = room(1,1,1)

        do i=1, ds
        do j=1, ds
        do k=1, ds
        mval = MAX(mval,room(k,j,i))
        mival = MIN(mival, room(k,j,i))
        enddo
        enddo
        enddo
        ratio = mival/mval

        print *, ratio, time
        enddo
        print *, "Box equilibrated in "
        print *, time
        print *, " seconds of Simulated Time."

        end
