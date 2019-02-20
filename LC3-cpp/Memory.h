#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "bus_if.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include <bitset>


#define MEM_SIZE 0xFFFF

typedef unsigned short uint16;

using namespace std;

class Memory: public bus_if
{
public:
	virtual status_t read(uint16 addr , uint16 &data);
	virtual status_t write(uint16 addr, uint16 data);

	bool load(std::string file_name);

	Memory():dataMem(MEM_SIZE) {}
	~Memory(){}

private:
	std::vector<uint16> dataMem ;
};


#endif
