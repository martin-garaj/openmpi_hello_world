/*
 ============================================================================
 Name        : OpenMPI_test_v0_1.c
 Author      : Martin Garaj
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <string.h>
#include "mpi.h"

#include "Process.hpp"
#include "Process_master.hpp"
#include "Process_slave.hpp"

int main(int argc, char* argv[]){

	int world_rank;

	// start MPI
	MPI_Init(&argc, &argv);

	// get this process world_rank
	MPI_Comm_rank(MPI_COMM_WORLD, &(world_rank));
//--------------------------------------MASTER--------------------------------------//
	if(world_rank == PROCESS_MASTER){
		Process_master master(PROCESS_MASTER);
		master.init();
		master.run();
		master.finish();

//--------------------------------------SLAVE--------------------------------------//
	}else{
		Process_slave slave(world_rank);
		slave.init();
		slave.run();
		slave.finish();
	}

	// MASTER END
	if(world_rank == PROCESS_MASTER){
		printf("END : %i\n",world_rank);
	}

	// shut-down MPI
	MPI_Finalize(); 
	
	return 0;
}
