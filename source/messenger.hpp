/*
 * messenger.hpp
 *
 *  Created on: 23 Jun 2017
 *      Author: martin
 */

#ifndef MESSENGER_HPP_
#define MESSENGER_HPP_


//--------------------------------------------------------------//
//							MESSENGER CLASS						//
//--------------------------------------------------------------//
//																//
//	Responsibility to provide communication between MPI			//
//	processes. The main goal is to implement a set of functions	//
//	for communication between master process and slave 			//
//	processes.													//
//																//
//--------------------------------------------------------------//


class Messenger{
public :
	bool send();
	bool receive();


};

#endif /* MESSENGER_HPP_ */
