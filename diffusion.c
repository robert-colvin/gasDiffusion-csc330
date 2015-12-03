//#include "diffusion.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10

int main (int argc, char *argv[]) {

	int maxsize, wall;
	if(argc != 3) {
		printf("\nERROR: Run as ./diffusion size wall\n wall = 1 to add the wall, 0 otherwise\n");
		exit(1);
	}
	else {
		maxsize = atoi(argv[1]);
		wall = atoi(argv[2]);
	}
	maxsize += 2;
	double cube[maxsize][maxsize][maxsize];
	short int mask[maxsize][maxsize][maxsize];

	int i, j, k;

	
	/* Zero the cube */

	for(i = 0; i < maxsize; i++) {
		for(j = 0; j < maxsize; j++) {
			for(k = 0; k < maxsize; k++) {
				cube[i][j][k] = 0.0;
				mask[i][j][k] = 0;
			}
		}
	}

	double diffusion_coefficient = 0.175;
	double room_dimension = 5;
	double speed_of_gas_molecules = 250.0;
	double timestep = (room_dimension / speed_of_gas_molecules) / (maxsize-2);
	double distance_between_blocks = room_dimension / (maxsize-2);
	double DTerm = diffusion_coefficient * timestep / (distance_between_blocks * distance_between_blocks);

	// Initialize the fist cell
		
	cube[1][1][1] = 1.0e21;
	for(i = 1; i < maxsize-1; i++){
		for(j = 1; j < maxsize-1; j++){
			for(k = 1; k < maxsize-1; k++){
				mask[i][j][k] = 1;
			}
		}
	}
	
	//code for wall
	if(wall == 1){
		for (i = maxsize - 1; i > maxsize/2; i--){
			for(j = maxsize - 1; j > maxsize/2; j--){
				mask[i][j][maxsize/2] = 0;
			}		
		}
	}

	int pass = 0;
	double time = 0.0;
	double ratio;
	double change;
        double maxval, minval, value;
	double sum = 0.0;

	do{
		change = 0.0;

		for (i=1; i<maxsize-1; i++) { 
			for (j=1; j<maxsize-1; j++) { 
				for(k=1; k<maxsize-1; k++) {
					change = (cube[i][j][k]-cube[i+1][j][k])*DTerm*(mask[i+1][j][k]);
					cube[i][j][k]-=change;
					cube[i+1][j][k]+=change;


					change = (cube[i][j][k]-cube[i-1][j][k])*DTerm*(mask[i-1][j][k]);
					cube[i][j][k]-=change;
					cube[i-1][j][k]+=change;


					change = (cube[i][j][k]-cube[i][j+1][k])*DTerm*(mask[i][j+1][k]);
					cube[i][j][k]-=change;
					cube[i][j+1][k]+=change;


					change = (cube[i][j][k]-cube[i][j-1][k])*DTerm*(mask[i][j-1][k]);
					cube[i][j][k]-=change;
					cube[i][j-1][k]+=change;
	

					change = (cube[i][j][k]-cube[i][j][k+1])*DTerm*(mask[i][j][k+1]);
					cube[i][j][k]-=change;
					cube[i][j][k+1]+=change;


					change = (cube[i][j][k]-cube[i][j][k-1])*DTerm*(mask[i][j][k-1]);
					cube[i][j][k]-=change;
					cube[i][j][k-1]+=change;
				}
	        	}
		}

	
		time = time + timestep;
	
		maxval = cube[1][1][1];
		minval = cube[1][1][1];
		
		for(i = 1; i < maxsize-1; i++){
			for(j = 1; j < maxsize-1; j++){
				for(k = 1; k < maxsize-1; k++) {
					value = cube[i][j][k];
					if(value > maxval) maxval = value;
					else if(value < minval) minval = value;
				}
			}
		}
	
		ratio = minval / maxval;

		//printf("\n%E time = %lf", ratio, time);

	} while(ratio < 0.99);

	for(i = 1; i < maxsize - 1; i++){
		for(j = 1; j < maxsize - 1; j++){
			for(k = 1; k < maxsize - 1; k++){
				sum += cube[i][j][k];
			}
		}
	}
	printf("\nFinal # of particles: %E\n", sum);
		
	printf("\nBox equilibrated in %lf seconds of simulated time.\n", time);
}
