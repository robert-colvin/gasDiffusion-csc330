import java.util.*;

public class  rdiffusion {

public static void main(String[] args) {

final int maxsize = 10;
final int realsize = maxsize+2;
Double[][][] cube = new Double[realsize][realsize][realsize];
short[][][] mask = new short[realsize][realsize][realsize];
Double[][][] testcube = new Double[maxsize][maxsize][maxsize];
for (int i =0;i<realsize;i++){
	for (int j=0;j<realsize;j++){
		for (int k=0;k<realsize;k++){
			cube[i][j][k] = 0.0;
		}
	}
}
// Initialize the first cell
//
cube[1][1][1] = 1.0e21;

for (int i=1;i<realsize-1;i++)
{
	for (int j=1;j<realsize-1;j++)
	{
		for (int k=1;k<realsize-1;k++)
		{
				mask[i][j][k] = 1;
		}
	}
}
for (int i=realsize-1;i>realsize/2;i--){
	for (int j=realsize-1;j>realsize/2;j--){
		mask[i][j][realsize/2] = 0;
	}
}

double diffusion_coefficient = 0.175; 
double room_dimension = 5;                      // 5 Meters
double speed_of_gas_molecules = 250.0;          // Based on 100 g/mol gas at RT
double timestep = (room_dimension / speed_of_gas_molecules) / maxsize; // h in seconds
double distance_between_blocks = room_dimension / maxsize;

double DTerm = diffusion_coefficient * timestep / (distance_between_blocks*distance_between_blocks);



int pass = 0;
double time = 0.0;  // to keep up with accumulated system time.
double ratio = 0.0;

do {
	Double change = 0.0;

	for (int i=1; i<realsize-1; i++) { 
		for (int j=1; j<realsize-1; j++) { 
			for (int k=1; k<realsize-1; k++) { 
				change = (cube[i][j][k]-cube[i+1][j][k])*DTerm*mask[i+1][j][k];
				cube[i][j][k]-=change;
				cube[i+1][j][k]+=change;
				
				
			
				change = (cube[i][j][k]-cube[i-1][j][k])*DTerm*mask[i-1][j][k];
				cube[i][j][k]-=change;
				cube[i-1][j][k]+=change;
				=cube[i-1][j][k];


				change = (cube[i][j][k]-cube[i][j+1][k])*DTerm*mask[i][j+1][k];
				cube[i][j][k]-=change;
				cube[i][j+1][k]+=change;
				=cube[i][j+1][k];

				change = (cube[i][j][k]-cube[i][j-1][k])*DTerm*mask[i][j-1][k];
				cube[i][j][k]-=change;
				cube[i][j-1][k]+=change;
				=cube[i][j-1][k];

				change = (cube[i][j][k]-cube[i][j][k+1])*DTerm*mask[i][j][k+1];
				cube[i][j][k]-=change;
				cube[i][j][k+1]+=change;
				=cube[i][j][k+1];

				change = (cube[i][j][k]-cube[i][j][k-1])*DTerm*mask[i][j][k-1];
				cube[i][j][k]-=change;
				cube[i][j][k-1]+=change;
				
				testcube[i-1][j-1][k-1]=cube[i][j][k];
		       }
	        }
    	}

	time = time + timestep;
	double maxval =cube[1][1][1]; 
	double minval =cube[1][1][1];
	/*for (int i=1; i<realsize-1; i++) { 
		for (int j=1; j<realsize-1; j++) { 
			for (int k=1; k<realsize-1; k++) { 
		                maxval = Math.max(cube[i][j][k],maxval);
            			minval = Math.min(cube[i][j][k],minval);	
        		}
   		 }		
	}*/	

	
	for (Double[][] box: cube) {
		for (Double[] line: box){
			for (Double f:line){
				System.out.println(f);/*
			List<Double> x = new ArrayList<Double>();
			x =  Arrays.asList(line);
			maxval = Collections.max(x);
			minval = Collections.min(x);*/
			}
		}
	}
	ratio = minval / maxval;
	//System.out.println(ratio + " time = " + time);

} while ( ratio < 0.99 );
System.out.println( "Box equilibrated in " + time + " seconds of simulated time." );
}
}
