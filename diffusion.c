//#include "diffusion.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

	int maxsize = 10;
	double ***cube;

	int i, j, k, l, m, n;

	for(i = 0; i < maxsize; i++) {
		cube[i] = (double**) malloc(maxsize * sizeof(double*));
	}

	for(i = 0; i < maxsize; i++) {
		for(j = 0; j < maxsize; j++) {
			cube[i][j] = (double*) malloc(maxsize * sizeof(double));
		}
	}
	
	printf("\nCube created");

	/* Zero the cube */

	for(i = 0; i < maxsize; i++) {
		for(j = 0; j < maxsize; j++) {
			for(k = 0; k < maxsize; k++) {
				cube[i][j][k] = 0.0;
			}
		}
	}

	printf("\nCube zeroed");

	double diffusion_coefficient = 0.175;
	double room_dimension = 5;
	double speed_of_gas_molecules = 250.0;
	double timestep = (room_dimension / speed_of_gas_molecules) / maxsize;
	double distance_between_blocks = room_dimension / maxsize;
	double DTerm = diffusion_coefficient * timestep / (distance_between_blocks * distance_between_blocks);

	// Initialize the fist cell
	
	cube[0][0][0] = 1.0e21;

	int pass = 0;
	double time = 0.0;
	double ratio = 0.0;
	double change;

	do {
		for(i = 0; i < maxsize; i++) {
			for(j = 0; j < maxsize; j++) {
				for(k = 0; k < maxsize; k++) {
					for(l = 0; l < maxsize; l++) {
						for(m = 0; m < maxsize; m++) {
							for(n = 0; n < maxsize; n++) {
								if( ((i == l) && (j == m) && (k == n+1)) ||
								    ((i == l) && (j == m) && (k == n-1)) ||
								    ((i == l) && (j == m+1) && (k == n)) ||
								    ((i == l) && (j == m-1) && (k == n)) ||
								    ((i == l+1) && (j == m) && (k == n)) ||
								    ((i == l-1) && (j == m) && (k == n)) ) {
									
									change = (cube[i][j][k] - cube[l][m][l]) * DTerm;
									cube[i][j][k] = cube[i][j][k] - change;
									cube[l][m][n] = cube[l][m][n] + change;
								}
							}
						}
					}
				}
			}
		}
		
		time = time + timestep;
	
		double maxval = cube[0][0][0];
		double minval = cube[0][0][0];
		double value;	

		for(i = 0; i < maxsize; i++){
			for(j = 0; j < maxsize; j++){
				for(k = 0; k < maxsize; k++) {
					value = cube[i][j][k];
					if(value > maxval) maxval = value;
					else if(value < minval) minval = value;
				}
			}
		}
	
		ratio = minval / maxval;

		printf("\n%lf time = %lf", ratio, time);

	} while(ratio < 0.99);

	printf("\nBox equilibrated in %lf seconds of simulated time.", time);
}
