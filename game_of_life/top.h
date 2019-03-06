/*

Conway's Game of Life as a SystemC Model

Author: snehiths@vayavyalabs.com

This is the header for top module/grid

*/

#pragma once

#include <string>
#include "cell.h"


class top: public sc_module
{

	SC_HAS_PROCESS(top);
	public:
	top(sc_module_name nm, int size): sc_module(nm), gridsize(size+2),grid(gridsize),clock((const char*)"top_clock",sc_time(2,SC_NS),0.5,SC_ZERO_TIME),gen(0),rep(0)
	{

		t_clock(clock);

		SC_METHOD(display);
		sensitive << t_clock.pos(); //Trigger at every negative clock edge
		dont_initialize();

		bool life=false; 
		std::string cell_name;

		grid.resize(gridsize);

		//Instantiate grid of cells with boundary 

		for (int i=0; i<gridsize; i++)
		{
			grid[i].resize(gridsize);

			for(int j=0; j<gridsize;j++)
			{  

				cell_name = "Cell_";
				cell_name = cell_name+ std::to_string(i)+ std::to_string(j);

				if(i>0 && i<gridsize-1 && j>0 && j<gridsize-1) //Actual cells
				{
					std::cout<<"Initialize "<<cell_name<<" to: ";
					std::cin>>life;

					grid[i][j] = new cell(cell_name.c_str(), life);
				}
				else //Dummy cells around boundary
				{
					grid[i][j] = new cell(cell_name.c_str(), false);
				}
				grid[i][j]->clk(clock);
			}
		}

		//Binding cell neighbor ports to neighbor cells

		for (int i=0; i<gridsize; i++)
		{
			for(int j=0; j<gridsize;j++)
			{
				int p=0;
				if(i>0 && i<gridsize-1 && j>0 && j<gridsize-1) //Actual cells
				{

					for(int k=-1;k<2;k++)
					{	for(int l=-1;l<2;l++)
						{
							if(k==0 && l==0) continue;
							grid[i][j]->neighbor[p](*grid[i+k][j+l]);
							p++;

						} 
						if (p==8) break;
					}
				}

				else // Dummy cells around boundary - bind to self
				{
					for(int p=0;p<8;p++)
					{
						grid[i][j]->neighbor[p](*grid[i][j]);
					}
				}
			}
		}

	}

	~top() //Delete cell pointers
	{

		for (int i=0; i<gridsize; i++)
			for(int j=0; j<gridsize;j++) 
				delete grid[i][j];

	}

private:
	void display() //Displays grid for each generation
	{
		std::cout<<std::endl<<"Generation "<<gen++<<std::endl;
		for (int i=1; i<gridsize-1; i++)
		{
			std::cout<<endl;
			for(int j=1; j<gridsize-1;j++) 
				std::cout<< (int) grid[i][j]->is_alive()<<" ";
		}
		std::cout<<std::endl<<std::endl<<"Continue game? (1/0) : ";
		cin>>rep;

		if(!rep) sc_stop();
	}

	int gridsize;
	std::vector<std::vector<cell*>> grid;
	sc_clock clock;
	sc_in<bool> t_clock;
	unsigned int gen,rep;

}; 
