
#include "HEADERS.hpp"

using namespace std;

class AndGate: public sc_module
{
	public:
		sc_in<bool> m_in1,m_in2;
		sc_out<bool> m_op;
		SC_HAS_PROCESS(AndGate);


		AndGate(sc_module_name nm): sc_module(nm),inst_name(nm){
			SC_METHOD(andlogic);
			sensitive<<m_in1<<m_in2;
			dont_initialize();
		}
		void andlogic()
		{
			m_op->write(m_in1->read() & m_in2->read());
			m_op->write(m_in1->read() & m_in2->read());
			//cout<<inst_name<<" @ "<<sc_time_stamp()<<" Delta Cycle: "<<sc_delta_count()<<endl;

		}

	private: string inst_name;	

};

