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
	top(sc_module_name nm, int size): sc_module(nm), m_gridsize(size+2),m_grid(m_gridsize),m_clock((const char*)"top_clock",sc_time(1,SC_NS),0.5,SC_ZERO_TIME),gen(0),rep(0)
	{


		SC_METHOD(display);
		sensitive << m_clock.posedge_event(); //Trigger at every m_clock postive edge
		dont_initialize();

		bool life=false; 
		std::string cell_name;

		m_grid.resize(m_gridsize);

		//Instantiate m_grid of cells with boundary 

		for (int i=0; i<m_gridsize; i++)
		{
			m_grid[i].resize(m_gridsize);

			for(int j=0; j<m_gridsize;j++)
			{  

				cell_name = "Cell_";
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
			}
		}

		//Binding cell m_neighbor ports to m_neighbor cells

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
							m_grid[i][j]->m_neighbor[p](*m_grid[i+k][j+l]);
							p++;

						} 
						if (p==8) break;
					}
				}

				else // Dummy cells around boundary - bind to self
				{
					for(int p=0;p<8;p++)
					{
						m_grid[i][j]->m_neighbor[p](*m_grid[i][j]);
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
		std::cout<<std::endl<<"Generation "<<gen++<<std::endl;
		for (int i=1; i<m_gridsize-1; i++)
		{
			std::cout<<endl; 

			for(int j=1; j<m_gridsize-1;j++) 
			{
				if( m_grid[i][j]->is_alive())
					std::cout<<"|*|";
				else
					std::cout<<"| |";
			}
		}
		std::cout<<std::endl<<std::endl<<"Continue game? (1/0) : ";
		cin>>rep;

		if(!rep) 
		{
			std::cout<<std::endl<<"Total simulation time: "<<sc_time_stamp()<<std::endl<<"Thanks for playing :)"<<std::endl;
			sc_stop();
		}
	}

	int m_gridsize;
	std::vector<std::vector<cell*>> m_grid;
	sc_clock m_clock;
	unsigned int gen,rep;

}; 
