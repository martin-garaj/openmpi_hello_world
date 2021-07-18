# openmpi_hello_world

Simple _OpenMPI_ hello world program that initializes [main](./source/Process_master.cpp) and [worker](./source/Process_slave.cpp) process on every node. The [main](./source/Process_master.cpp) process is started on node with _world\_rank_ == 0, while the [worker](./source/Process_slave.cpp) is started on every other node.

##### Process class
[Main](./source/Process_master.cpp) and [worker](./source/Process_slave.cpp) processes inherit from [Process](./source/Process.cpp) class.
	- [Process](./source/Process.cpp) class defines the _world communicator_, where the processes exists; this enables to distribute _world\_rank_(s) to every process, thus distinguish [main](./source/Process_master.cpp) and [worker](./source/Process_slave.cpp) process
	
##### COMM_Groups class
[Main](./source/Process_master.cpp) and [worker](./source/Process_slave.cpp) processes inherit from [COMM_Groups](./source/COMM_Groups.hpp) class. 
	- [COMM_Groups](./source/COMM_Groups.hpp) class defines colors of communicators
	
##### Scatter-Work-Gather
The [worker](./source/Process_slave.cpp) processes used traditional Scatter-Work-Gather strategy to split the work load. The _Scatter_ is started by [main](./source/Process_master.cpp) process using _MPI\_Send_ to distribute the data.


##### Sychronization
The [main](./source/Process_master.cpp) process uses _MPI\_Barrier_ to synchronize with [worker](./source/Process_slave.cpp) process. See the image below to see the synchronization in time.


![./openmpi.png](./openmpi.png?raw=true "OpenMPI hello world")
NOTICE: For the matter of exercise, the _worker_ nodes are actually structured, where the highlighted Node 1 has a leading role in data distribution. In practice, this role belongs to the _main_ node.

