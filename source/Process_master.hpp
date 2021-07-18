/*
 * Process_master.hpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */

#ifndef PROCESS_MASTER_HPP_
#define PROCESS_MASTER_HPP_

#include "Process.hpp"
#include "COMM_Groups.hpp"
#include "mpi.h"

class Process_master : 	public Process,		// inherits Process, because this object defines specific Process
						public COMM_Groups 	// inherits from COMM_Groups, the Process_master uses specific non-default communicator
{
public:

public:
	Process_master(int rank);
	~Process_master();
	int init(void);
	int run(void);
	int finish(void);

};



#endif /* PROCESS_MASTER_HPP_ */
