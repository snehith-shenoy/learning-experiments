/*
 * Bus.h
 *
 *  Created on: 14-Mar-2019
 *      Author: snehiths
*/

#ifndef BUS_H_
#define BUS_H_

#include "Headers.h"

class addrElement{  //Address map of each slave
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

class Bus: public sc_module, public tlm::tlm_bw_transport_if<>, public tlm::tlm_fw_transport_if<> {

	public:

		Bus(sc_module_name nm,unsigned int nMaster,unsigned int nSlave);

		void b_transport(tlm::tlm_generic_payload &, sc_time&);

		tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& ph , sc_time& delay){ return tlm::TLM_ACCEPTED;}
		tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& ph, sc_time& delay){ return tlm::TLM_ACCEPTED;}
		bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data){ return false; }
		void invalidate_direct_mem_ptr(sc_dt::uint64  start_range,sc_dt::uint64  end_range){}
		unsigned int transport_dbg(tlm::tlm_generic_payload& trans){ return 0;}	


		void set_addr_map(uint16 low, uint16 high, uint mPort);
		unsigned int get_addrmap_size(void);



		sc_vector< tlm::tlm_target_socket<16> > pSlave;
		sc_vector<tlm::tlm_initiator_socket<16> > pMaster;
	private:
		std::vector<addrElement> addrMap;
		int get_slave_id(uint16 addr);


};


#endif /* BUS_H_ */
