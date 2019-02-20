#include "LC3.h"

#define DR_MASK 0xE00
#define SR1_MASK 0x1C0
#define SR2_MASK 0x7

#define IMM5_MASK 0x1F
#define IMM6_MASK 0x3F
#define IMM9_MASK 0x1FF
#define IMM11_MASK 0xFFF

#define n_MASK 0x800
#define z_MASK 0x400
#define p_MASK 0x200

#define RET_MASK 0x1C0
#define JSR_MASK 0x800
#define BREG_MASK 0x1C0

void LC3::setcc(uint16 result)
{
	if (result==0)
	{
		m_Z=1; m_N=0; m_P=0;
	}
	else if (result<0)
	{
		m_Z=0; m_N=1; m_P=0;
	}
	else
		m_Z=0; m_N=0; m_P=1;
}

opcode_t LC3::get_opcode(uint16 inst)
{
	switch(inst & 0xF000)
		{
			case 0x0000: return OP_BR;
			case 0x1000: return OP_ADD;
			case 0x2000: return OP_LD;
			case 0x3000: return OP_ST;
			case 0x4000: return OP_JSR_JSRR;
			case 0x5000: return OP_AND;
			case 0x6000: return OP_LDR;
			case 0x7000: return OP_STR;
			case 0x8000: return OP_RTI;
			case 0x9000: return OP_NOT;
			case 0xA000: return OP_LDI;
			case 0xB000: return OP_STI;
			case 0xC000: return OP_JMP_RET;
			case 0xD000: return OP_RESERVED;
			case 0xE000: return OP_LEA;
			case 0xF000: return OP_TRAP;
			default: std::cout<<"Error in decoding opcode";
					 exit(0);

		}
}

