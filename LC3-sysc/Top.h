/*
 * Top.h
 *
 *  Created on: 25-Feb-2019
 *      Author: snehiths
 */

#ifndef TOP_H_
#define TOP_H_

#include "Memory.h"
#include "LC3.h"
#include "Bus.h"

class TopModule: public sc_module{

	public:
    LC3 lc3;
    Memory mem;
    Bus bus;

	// Bus: arg2 = nMasters arg3 = nSlaves
        TopModule(sc_module_name nm, char *fn): sc_module(nm),lc3("LC3"),mem("Memory"),bus("bus",2,1)
	{

	//     set_addr_map(uint16 low, uint16 high, uint16 slaveId);
    bus.set_addr_map(0x3000,0xFFFF,0);
    std::cout<<"Address map set!"<<std::endl;

	//Binding
<<<<<<< HEAD

	lc3.iport(bus.pSlave[0]);
	lc3.dport(bus.pSlave[1]);
	bus.pMaster[0](mem.memPort);
	std::cout<<"Bound!"<<std::endl;
=======
	lc3.iport(bus);
	lc3.dport(bus);
	bus.pMaster[0](mem);
>>>>>>> a39fc1a8e762bd3817f8274c0946c4c97eddde33
 	if(!(mem.load(fn)))
		std::cout<<"Error in loading program file!";
	}

};




#endif /* TOP_H_ */
