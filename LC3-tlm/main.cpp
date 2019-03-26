/*
 * main.cpp
 * 
 * 
 * Test Bench for LC3 Arhitecture Implementation
 * using TLM 2.0
 *
 *  Created on: 26-Mar-2019
 *      Author: Snehith Shenoy
 */


#include "Top.h"

using namespace std;
int sc_main(int argc, char *argv[])
{

	if(argc!=2)
	{
		cout<<endl<<"Please provide a program file to load!"<<endl<<endl;
		exit(0);
	}
	
	cout<<"\n######## LC-3 Simulator (TLM 2.0) ########\n\n";

	TopModule top("Top",argv[1]);
	
	//Simulate for 100 ns
	top.nIRQ.write(1);
	top.nReset.write(0);
	sc_start(100,SC_NS);

	top.nIRQ.write(0);
	top.nReset.write(1);
	sc_start(100,SC_NS);

	top.nIRQ.write(1);
	top.nReset.write(1);
	sc_start(100,SC_NS);

	return 0;
}
