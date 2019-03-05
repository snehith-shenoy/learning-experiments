#include <string>
#include "cell.h"


class top: public sc_module
{

	SC_HAS_PROCESS(top);
	public:
	top(sc_module_name nm, int size): sc_module(nm), gridsize(size+1),grid(gridsize)
	{
		const sc_time period(5,SC_NS);
		sc_clock clock("top_clock", period, 0.5,SC_ZERO_TIME, false);

		t_clock(clock);
		SC_METHOD(display);
		sensitive << t_clock.neg();
		dont_initialize();

		//Instantiate grid of cells with boundary 
		bool life=false; 
		std::string cell_name;

		grid.resize(gridsize);

		for (int i=0; i<gridsize; i++)
		{
			grid[i].resize(gridsize);

			for(int j=0; j<gridsize;j++)
			{  

				cell_name = "Cell_";
				cell_name = cell_name+ std::to_string(i)+ std::to_string(j);

				if(i>0 && i<gridsize-1 && j>0 && j<gridsize-1)
				{
					std::cout<<"Enter the value of "<<(const char*) &cell_name[0] ;
					std::cin>>life;

					grid[i][j] = new cell((const char*) &cell_name[0], life);
				}
				else
				{
					grid[i][j] = new cell((const char*) &cell_name[0], false);
				}
				grid[i][j]->clk(clock);
			}
		}

		//Binding cell ports to neighbor
		for (int i=0; i<gridsize; i++)
		{
			for(int j=0; j<gridsize;j++)
			{
				int p=0;
				if(i>0 && i<gridsize-1 && j>0 && j<gridsize-1) //Actual grid
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

				else // Dummy cells around boundary
				{
					for(int p=0;p<8;p++)
					{
						grid[i][j]->neighbor[p](*grid[i][j]);
					}
				}
			}
		}



	}

	~top()
	{

		for (int i=0; i<gridsize; i++)
			for(int j=0; j<gridsize;j++) 
				delete grid[i][j];

	}
	//	private: 
	void display()
	{
		for (int i=0; i<gridsize; i++)
		{
			std::cout<<endl;
			for(int j=0; j<gridsize;j++) 
				std::cout<<grid[i][j]<<" ";
		}

	}
	int gridsize;
	std::vector<std::vector<cell*>> grid;
	sc_clock clock;
	sc_in<bool> t_clock;

}; 
