/*
 * Memory.cpp
 *
 *  Created on: 14-Mar-2019
 *      Author: Snehith Shenoy
 */

#include "Memory.h"


Memory::Memory(sc_module_name nm): sc_module(nm),dataMem(MEM_SIZE)
{
	memSock.bind(*this);
	std::cout<<"\nNote: Memory has READ latency of "<<READ_DELAY<<"ns and WRITE latency of "<<WRITE_DELAY<<"ns\n";
}

void Memory::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{

	uint16 * dataPtr = (uint16 *)trans.get_data_ptr();
	uint16 addr = (uint16)trans.get_address();

	switch(trans.get_command())
	{
		case tlm::TLM_READ_COMMAND: 
			{
				*dataPtr = dataMem[addr];

				wait(READ_DELAY,SC_NS); //Read latency
				trans.set_response_status(tlm::TLM_OK_RESPONSE);
				break;
			}

		case tlm::TLM_WRITE_COMMAND:
			{
				dataMem[addr] = *dataPtr;
				wait(WRITE_DELAY,SC_NS); //Write latency
				trans.set_response_status(tlm::TLM_OK_RESPONSE);
				break;	
			}


		default:
			trans.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
	}

}
tlm::tlm_sync_enum Memory::nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& ph , sc_time& delay)
{
	return tlm::TLM_ACCEPTED;
}
bool Memory::get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
{
	return false; 
}
unsigned int Memory::transport_dbg(tlm::tlm_generic_payload& trans)
{
	return 0;
}	


bool Memory::load (std::string file_name)
{
  unsigned int i = 1;
  ifstream obj;
  std::string line;
  uint16 capture;
  std::vector<std::string> token;

  obj.open (file_name, ios::in | ios::app | ios::out);

  while(getline(obj, line))
  {
    if (line[0] != '#') {
      if ((line[0] == 'A') || (line[0] == 'D')) {
        std::stringstream word (line);
        std::string new_words;
        while(word >> new_words)
          token.push_back(new_words);
      }
    }
  }

  while (i < token.size())
  {
    if (token[i-1] == "A")
    {
      capture = stoi(token[i], nullptr, 0);
      i++;

    } else if (token[i-1] == "D") {
      dataMem[capture] = (uint16)stoi(token[i], nullptr, 16);
      std::cout<<std::setfill('0')<<std::setw(4)<<capture<<"    | "<<std::hex<<std::setw(4)<<dataMem[capture]<<std::endl;


      capture++;
      i++;
    } else
      i++;
  }

  return 1;
}
