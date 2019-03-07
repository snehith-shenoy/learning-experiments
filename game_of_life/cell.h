/*

   Conway's Game of Life as a SystemC Model

Author: snehiths@vayavyalabs.com

This is the header for cell

 */


#pragma once

#include "systemc.h"
#include <iostream>
#include <string>


class cell_if: public sc_interface
{

	public:
		//Queries the current status of a cell 
		virtual bool is_alive() =0;


};

class cell: public sc_module, public cell_if
{

	SC_HAS_PROCESS(cell);

	public:
	sc_in<bool> m_clk;
	sc_vector<sc_port<cell_if>> m_neighbor;

	cell(sc_module_name nm,bool i_life): sc_module(nm),m_neighbor("nbr_port_vector",8),m_alivenow(i_life), m_alivenext(false)
	{
		SC_THREAD(step);
		sensitive << m_clk.pos();
		dont_initialize();
#if 1
		std::cout<<"Cell "<<name()<<": "<<m_alivenow<<std::endl;
#endif		
	}


	void step(void)
	{
		unsigned int nbr_count;
		while(1)
		{
			nbr_count = 0;
			for(int i=0;i<8;i++)
			{ if(m_neighbor[i]->is_alive())
				{ nbr_count++; }
			}
			switch(nbr_count)
			{
				case 2: m_alivenext = m_alivenow ; break;
				case 3: m_alivenext = true; break;
				default: m_alivenext = false;
			}

			wait(0,SC_NS); //Update in next Delta
			m_alivenow = m_alivenext;


			wait();	
		}

	}
	bool is_alive()
	{
		return m_alivenow;
	}

	private:

	bool m_alivenow, m_alivenext;

};
