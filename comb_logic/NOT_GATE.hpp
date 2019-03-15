
#include "HEADERS.hpp"

class NotGate: public sc_module 
{
	public:

		SC_HAS_PROCESS(NotGate);

		NotGate(sc_module_name nm):sc_module(nm), inst_name(nm)
		{
			SC_METHOD(notlogic);
			sensitive<<m_in1;
	 		dont_initialize();
		}

		void notlogic()
		{
			m_op->write(~m_in1->read());
			m_op->write(~m_in1->read());
			//cout<<inst_name<<" @ "<<sc_time_stamp()<<" Delta Cycle: "<<sc_delta_count()<<endl;

		}


		sc_in <bool> m_in1;
		sc_out<bool> m_op;

	private:

		string inst_name;
};
