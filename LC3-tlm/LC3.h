/*
 * LC3.h
 *
 *  Created on: 26-Mar-2019
 *      Author: Snehith Shenoy
 */

#ifndef __LC3_h__
#define __LC3_H__


#include <vector>
#include <bitset>
#include "Headers.h"
#include <iostream>

#define LC3_NUM_REGS 9

typedef enum opcode {

	OP_BR,           // PC = PCi + PCoffset9 if condition is met
	OP_ADD,          // DR = SR1 + SR2 or DR = SR1 + imm5
	OP_LD,           // DR = mem[PCi + PCoffset9]
	OP_ST,           // mem[PCi + PCoffset9] = SR
	OP_JSR_JSRR,     // R7 = PCi and (PC = SR or PC = PCi + PCoffest9)
	OP_AND,          // DR = SR1 & SR2
	OP_LDR,          // DR = mem[BaseR + offset6]
	OP_STR,          // mem[BaseR + offset6] = SR
	OP_RTI,          // PC = R7, exit supervisor mode
	OP_NOT,          // DR = ~SR1
	OP_LDI,          // DR = mem[mem[PCi + PCoffset9]]
	OP_STI,          // mem[mem[PCi + offset9]] = SR
	OP_JMP_RET,      // PC = R7 (RET) or PC = Rx (JMP Rx)
	OP_RESERVED,     // Currently not used
	OP_LEA,		  	 // Load Effective Address: DR=PC +SEXT(PCoffset9)
	OP_TRAP
} opcode_t;


class LC3: public sc_module, public tlm::tlm_bw_transport_if<> {

	public:

		SC_HAS_PROCESS(LC3);

		tlm::tlm_initiator_socket<16> 	iport; //Instruction access socket, only reads
		tlm::tlm_initiator_socket<16> 	dport; // Data access port, read/write, load-store
		sc_in<bool> m_nReset, m_nIRQ; // Reset and IRQ signals
		LC3(sc_module_name);

	~LC3(){}

// Bw interface
	tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload&, tlm::tlm_phase&, sc_time&);
	void invalidate_direct_mem_ptr(sc_dt::uint64, sc_dt::uint64);

	private:
	void reset(); //Resets LC3: R0-R7, PC=0 and clear all flags
	void step(); // Forward ISS: Fetch > Decode > Execute

// 	Flags of PSR
	bool m_privilege;
	bool m_priority;
	bool m_N;
	bool m_Z;
	bool m_P;

	uint16 m_PC;
	std::vector<uint16> m_R;

	bool m_acceptIRQ;
	sc_process_handle step_handle;

	uint16 SEXT(int n, uint16 data);
	opcode_t get_opcode(uint16 inst);
	void dec_and_exec(uint16 instruction);

	void setcc(uint16 result);

};

#endif
