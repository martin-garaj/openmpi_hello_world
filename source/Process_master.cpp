/*
 * Process_master.cpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */


#include "Process_master.hpp"
#include "mpi.h"
#include <stdio.h>
#include <string.h>

Process_master::Process_master(int rank) : Process(rank){};
Process_master::~Process_master(){};

int Process_master::init(){
	// sanity check for the minimum amount of processes
	if(this->world_size < PROCESS_FIRST_SLAVE+1){
		printf("ERROR, not enough processes started, no SLAVES");
		MPI_Abort(MPI_COMM_WORLD, 3001);
	}

	// add this process into a MPI_COMM_NON_SLAVE communicator
	MPI_Comm_split(	MPI_COMM_WORLD,					// MPI default world communicator
					COLOR_NON_SLAVE, 				// color of this process in the new communicator
					this->world_rank, 				// rank in the new communicator
					&(this->MPI_COMM_NON_SLAVE)); 	// new communicator from COMM_Groups

	// define the size of MPI_COMM_NON_SLAVE communicator
	MPI_Comm_size(	MPI_COMM_NON_SLAVE, 			// non-default communicator group
					&(this->comm_non_slave_size));	// variable to store the value
	// assign local ranks within MPI_COMM_NON_SLAVE communicator
	MPI_Comm_rank(MPI_COMM_NON_SLAVE, &(this->local_rank));

	// ALLOCATE MEMORY
	// master may/may not allocate memory


	// listen for an answer from all processes (registered as slaves)
	printf("MASTER %i : world_size: %i\n",this->world_rank, this->world_size);
	for (int rank = PROCESS_FIRST_SLAVE; rank < this->world_size; rank++)
	{
		// BLOCKING
		MPI_Recv(this->message, 	// receive buffer
				message_size, 		// max length of receive buffer
				MPI_CHAR, 			// receive buffer data type
				rank, 				// world_rank of sending process
				TAG_SYNC,			// message tag
				MPI_COMM_WORLD,		// communicator group
				&status);			// return status
		printf("%s\n",message);
	}

	// print information
	printf("MASTER %i : check the non_slave communicator size : %i\n",this->world_rank, this->comm_non_slave_size);




	return PROCESS_SUCCESS;
};


int Process_master::run(void){

	// GLOBAL SYNC
	MPI_Barrier(MPI_COMM_WORLD);

	// send data to the first slave process
	printf("MASTER %i : SEND to first slave\n",this->world_rank);
	MPI_Send(this->data,				// buffer
			data_size,					// buffer length
			MPI_INT,					// buffer data type
			PROCESS_FIRST_SLAVE,		// world_rank of destination process
			TAG_DATA, 					// message tag
			MPI_COMM_WORLD);			// communicator group





	// FINAL GLOBAL SYNC
	MPI_Barrier(MPI_COMM_WORLD);


	return PROCESS_SUCCESS;
};


int Process_master::finish(void){
	// deregister current process from the communicator group
	MPI_Comm_free(&(this->MPI_COMM_NON_SLAVE));
	// DE-ALLOCATE MEMORY
	// master may/may not allocate memory
	return PROCESS_SUCCESS;
};

