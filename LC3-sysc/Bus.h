/*
 * Bus.h
 *
 *  Created on: 25-Feb-2019
 *      Author: snehiths
 */

#ifndef BUS_H_
#define BUS_H_

#include "bus_if.h"

class addrMap{  //Address map of each slave
public:
	uint16 low;
	uint16 high;
	int slaveId;
	bool belongs(uint16 addr)
	{
		if ((low<=addr )&& (addr <= high))
			return true;
		else
			return false;
	}

};

class Bus: public sc_channel, public bus_if {

public:

	Bus(sc_module_name nm,unsigned int nMaster,unsigned int nSlave);

	status_t read(uint16 addr, uint16 &data);
	status_t write(uint16 addr,uint16 data);

	void set_addr_map(uint16 low, uint16 high, uint mPort);
	int get_slave_id(uint16 addr);


	std::vector<sc_export<bus_if>> pSlave;
	std::vector<sc_port<bus_if>> pMaster;

	std::vector<addrMap> amap;

};


#endif /* BUS_H_ */
