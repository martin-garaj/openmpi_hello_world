/*
 * Process.cpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */

#include "Process.hpp"
#include "mpi.h"

Process::Process(int rank){
	// get the number of all MPI processes
	MPI_Comm_size(	MPI_COMM_WORLD, 		// MPI default world communicator
					&(this->world_size));	// Process base variable
	this->world_rank = rank;
	this->local_rank = 0;
	this->tag = 0;
};

Process::~Process(){

};

