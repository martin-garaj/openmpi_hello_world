/*
 * COMM_Non_slave.hpp
 *
 *  Created on: 24 Jun 2017
 *      Author: martin
 */

#ifndef COMM_GROUPS_HPP_
#define COMM_GROUPS_HPP_

//----------------------------------------------------------------------------------------------//
//										COMM_Groups.hpp											//
//----------------------------------------------------------------------------------------------//
//																								//
//	This is a base class for any Process that requires the use of non-default communicators. 	//
//	At the moment all communicators and COLORs are defined within this class. Therefore any 	//
//	process inheriting from COMM_Groups can be part of any/all communicators.					//
//																								//
//	All #define(s) regarding communicators (even if specific only for certain communicators) 	//
//	are defined here (inheriting from this class means including the .hpp file, thus gaining 	//
//	scope of #define(s)).																		//
//																								//
//----------------------------------------------------------------------------------------------//

// defines
	#define PROCESS_FIRST_SLAVE_LOCAL	0	// the first slave in local group
	// colors to distinguish communicator groups
	#define COLOR_NON_SLAVE 	0
	#define COLOR_SLAVE			1

// base class
	class COMM_Groups{
	// variables
	public:
		// NON_SLAVE communicator
		MPI_Comm MPI_COMM_NON_SLAVE;	// communicator including NON slaves only
		int comm_non_slave_size;		// size of non slave communicator

		// SLAVE communicator
		MPI_Comm MPI_COMM_SLAVE;	// communicator including NON slaves only
		int comm_slave_size;		// size of non slave communicator

	};

#endif /* COMM_GROUPS_HPP_ */
