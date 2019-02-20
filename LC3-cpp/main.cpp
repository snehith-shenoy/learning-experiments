#include "Memory.h"
#include "LC3.h"

int main(int argc, char *argv[])
{
	//Instantiation
	LC3 lc3;
	Memory mem;	// Memory instance

	//Binding
	lc3.iport= &mem;
	lc3.dport= &mem;
	// Load program

	if(!mem.load(argv[1]))
		{
		cout<<"Couldn't load program";
		exit(0);
		}
	int i=1;
	while(1)	//Simulate
	{
		//cout<<"Executing step:"<<i++<<endl;
		i++;
		lc3.step();
		if(i>20) break;
	}
	return 0;
}
