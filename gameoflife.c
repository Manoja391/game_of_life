//Author: Manoja Putta
//**  Email: manoja@uab.edu
//**  Date: Febraury 3, 2021
//Course Section :  CS 632
//Homework # :
//Instructions to compile the program : (for example: gcc -std=c99 O3 game gameoflife.c)
//Instructions to run the program : (for example: ./game 1000 1000)

#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>


double gettime() {
    struct timeval tval;

    gettimeofday(&tval, NULL);

     return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
     }

int main( int argc, char* argv[])
{

//initialization of main and temporary arrays
  int **grid, **temp;

	int size = atoi (argv[1]);
  int generation =atoi (argv[2]);

    // dynamic memory allocation of arrays
	grid = (int**)malloc((size + 2) * sizeof(int*));
  temp= (int**)malloc((size + 2) * sizeof(int*));


  //timestarts
	double starttime = gettime();
	int l;
  for (l = 0;l<size + 2;l++){
      grid[l] = (int*)malloc((size + 2) * sizeof(int));
      temp[l] = (int*)malloc((size + 2) * sizeof(int));
	}
  **grid = insertelementstoarray(size,grid);
int a;
  for (a = 0; a < generation; a++)
    {
        //To check neighbour elements state
		**grid = countneighbours(size,grid,temp);
		if(grid==0){
            generation=1;
		}
		//dispArray(size, grid);
	}

double endtime = gettime();

printf("Time taken = %lf seconds\n", endtime-starttime);
return 0;

}


int countneighbours(int size, int **grid, int **temp){

//check all neighbors of the cell
int position;

 int i;
 int j;
 int x;
 int y;

	for(i=0;i<size+2;i++){

      for(j=0;j<size+2;j++){

        position = grid[i][j];
        if(i == 0 || i== size+1 || j == 0|| j== size+1){
          //ignnoring the edges.
          temp[i][j]=position;

        }
        else{
            int neighbourexist = 0;
            for(x=-1;x<2;x++){

              for(y=-1;y<2;y++){

                neighbourexist += grid[x+i][y+j];
              }
            }
            neighbourexist -= grid[i][j];
            if(position==1){
                if(neighbourexist<2 || neighbourexist>3){
              //each state of a cell changes to Dead by lonliness or overpopulation.
              temp[i][j] = 0;
            }
            else if(neighbourexist==2 || neighbourexist==3){
              //Each state of a cell changes to Live .
              temp[i][j] = 1;
            }
            else{
              //otherwise it reamins same for next generation.
              temp[i][j] = grid[i][j];
            }
        }
        else if(position==0){
            if(neighbourexist==3){
              //Each state of a cell changes to Live .
              temp[i][j] = 1;
            }
            else{
                temp[i][j] = grid[i][j];
            }
        }
      }
    }
	}

	int arraychk=0;
	int m,n;

            for(int m=0;m<size+2;m++)
                {
                for(int n=0;n<size+2;n++)
                    {
            //comparing the elements of two arrays
                if(grid[m][n] != temp[m][n]) {
                            arraychk =1;
                    }
                    grid[m][n]=temp[m][n];
                    }
                }

        if(arraychk==1)
            {
                return **grid;
            }
        else{
                return 0;
            }
}



int insertelementstoarray(int size, int **grid)
{
    int i,j;
	for(i=0;i < size + 2;i++){
      for(j=0;j< size + 2;j++){
          grid[i][j]=rand()%2;
          if(i == 0 || i== size+1 || j == 0|| j== size+1){
            grid[i][j]= 0;
          }
      }
    }

	return **grid;
}


int dispArray(int size,int **grid)//function to display
{
    int i,j;

    //print all the stuff that's been pushed into our array
    for(i=0;i<=size+1;i++){
		printf("\n");
		for(j=0;j<=size+1;j++)
		{
			printf("%d ",grid[i][j]);
		}
	}

  return 0;
}
