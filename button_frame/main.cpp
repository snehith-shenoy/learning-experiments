#include "ButtonFrame.h"
#include <cstdlib>

int main(int argc, char * argv[])
{
	unsigned  int n=0;
	cout<<"Enter number of buttons to create: "; cin>>n;

	ButtonFrame bframe(n);

	for (int i=0; i<= rand() % 100 ; i++)
		bframe.click(rand() % n +1);


	return 0;

}