void LC3::dec_and_exec(uint16 inst)
{
//using namespace LC3;
	switch(get_opcode(inst))
	{
	case  OP_BR:         // PC = PCi + PCoffset9 if condition is met
	{
		if ( (m_N&(inst&n_MASK)) || (m_Z&(inst&z_MASK)) || (m_P&(inst&p_MASK)))

			m_PC+= SEXT(7,inst&IMM9_MASK);
		break;
	}

	case  OP_ADD: // DR = SR1 + SR2 or DR = SR1 + imm5
		{
			if(inst & 0x20){
				m_R[(inst&DR_MASK)>>9]= m_R[(inst & SR1_MASK)>>6] + SEXT(11,inst & IMM5_MASK);
				std::cout<<"Using IMM5 value because:"<<std::hex<<(inst & 0x20)<<std::endl;}
			else
			{
				m_R[(inst&DR_MASK)>>9]= m_R[(inst & SR1_MASK)>>6] + m_R[inst & SR2_MASK];}
			setcc(m_R[(inst&DR_MASK)>>9]);
			std::cout<<"OP_ADD result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
			break;
		}

	case OP_AND:          // DR = SR1 & SR2 or DR = SR1 & imm5
	{
		if(inst & 0x20)
			m_R[(inst&DR_MASK)>>9]= m_R[(inst& SR1_MASK)>>6] & SEXT(11,inst & IMM5_MASK);
		else
			m_R[(inst&DR_MASK)>>9]= m_R[(inst & SR1_MASK)>>6] & m_R[inst & SR2_MASK];
		std::cout<<"OP_AND result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		setcc(m_R[(inst&DR_MASK)>>9]);
		break;
	}


	case OP_NOT:          // DR = ~SR1
	{
		m_R[(inst&DR_MASK)>>9]= ~(m_R[(inst & SR1_MASK)>>6]);
		std::cout<<"OP_NOT result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		setcc(m_R[(inst&DR_MASK)>>9]);
		break;
	}

	case OP_LD:           // DR = mem[PCi + PCoffset9]
	{
		uint16 data;

		dport->read(m_PC+SEXT(7,inst & IMM9_MASK),data);
		std::cout<<"Loading data from M"<<std::hex<<m_PC+SEXT(7,inst & IMM9_MASK)<<std::endl;
		m_R[(inst&DR_MASK)>>9]=data;
		setcc(m_R[(inst&DR_MASK)>>9]);
		std::cout<<"OP_LD result: "<<std::hex<<data<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		break;
	}

	case OP_ST:           // mem[PCi + PCoffset9] = SR
	{
		//bus_if::status_t trans;
		//trans=
				dport->write(m_PC+SEXT(7,inst & IMM9_MASK),m_R[(inst&DR_MASK)>>9] );
				std::cout<<"OP_ST result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at M"<<std::hex<<m_PC+SEXT(7,inst & IMM9_MASK)<<std::endl;
				break;
	}

	case OP_JSR_JSRR:     // R7 = PCi and (PC = SR or PC = PCi + PCoffest9)
	{
		uint16 TEMP = m_PC;

		if(inst&JSR_MASK)
			m_PC=m_PC + SEXT(5,inst&IMM11_MASK);
		else
			m_PC= m_R[(inst&BREG_MASK)>>6];

		m_R[7]= TEMP;
		break;

	}

	case OP_LDR:          // DR = mem[BaseR + offset6]
	{
		uint16 data;
		//bus_if::status_t trans;
		//trans=
				dport->read(m_R[(inst&BREG_MASK)>>6]+SEXT(10,inst&IMM6_MASK), data);
		m_R[(inst&DR_MASK)>>9]=data;
		setcc(data);
		std::cout<<"OP_LEA result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		break;
	}

	case OP_STR:          // mem[BaseR + offset6] = SR
	{
		//bus_if::status_t trans;
		//trans=
		dport->write(m_R[(inst&BREG_MASK)>>6]+SEXT(10,inst&IMM6_MASK),m_R[(inst&DR_MASK)>>9]);
		break;
	}

	case OP_RTI:          // PC = R7: exit supervisor mode
	{
		//Pending
		break;
	}

	case OP_LEA:
	{
		m_R[(inst&DR_MASK)>>9]=m_PC+SEXT(7,inst&IMM9_MASK);
		setcc(m_R[(inst&DR_MASK)>>9]);
		std::cout<<"OP_LEA result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		break;
	}

	case OP_LDI:          // DR = mem[mem[PCi + PCoffset9]]
	{
		uint16 data;
		//bus_if::status_t trans;
		//trans=
		dport->read(m_R[m_PC+SEXT(7,inst&IMM9_MASK)], data);
		m_R[(inst&DR_MASK)>>9]=data;
		setcc(data);
		std::cout<<"OP_LDI result: "<<std::hex<<data<<" at R"<<((inst&DR_MASK)>>9)<<std::endl;
		break;
	}

	case OP_STI:          // mem[mem[PCi + offset9]] = SR
	{
		uint16 tempaddr;
		//bus_if::status_t trans;
		//trans=
				dport->read(m_PC+SEXT(7,inst&IMM9_MASK),tempaddr);

		//trans=
				dport->write(tempaddr,m_R[(inst&DR_MASK)>>9]);
				std::cout<<"OP_LDI result: "<<std::hex<<m_R[(inst&DR_MASK)>>9]<<" at M"<<std::hex<<tempaddr<<std::endl;
		break;
	}

	case OP_JMP_RET:      // PC = R7 (RET) or PC = Rx (JMP Rx)
	{
		if((inst&BREG_MASK)==0x1C0)
			m_PC= m_R[7];
		else
			m_PC= m_R[(inst&BREG_MASK)>>6]; //JMP
		break;


	}
	case OP_RESERVED:
	{
		std::cout<<"Illegal OPCODE!";
		exit(0);
		//break;
	}
	case OP_TRAP:
	{
		//Pending
		exit(0);
		//break;
	}
	}



}

void LC3::step()
{
	uint16 instruction;
	//bus_if::status_t trans;
	//trans=
	iport->read(m_PC, instruction);
	m_PC++;
	dec_and_exec(instruction);
	std::cout<<"OPCODE: "<< get_opcode(instruction)<<std::endl;
}

void LC3::reset()
{

	m_PC=0; //Reset PC
	std::fill(m_R.begin(), m_R.end(), 0); //Reset R0-R7

	//Reset PSR flags
	//m_privilege =0;
	//m_priority =0;
	m_N = 0; m_Z = 0; m_P = 0;
}

uint16 LC3::SEXT(int num_bits, uint16 immediate)
{
	if(num_bits==11 && (immediate & 0x10)) {
		std::cout<<"IMM5 val: "<<std::hex<<immediate<<" SignExtended: "<<std::hex<<(immediate | 0xFFE0)<<std::endl;
				return (immediate | 0xFFE0);
	}
	else if(num_bits==10 &&  (immediate & 0x20)) return (immediate | 0xFFC0);
	else if(num_bits==7 && (immediate & 0x100))
		{
			std::cout<<"Returned extended IMM9"<<std::endl;
			return (immediate | 0xFE00);
		}
	else if(num_bits==5 && (immediate & 0x800)) return (immediate | 0xF000);
	else return immediate;
}
