/*
 * Top.h
 * 
 * LC3 Arhitecture Implementation
 * using TLM 2.0
 *
 *  Created on: 14-Mar-2019
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
		TopModule(sc_module_name nm, char *fn): sc_module(nm),lc3("LC3"),mem("Memory"),bus("Bus",2,1)
	{

		bus.set_addr_map(0x3000,0xFFFF,0); //For memory
//		bus.set_addr_map(0,0x3000,1); //Dummy; to test address map mismatch
	
		if(bus.pMaster.size() == bus.get_addrmap_size())
		{
			std::cout<<"\nAddress map set!\n\n";
		}
		else
		{
			std::cout<<"\nWarning! Address map mismatches the slaves connected to bus"<<std::endl;
			std::cout<<bus.name()<<" has "<<bus.pMaster.size()<<" slave(s) and "<<bus.get_addrmap_size()<<" address map(s) set\n"<<std::endl;
		}

		//Binding

		lc3.iport.bind(bus.pSlave[0]);
		lc3.dport.bind(bus.pSlave[1]);
		bus.pMaster[0].bind(mem.memSock);

		if(!(mem.load(fn)))
			std::cout<<"Error in loading program file!";
	}

};




#endif /* TOP_H_ */
