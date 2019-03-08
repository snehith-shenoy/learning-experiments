/*

   Conway's Game of Life as a SystemC Model

Author: snehiths@vayavyalabs.com

This is the main file for the game

 */





#include "top.h"

int sc_main(int argc, char* argv[])
{
	int size;

	std::cout<<endl<<endl<<"######################[ Welcome to Game of Life ]######################";

	cout<<endl<<endl<<"Enter grid size >> ";
	cin>>size;

	std::cout<<std::endl<<"=================>>  Please set the initial pattern   <<================="<<std::endl;
	std::cout<<std::endl<<"!!! Note: You can initialize cells only to either alive(1) or dead(0) !!!"<<std::endl<<std::endl;

	top TopModule("Top_Module",size);
	cout<<endl<<"Starting the game..."<<endl;
	sc_start();

	return 0;

}
