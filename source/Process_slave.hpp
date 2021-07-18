/*
 * Process_slave.hpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */

#ifndef PROCESS_SLAVE_HPP_
#define PROCESS_SLAVE_HPP_

#include "Process.hpp"
#include "COMM_Groups.hpp"
#include "mpi.h"

class Process_slave : 	public Process,		// inherits Process, because this object defines specific Process
						public COMM_Groups 	// inherits from COMM_Groups, the Process_master uses specific non-default communicator
{
public:

public:
	Process_slave(int rank);
	~Process_slave();
	int init(void);
	int run(void);
	int finish(void);

};



#endif /* PROCESS_SLAVE_HPP_ */
