#pragma once


#include "HEADERS.hpp"

using namespace std;

class MONITOR: public sc_module
{

	public:

		SC_HAS_PROCESS(MONITOR);

		MONITOR(sc_module_name nm): sc_module(nm)
		{
			SC_METHOD(mon_print);
			sensitive<< m_in1;
			dont_initialize();
		}

		void mon_print()
		{
			cout<<endl<<" Output: "<<m_in1->read()<<" @ "<<sc_time_stamp()<<endl;
		}

		sc_in<bool> m_in1;

};
