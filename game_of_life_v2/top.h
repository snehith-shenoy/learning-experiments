/*

   Conway's Game of Life as a SystemC Model

Author: snehiths@vayavyalabs.com

This is the header for top module/m_grid

 */

#pragma once

#include <string>
#include "cell.h"


class top: public sc_module
{

	SC_HAS_PROCESS(top);
	public:
	top(sc_module_name nm, int size): sc_module(nm),
	m_gridsize(size+2),
	m_grid(m_gridsize),
	m_clock((const char*)"top_clock",sc_time(1,SC_NS),0.5,SC_ZERO_TIME),
	m_sig("Sig_Rows",m_gridsize),
	m_gen(0),
	m_rep(0)
	{


		SC_METHOD(display);
		sensitive << m_clock.posedge_event(); //Trigger at every m_clock postive edge
		dont_initialize();

		bool life= false; 
		std::string cell_name;


		//Instantiate m_grid of cells with boundary 
		for (int i=0; i<m_gridsize; i++)
		{
			// Set size of column for each row of Cells and Signals
			m_grid[i].resize(m_gridsize); 
			m_sig[i].init(m_gridsize);
			for(int j=0; j<m_gridsize;j++)
			{  

				cell_name = "Cell_";

				//Generate unique cell name
				cell_name = cell_name+ std::to_string(i)+ std::to_string(j);

				if(i>0 && i<m_gridsize-1 && j>0 && j<m_gridsize-1) //Actual cells
				{
					std::cout<<"Initialize "<<cell_name<<" to: ";
					std::cin>>life;
					m_grid[i][j] = new cell(cell_name.c_str(), life);

				}
				else //Dummy cells around boundary
				{
					m_grid[i][j] = new cell(cell_name.c_str(), false);
				}
				m_grid[i][j]->m_clk(m_clock);
				m_grid[i][j]->m_out(m_sig[i][j]);
			}
		}

		//Binding cell neighbor in ports to neighbor cell out ports

		for (int i=0; i<m_gridsize; i++)
		{
			for(int j=0; j<m_gridsize;j++)
			{
				int p=0;
				if(i>0 && i<m_gridsize-1 && j>0 && j<m_gridsize-1) //Actual cells
				{

					for(int k=-1;k<2;k++)
					{	for(int l=-1;l<2;l++)
						{
							if(k==0 && l==0) continue;
							m_grid[i][j]->m_neighbor[p](m_sig[i+k][j+l]);
							p++;

						} 
						if (p==8) break;
					}
				}

				else // Dummy cells around boundary - bind to Top sc_out
				{
					for(int p=0;p<8;p++)
					{
						m_grid[i][j]->m_neighbor[p](m_sig[i][j]);
					}
				}
			}
		}

	}

	~top() //Delete cell pointers
	{

		for (int i=0; i<m_gridsize; i++)
			for(int j=0; j<m_gridsize;j++) 
				delete m_grid[i][j];

	}

	private:
	void display() //Displays grid for each generation
	{
		std::cout<<std::endl<<"Generation "<<m_gen++<<std::endl;
		for (int i=1; i<m_gridsize-1; i++)
		{
			std::cout<<endl; 

			for(int j=1; j<m_gridsize-1;j++) 
			{
				if( m_grid[i][j]->m_out->read())
					std::cout<<"|*|";
				else
					std::cout<<"| |";
			}
		}
		std::cout<<std::endl<<std::endl<<"1:Continue | Other Key: Quit >> ";
		cin>>m_rep;

		if(m_rep!=1) 
		{
			std::cout<<std::endl<<"######################[   Thanks for playing :)   ]######################"<<std::endl;
			std::cout<<std::endl<<"Total simulation time: "<<sc_time_stamp();
			sc_stop();
		}
	}

	int m_gridsize;
	std::vector< std::vector<cell*> > m_grid;
	sc_clock m_clock;
	sc_vector< sc_vector< sc_signal<bool> > > m_sig;

	unsigned int m_gen,m_rep;

}; 
