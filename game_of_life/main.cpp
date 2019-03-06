/*

   Conway's Game of Life as a SystemC Model

Author: snehiths@vayavyalabs.com

This is the main file for the game

 */





#include "top.h"

int sc_main(int argc, char* argv[])
{
	int size;

	cout<<"Enter grid size: ";
	cin>>size;
	top TopModule("Top_Module",size);

	sc_start();

	return 0;

}
