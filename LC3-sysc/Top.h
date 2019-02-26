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

	// Bus: arg2 = nMasters arg3 = nSlaves
        TopModule(sc_module_name nm, char *fn): sc_module(nm),lc3("LC3"),mem("Memory"),bus("bus",2,1)
	{

	//     set_addr_map(uint16 low, uint16 high, uint16 slaveId);
	std::cout<<"Setting address map.."<<std::endl;

    bus.set_addr_map(0x3000,0xFFFF,0);

	//Binding
	lc3.iport(bus);
	lc3.dport(bus);
	bus.pMaster[0](mem);
 	if(!(mem.load(fn)))
		std::cout<<"Error in loading program file!";
	}


      LC3 lc3;
      Memory mem;
      Bus bus;
};




#endif /* TOP_H_ */
