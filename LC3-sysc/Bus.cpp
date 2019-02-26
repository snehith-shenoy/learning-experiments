/*
 * Bus.cpp
 *
 *  Created on: 25-Feb-2019
 *      Author: vayavya
 */

#include "Bus.h"

void Bus::set_addr_map(uint16 low, uint16 high, uint slId)
{
	addrMap temp;
	temp.low=low;
	temp.high=high;
	temp.slaveId=slId;
	amap.push_back(temp);
}

int Bus::get_slave_id(uint16 addr)
{
	for(auto iter=amap.begin();iter!=amap.end();iter++)
	{
		if(iter->belongs(addr))
			{
//			std::cout<<"Trans address:"<<std::hex<<addr<<" Sl. ID: "<<(*iter).slaveId<<std::endl;
			return iter->slaveId;
			}

	}		return -1;
}

Bus::status_t Bus::read(uint16 addr, uint16 &data)
{
	int slId = get_slave_id(addr);
//	cout<<"Calling read in Bus"<<"for Slave "<<slId<<std::endl;
	if (slId>=0)
		return(pMaster[slId]->read(addr,data));
	else
		return BUS_ERROR;
}

Bus::status_t Bus::write(uint16 addr,uint16 data)
{
	int slId = get_slave_id(addr);
	if (slId>=0)
		return(pMaster[slId]->write(addr,data));
	else
		return BUS_ERROR;
}
