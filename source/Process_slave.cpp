/*
 * Process_master.cpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */


#include "Process_slave.hpp"
#include "mpi.h"
#include <stdio.h>
#include <string.h>

//================================================================constructor()================================================================//
Process_slave::Process_slave(int rank) : Process(rank){};


//================================================================destructor()================================================================//
Process_slave::~Process_slave(){};


//================================================================init()================================================================//
int Process_slave::init(){
	// sanity check for the minimum amount of processes
	if(this->world_size < PROCESS_FIRST_SLAVE+1){
		printf("ERROR, not enough processes started, no SLAVES");
		MPI_Abort(MPI_COMM_WORLD, 3001);
	}

	// add this process into a MPI_COMM_SLAVE communicator
	MPI_Comm_split(	MPI_COMM_WORLD,							// MPI default world communicator
					COLOR_SLAVE, 							// color of this process in the new communicator
					this->world_rank - PROCESS_FIRST_SLAVE, // rank in the new communicator
					&(this->MPI_COMM_SLAVE)); 				// new communicator from COMM_Groups

	// define the size of MPI_COMM_NON_SLAVE communicator
	MPI_Comm_size(	MPI_COMM_SLAVE, 			// non-default communicator group
					&(this->comm_slave_size));	// variable to store the value
	// assign local ranks within MPI_COMM_NON_SLAVE communicator
	MPI_Comm_rank(MPI_COMM_SLAVE, &(this->local_rank));

	// ALLOCATE MEMORY


	// report to master
	sprintf(this->message, "response from SLAVE %i : local rank : %i in MPI_COMM_SLAVE",this->world_rank, this->local_rank);

	MPI_Send(this->message,				// buffer
			this->message_size, 		// buffer length
			MPI_CHAR,					// buffer data type
			PROCESS_MASTER,				// world_rank of destination process
			TAG_SYNC, 					// message tag
			MPI_COMM_WORLD);			// communicator group



	return PROCESS_SUCCESS;
};



//================================================================run()================================================================//
int Process_slave::run(void){

	// GLOBAL SYNC
	MPI_Barrier(MPI_COMM_WORLD);

// FIRST SLAVE PROCESS receives the data from MASTER
	if(this->world_rank == PROCESS_FIRST_SLAVE){
		printf("SLAVE %i : check the slave communicator size : %i\n",this->world_rank, this->comm_slave_size);
		// receive data from master
		MPI_Recv(this->data, 		// receive buffer
				data_size, 				// max length of receive buffer
				MPI_INT, 			// receive buffer data type
				PROCESS_MASTER, 				// world_rank of sending process
				TAG_DATA,			// message tag
				MPI_COMM_WORLD,		// communicator group
				&status);			// status
	}

// FIRST SLAVE PROCESS MPI_Scatter() to other SLAVEs in MPI_COMM_SLAVE communicator
	MPI_Scatter(this->data,					// send buffer (PROCESS_FIRST_SLAVE)
				10/(this->comm_slave_size),	// number of data per slave
				MPI_INT,					// data type
				this->data_in,				// receive buffer (every other slave)
				10/(this->comm_slave_size),	// number of data per slave
				MPI_INT,					// data type
				PROCESS_FIRST_SLAVE_LOCAL,	// root process sending data
				this->MPI_COMM_SLAVE);		// communicator

	// LOCAL SYNC
	MPI_Barrier(this->MPI_COMM_SLAVE);
	printf("SLAVE %i : data_in : [%i, %i]\n",this->local_rank, this->data_in[0], this->data_in[1]);


// HEAVY WORK !!!===========================================================//
																			//
	data_in[0] = data_in[0] + data_in[1];									//
	data_in[1] = this->local_rank;											//
																			//
	if(this->world_rank == PROCESS_FIRST_SLAVE){							//
		printf("SLAVE %i : HEAVY WORK FOR ALL SLAVES\n",this->world_rank);	//
		printf("SLAVE %i : data cleared\n",this->world_rank);				//
																			//
		for(int i = 0; i < 10; i++){										//
			this->data[i] = 0;												//
		}																	//
																			//
	}																		//
																			//
// HEAVY WORK !!!===========================================================//


// SLAVEs MPI_Gather() to FIRST SLAVE PROCESS
	MPI_Gather(	this->data_in,				// send buffer (PROCESS_FIRST_SLAVE)
				10/(this->comm_slave_size),	// number of data per slave
				MPI_INT,					// data type
				this->data,					// receive buffer (every other slave)
				10/(this->comm_slave_size),	// number of data per slave
				MPI_INT,					// data type
				PROCESS_FIRST_SLAVE_LOCAL,	// root process sending data
				this->MPI_COMM_SLAVE);		// communicator


// FIRST SLAVE PROCESS checks the gathered data
	if(this->world_rank == PROCESS_FIRST_SLAVE){
		printf("SLAVE %i : result : ", this->world_rank);
		for(int i = 0; i < 10; i++){
			printf(" %i,",this->data[i]);
		}
		printf("\n");
	}


	// FINAL GLOBAL SYNC
	MPI_Barrier(MPI_COMM_WORLD);

	return PROCESS_SUCCESS;
};



//================================================================finish()================================================================//
int Process_slave::finish(void){
	// deregister current process from the communicator group
	MPI_Comm_free(&(this->MPI_COMM_SLAVE));
	// DE-ALLOCATE MEMORY

	return PROCESS_SUCCESS;
};

