

#include "HEADERS.hpp"

class STIMULATOR: public sc_module
{
	public:
		SC_HAS_PROCESS(STIMULATOR);

		STIMULATOR(sc_module_name nm): sc_module(nm)
	{
		SC_THREAD(logic_test);
	}
		void logic_test()
		{
			unsigned short t = 0;
					
			cout<<"ABCD | F |\n";
			cout<<"==========\n";

			while(t<16){
				m_A->write(t&0x8);			
				m_B->write(t&0x4);
				m_C->write(t&0x2);
				m_D->write(t&0x1);
				wait(1,SC_NS);

				cout<< m_A<<m_B<<m_C<<m_D;
				cout<<" | "<<m_in1<<" |\n----------\n";
				++t;
			
			 } 		
		}



	sc_out<bool> m_A,m_B,m_C,m_D;
	sc_in <bool> m_in1;

};

