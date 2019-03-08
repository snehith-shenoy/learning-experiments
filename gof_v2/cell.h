/*

   Conway's Game of Life as a SystemC Model

Version 2 (Using ports and exports directly)

Author: snehiths@vayavyalabs.com

This is the header for cell

 */


#pragma once

#include "systemc.h"
#include <iostream>
#include <string>


class cell: public sc_module
{

	SC_HAS_PROCESS(cell);

	public:
	sc_in<bool> m_clk;
	sc_vector< sc_in<bool> > m_neighbor;
	sc_out<bool> m_out;

	cell(sc_module_name nm,bool i_life): sc_module(nm),m_neighbor("nbr_port_vector",8),m_i_life(i_life)
	{
		SC_THREAD(step);
		sensitive << m_clk.pos();
		dont_initialize();
	}


	void step(void)
	{
		unsigned int nbr_count;
		while(1)
		{
			nbr_count = 0;
			for(int i=0;i<8;i++)
			{ if(m_neighbor[i]->read())
				{ nbr_count++; }
			}
			switch(nbr_count)
			{
				case 2: m_out->write( m_out->read()); break;
				case 3:  m_out->write(1); break;
				default: m_out->write(0);
			}
			
			wait();	
		}

	}

	void end_of_elaboration()
	{
		m_out->write(m_i_life);
	}

private:
	bool m_i_life;

};
