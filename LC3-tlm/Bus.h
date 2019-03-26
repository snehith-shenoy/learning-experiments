/*
 * Bus.h
 *
 *  Created on: 26-Mar-2019
 *      Author: Snehith Shenoy
*/

#ifndef BUS_H_
#define BUS_H_

#include "Headers.h"

class addrElement{  //Address map of each slave
public:
	unsigned short low;
	unsigned short high;
	int slaveId;
	bool belongs(unsigned short addr)
	{
		if ((low<=addr )&& (addr <= high))
			return true;
		else
			return false;
	}

};

class Bus: public sc_module, public tlm::tlm_bw_transport_if<>, public tlm::tlm_fw_transport_if<> {

	public:

		Bus(sc_module_name nm,unsigned int nMaster,unsigned int nSlave);

		void b_transport(tlm::tlm_generic_payload &, sc_time&);

		tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_time& );
		tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_time&);
		bool get_direct_mem_ptr(tlm::tlm_generic_payload&, tlm::tlm_dmi& );
		void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64 );
		unsigned int transport_dbg(tlm::tlm_generic_payload&);


		void set_addr_map(unsigned short low, unsigned short high, uint16 mPort);
		unsigned int get_addrmap_size(void);



		sc_vector< tlm::tlm_target_socket<16> > pSlave;
		sc_vector<tlm::tlm_initiator_socket<16> > pMaster;
	private:
		std::vector<addrElement> addrMap;
		int get_slave_id(uint16 addr);


};


#endif /* BUS_H_ */
