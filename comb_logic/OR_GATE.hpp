#include "HEADERS.hpp"

class OrGate: public sc_module
{
	public:

		SC_HAS_PROCESS(OrGate);

		OrGate(sc_module_name nm): sc_module(nm), inst_name(nm)
		{
		SC_METHOD(orlogic);
		sensitive<< m_in1 << m_in2;
		dont_initialize();
		}

		void orlogic()
		{

			m_op->write( m_in1->read() | m_in2->read());
#ifdef D_PRINT

			cout<<inst_name<<" @ "<<sc_time_stamp()<<" Delta Cycle: "<<sc_delta_count()<<endl;
#endif

		}

		sc_in<bool> m_in1,m_in2;

		sc_out<bool> m_op;
	private:
		string inst_name;

};

