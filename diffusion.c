//#include "diffusion.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 10

int main (int argc, char *argv[]) {

	int maxsize;
	if(argc > 1) maxsize = atoi(argv[1]);
	else maxsize = MAXSIZE;
	maxsize += 2;
	double cube[maxsize][maxsize][maxsize];
	short int maskX[maxsize], maskY[maxsize], maskZ[maxsize];

	int i, j, k;

	
//	cube = (double ***) malloc(maxsize * sizeof(double **));
	//mask = (short int ***) malloc((maxsize) * sizeof(short int **));
/*
	for(i = 0; i < maxsize; i++) {
		cube[i] = (double**) malloc(maxsize * sizeof(double*));
		for(j = 0; j < maxsize; j++) {
			cube[i][j] = (double*) malloc(maxsize * sizeof(double));
		}
	}
*/
/*
	for(i = 0; i < maxsize; i++){
		mask[i] = (short int**) malloc((maxsize) * sizeof(short int*));
		for(j = 0; j < maxsize; j++){
			mask[i][j] = (short int*) malloc((maxsize) * sizeof(short int));
		}
	}
*/	
	//printf("\nCube created");
	printf("\nVersion2\n");
	/* Zero the cube */

	for(i = 0; i < maxsize; i++) {
		for(j = 0; j < maxsize; j++) {
			for(k = 0; k < maxsize; k++) {
				cube[i][j][k] = 0.0;
			}
		}
	}

	//printf("\nCube zeroed");

	double diffusion_coefficient = 0.175;
	double room_dimension = 5;
	double speed_of_gas_molecules = 250.0;
	double timestep = (room_dimension / speed_of_gas_molecules) / (maxsize-2);
	double distance_between_blocks = room_dimension / (maxsize-2);
	double DTerm = diffusion_coefficient * timestep / (distance_between_blocks * distance_between_blocks);

	// Initialize the fist cell
	
	cube[1][1][1] = 1.0e21;
	/*
	for(i = 0; i < maxsize; i++){
		for(j = 0; j < maxsize; j++){
			for(k = 0; k < maxsize; k++){
				mask[i][j][k] = 0;
			}
		}
	}
	*/

	maskX[0] = maskY[0] = maskZ[0] = 0;
	maskX[maxsize-1] = maskY[maxsize-1] = maskZ[maxsize-1] = 0;
	for (i=1;i<maxsize-1;i++){
		maskX[i] = maskY[i] = maskZ[i] = 1;
		
		/*
		for (j=1;j<maxsize-1;j++){
			for (k=1;k<maxsize-1;k++){
				mask[i][j][k] = 1;
			}
		}
		*/
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
				for (k=1; k<maxsize-1; k++) { 
					change = (cube[i][j][k]-cube[i+1][j][k])*DTerm*(maskX[i+1]*maskY[j]*maskZ[k]);
					cube[i][j][k]-=change;
					cube[i+1][j][k]+=change;


					change = (cube[i][j][k]-cube[i-1][j][k])*DTerm*(maskX[i-1]*maskY[j]*maskZ[k]);
					cube[i][j][k]-=change;
					cube[i-1][j][k]+=change;


					change = (cube[i][j][k]-cube[i][j+1][k])*DTerm*(maskX[i]*maskY[j+1]*maskZ[k]);
					cube[i][j][k]-=change;
					cube[i][j+1][k]+=change;


					change = (cube[i][j][k]-cube[i][j-1][k])*DTerm*(maskX[i]*maskY[j-1]*maskZ[k]);
					cube[i][j][k]-=change;
					cube[i][j-1][k]+=change;
	

					change = (cube[i][j][k]-cube[i][j][k+1])*DTerm*(maskX[i]*maskY[j]*maskZ[k+1]);
					cube[i][j][k]-=change;
					cube[i][j][k+1]+=change;


					change = (cube[i][j][k]-cube[i][j][k-1])*DTerm*(maskX[i]*maskY[j]*maskZ[k-1]);
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

	//	printf("\n%E time = %lf", ratio, time);

	} while(ratio < 0.99);

	for(i = 1; i < maxsize - 1; i++){
		for(j = 1; j < maxsize - 1; j++){
			for(k = 1; k < maxsize - 1; k++){
				sum += cube[i][j][k];
			}
		}
	}
	printf("\nFinal # of particles: %E\n", sum);
		
	//printf("\n%E ---- %E ---- %E\n", cube[1][1][1], cube[maxsize/2][maxsize/2][maxsize/2], cube[maxsize-2][maxsize-2][maxsize-2]);

	printf("\nBox equilibrated in %lf seconds of simulated time.\n", time);
}
