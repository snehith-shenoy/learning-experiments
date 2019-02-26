#ifndef __LC3_h__
#define __LC3_H__


#include <vector>
#include <bitset>
#include "bus_if.h"



#define LC3_NUM_REGS 8
typedef unsigned short uint16;

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
  OP_LEA,		   // Load Effective Address: DR=PC +SEXT(PCoffset9)
  OP_LDI,          // DR = mem[mem[PCi + PCoffset9]]
  OP_STI,          // mem[mem[PCi + offset9]] = SR
  OP_JMP_RET,      // PC = R7 (RET) or PC = Rx (JMP Rx)
  OP_RESERVED,     // Currently not used
  OP_TRAP
} opcode_t;


class LC3: public sc_module {
	public:

	SC_HAS_PROCESS(LC3);
	sc_port<bus_if> iport; //Instruction access port, only reads
	sc_port<bus_if> dport; // Data access port, read/write, load-store

	LC3(sc_module_name);

	~LC3(){}
	private:
	void reset(); //Resets LC3: R0-R7, PC=0 and clear all flags
	void step(); // Forward ISS: Fetch > Decode > Execute

//  Flags of PSR
//	bool m_privilege;
//	bool m_priority;
	bool m_N;
	bool m_Z;
	bool m_P;

	uint16 m_PC;

	std::vector<uint16> m_R;

	uint16 SEXT(int n, uint16 data);
	opcode_t get_opcode(uint16 inst);
	void dec_and_exec(uint16 instruction);

	void setcc(uint16 result);

};

#endif
