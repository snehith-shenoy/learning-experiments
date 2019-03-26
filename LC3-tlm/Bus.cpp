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

void Bus::set_addr_map(unsigned short low, unsigned short high, uint16 slId)
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
		if(iter->belongs((unsigned short)addr))
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
	std::cout<<"\nSlave: "<<slId<<"\n";
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

//Dummy non-blocking interfaces

tlm::tlm_sync_enum Bus::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& ph , sc_time& delay)
{
	return tlm::TLM_ACCEPTED;
}

tlm::tlm_sync_enum Bus::nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& ph, sc_time& delay)
{
	return tlm::TLM_ACCEPTED;
}

bool Bus::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
	return false; 
}

void Bus::invalidate_direct_mem_ptr(sc_dt::uint64  start_range,sc_dt::uint64  end_range)
{
}

unsigned int Bus::transport_dbg(tlm::tlm_generic_payload& trans)
{
	return 0;
}	
