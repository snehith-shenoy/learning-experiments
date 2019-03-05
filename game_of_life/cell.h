#pragma once

#include "systemc.h"


class cell_if: public sc_interface
{

	public:
		// Return true if cell is alive; else return false
		virtual bool is_alive() =0;


};

class cell: public sc_module, public cell_if
{
	
SC_HAS_PROCESS(cell);
	public:
		sc_in<bool> clk;
		sc_vector<sc_port<cell_if>> neighbor;

		cell(sc_module_name nm,bool i_life): sc_module(nm),neighbor("nbr_port_vector",8), alivenext(false)
	{
		SC_THREAD(step);
		sensitive << clk.pos();
		alivenow = i_life;
		
	}


		void step(void)
		{
			unsigned int nbr_count;
			while(1)
			{
				nbr_count =0;
				for(int i=0;i<8;i++) if(this->neighbor[i]->is_alive()) nbr_count++;
				switch(nbr_count)
				{
				  case 2: alivenext = alivenow;
				  case 3: alivenext = true;
			          default: alivenext = false;
				}
				
				alivenow = alivenext;
				wait();
			}

		}
bool is_alive()
{
return alivenow;
}

private:

bool alivenow, alivenext;
};
