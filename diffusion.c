//#include "diffusion.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 5

int main (int argc, char *argv[]) {

	int maxsize;
	if(argc > 1) maxsize = atoi(argv[1]);
	else maxsize = MAXSIZE;
	double ***cube;
	int ***mask;

	int i, j, k, l, m, n;

	
	cube = (double ***) malloc(maxsize * sizeof(double **));
	mask = (int ***) malloc((maxsize + 2) * sizeof(int **));

	for(i = 0; i < maxsize; i++) {
		cube[i] = (double**) malloc(maxsize * sizeof(double*));
		for(j = 0; j < maxsize; j++) {
			cube[i][j] = (double*) malloc(maxsize * sizeof(double));
		}
	}

	for(i = 0; i < maxsize + 2; i++){
		mask[i] = (int**) malloc((maxsize + 2) * sizeof(int*));
		for(j = 0; j < maxsize + 2; j++){
			mask[i][j] = (int*) malloc((maxsize + 2) * sizeof(int));
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
	double maxval;
	double minval;
	double value;
	double maxi, maxj, maxk;
	maxi = maxj = maxk = maxsize;
	i = j = k = 0;
	do {
		for(i = 0; i < maxsize/* && cube[i][j][k] != 0*/; i++) {
			for(j = 0; j < maxsize/* && cube[i][j][k] != 0*/; j++) {
				for(k = 0; k < maxsize/* && cube[i][j][k] != 0*/; k++) {
					if(i == 0) l = 0;
					else l = i - 1;
					maxi = i + 1 ; //(int)((double)(maxsize-1)/(double)i);
					if(maxi > maxsize - 1) maxi = maxsize - 1;
					for(l; l <= maxi; l++) {
						if(j == 0) m = 0;
						else m = j - 1;
						maxj = j + 1; //(int)((double)(maxsize-1)/(double)j);
						if(maxj > maxsize - 1) maxj = maxsize - 1;
						for(m; m <= maxj; m++) {
							if(k == 0) n = 0;
							else n = k - 1;
							maxk = k + 1; //(int)((double)(maxsize-1)/(double)k);
							if(maxk > maxsize - 1) maxk = maxsize - 1;
							for(n; n <= maxk; n++) {
								if( ((i == l) && (j == m) && (k == n+1)) ||
								    ((i == l) && (j == m) && (k == n-1)) ||
								    ((i == l) && (j == m+1) && (k == n)) ||
								    ((i == l) && (j == m-1) && (k == n)) ||
								    ((i == l+1) && (j == m) && (k == n)) ||
								    ((i == l-1) && (j == m) && (k == n)) ) {
									
									change = (cube[i][j][k] - cube[l][m][n]) * DTerm;
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
	
		maxval = cube[0][0][0];
		minval = cube[0][0][0];
		
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

		printf("\n%E time = %lf", ratio, time);

	} while(ratio < 0.99);

	printf("\n%E ---- %E ---- %E\n", cube[0][0][0], cube[maxsize/2][maxsize/2][maxsize/2], cube[maxsize-1][maxsize-1][maxsize-1]);

	printf("\nBox equilibrated in %lf seconds of simulated time.\n", time);
}
