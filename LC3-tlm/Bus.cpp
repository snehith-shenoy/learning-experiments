/*
 * Bus.cpp
 *
 *  Created on: 14-Mar-2019
 *      Author: snehiths
 */

#include "Bus.h"

Bus::Bus(sc_module_name nm,unsigned int nMaster,unsigned int nSlave):sc_module(nm),
	pSlave("Bus_Target_Sockets",nMaster),
	pMaster("Bus_Init_Sockets", nSlave)

{

	for(unsigned int i=0; i<nMaster; i++)
	{
		pSlave[i].bind(*this);
	}
	for(unsigned int i=0; i<nSlave; i++)
	{
		pMaster[i].bind(*this);
	}

}

void Bus::set_addr_map(uint16 low, uint16 high, uint slId)
{
	addrElement temp;
	temp.low=low;
	temp.high=high;
	temp.slaveId=slId;
	addrMap.push_back(temp);
}


unsigned int Bus::get_addrmap_size()
{
	return addrMap.size();
	
}
int Bus::get_slave_id(uint16 addr)
{
	for(auto iter=addrMap.begin();iter!=addrMap.end();iter++)
	{
		if(iter->belongs(addr))
		{
			return iter->slaveId;
		}

	}		return -1;
}

void Bus::b_transport(tlm::tlm_generic_payload &trans, sc_time& delay)
{
	
	int slId = get_slave_id((uint16)trans.get_address());
#if 0
	std::cout<<"\nBus recieved address: "<<std::hex<<(uint16)trans.get_address()<<"\n";
	std::cout<<"\nBus recieved data ptr: "<<std::hex<<(uint16 *)trans.get_data_ptr()<<"\n";
#endif
	if (slId>=0)
	{
		pMaster[slId]->b_transport(trans, delay);
	}
	else
	{
		trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
	}
}

