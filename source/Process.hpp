/*
 * process.hpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include "mpi.h"

// these constants are known to every process
	// definition of MPI processes in world communicator scope
	// processes with specific role
	#define PROCESS_MASTER				0
	#define PROCESS_DEBUG				1
	#define PROCESS_AUXILIARY			2
	// all other processes are SLAVES
	#define PROCESS_FIRST_SLAVE			1	// the first slave
// return values
	#define PROCESS_SUCCESS				1
	#define PROCESS_ERROR				0

// message tags
	#define TAG_SYNC					0
	#define TAG_DATA					1

// base class for every process
	class Process {
		// every process has to utilize following variables
	public:
		int world_rank; 				// the id of process in MPI_COMM_WORLD communicator
		int local_rank;					// the id of process in comm_slave communicator
		int world_size;       			// world communicator size
		int tag;						// message tag
		MPI_Status status;   			// receive status for MPI_Recv

		// debugging
		char message[100];       				// storage
		const int message_size = 100;			// storage size
		int data[10] = {0,1,2,3,4,5,6,7, 8, 9};	// data
		const int data_size = 10;			// storage size
		int data_in[2];							// receive data buffer

		// every process has to define following functions
	public:
		virtual int init(void){};
		virtual int run(void){};
		virtual int finish(void){};

		Process(int rank);
		virtual ~Process();
	};

#endif /* PROCESS_HPP_ */
