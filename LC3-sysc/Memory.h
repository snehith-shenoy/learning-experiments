#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "bus_if.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include <bitset>
#include "systemc.h"

#define MEM_SIZE 0xFFFF

typedef unsigned short uint16;

using namespace std;

class Memory: public bus_if, public sc_module {
public:

	sc_export<bus_if> memPort;
	virtual status_t read(uint16 addr, uint16 &data)
	{

			data = dataMem[addr];
			return BUS_OK;

	}

	virtual status_t write(uint16 addr, uint16 data)
	{
			dataMem[addr] = data;
			return BUS_OK;
	}


	bool load(std::string file_name);

	Memory(sc_module_name);
	~Memory(){}

private:
	std::vector<uint16> dataMem ;
};


#endif
