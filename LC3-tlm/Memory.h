/*
 * Memory.h
 *
 *  Created on: 14-Mar-2019
 *      Author: snehiths
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "Headers.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>
#include <bitset>

#define MEM_SIZE 0xFFFF
#define READ_DELAY 10,SC_NS
#define WRITE_DELAY 5,SC_NS


class Memory: public sc_module,  public tlm::tlm_fw_transport_if<> {
public:

	tlm::tlm_target_socket<16> memSock;

	Memory(sc_module_name);
	~Memory(){}

	bool load(std::string file_name);
	
	void b_transport(tlm::tlm_generic_payload&, sc_time& );	
	tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_time&);
	bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi&);
	unsigned int transport_dbg(tlm::tlm_generic_payload&);

private:
	std::vector<uint16> dataMem ;
};


#endif
