

#include "HEADERS.hpp"

class STIMULATOR: public sc_module
{
	public:
		SC_HAS_PROCESS(STIMULATOR);

		STIMULATOR(sc_module_name nm): sc_module(nm)
	{
		SC_THREAD(logic_test);
//		SC_METHOD(mon_print);
//		sensitive << m_in1;
//		dont_initialize();	
	}
		void logic_test()
		{
			unsigned short t = 0;

			while(t<=16){
				m_A->write(t&0x8);			
				m_B->write(t&0x4);
				m_C->write(t&0x2);
				m_D->write(t&0x1);
				cout<<endl<<"ABCD:"<< m_A<<m_B<<m_C<<m_D<<endl;

				wait(1,SC_NS);
				cout<<endl<<" Output: "<<m_in1->read()<<" @ "<<sc_time_stamp()<<endl;

				wait(1,SC_NS);
				++t;
			
			 } 		
		}

		void mon_print()
		{
				}


	sc_out<bool> m_A,m_B,m_C,m_D;
	sc_in <bool> m_in1;

};

