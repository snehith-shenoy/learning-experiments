/*
 * Top.h
 * 
 * LC3 Arhitecture Implementation
 * using TLM 2.0
 *
 *  Created on: 26-Mar-2019
 *      Author: Snehith Shenoy
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

		sc_out<bool> nReset, nIRQ;

		// Bus: arg2 = nMasters arg3 = nSlaves
		TopModule(sc_module_name nm, char *fn): sc_module(nm),lc3("LC3"),mem("Memory"),bus("Bus",2,1)
	{

		bus.set_addr_map(0x0,0xFFFF,0); //For memory
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

		nReset(m_rstsig); lc3.m_nReset(m_rstsig);
		nIRQ(m_IRQsig);	lc3.m_nIRQ(m_IRQsig);

		lc3.iport.bind(bus.pSlave[0]);
		lc3.dport.bind(bus.pSlave[1]);

		bus.pMaster[0].bind(mem.memSock);

		std::cout<<"Loading program...\n\nAddress | Data \n"
										 "---------------\n";
		if(!(mem.load(fn)))
			std::cout<<"Error in loading program file!";
	}

private:
		sc_signal<bool> m_rstsig, m_IRQsig;
};




#endif /* TOP_H_ */
