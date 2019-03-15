

#include "Tree.h"

int main(int argc, char * argv[])
{

Tree  t(new OpPlus, 
	new Tree(new Num(1)),
	new Tree(new OpMul,
		 new Tree(new Num(2)),
		 new Tree(new Num(3)))); 

	std::cout<<t<<"\n";
	return 0;
}
