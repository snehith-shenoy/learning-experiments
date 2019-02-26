#include "Top.h"

using namespace std;
int sc_main(int argc, char *argv[])
{

	if(argc!=2)
		{
		cout<<"Please provide program file to load!";
		exit(0);
		}
	TopModule top("Top",argv[1]);

	//Simulate for 100 ns
	sc_start(200,SC_NS);

	return 0;
}
