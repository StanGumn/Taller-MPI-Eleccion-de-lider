#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#define BUFSIZE 128
#define TAG 0


void main(int argc, char* argv[]) { 
	int numero, idlider, numprocs, myid, i;
	char buff[BUFSIZE], auxbuff[BUFSIZE], *ptr;
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	srand(MPI_Wtime()*1000000);
	numero = rand()%100+1;

	idlider = myid;
	printf("%d: %d\n",myid, numero);
		
	for(i=0;i<numprocs;i++){
		if (myid!=i){
			sprintf(buff, "%d.%d\n", numero,myid);
			MPI_Send(buff, BUFSIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD);
		}
	}
	
	for(i=0;i<numprocs;i++){
		if (myid!=i){
			MPI_Recv(buff, BUFSIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD, &stat);
			strcpy(auxbuff,buff);
			ptr = strtok(auxbuff,".");
			
			if (numero <= atoi(ptr)){
				numero = atoi(ptr);
				ptr = strtok(NULL, ".");
				idlider = atoi(ptr);
			}
		}
	}

	printf("\n%d: El lider es %d con el numero %d\n", myid, idlider, numero);
	MPI_Finalize();
	
}
