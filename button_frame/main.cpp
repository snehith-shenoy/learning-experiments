#include "ButtonFrame.h"
#include <cstdlib>

int main(int argc, char * argv[])
{
	unsigned  int n=0;
	cout<<"Enter number of buttons to create: "; cin>>n;

	ButtonFrame bframe(n);

	for (int i=0; i<= rand() % 200 ; i++)
		bframe.m_buttons[rand() % n ].click();

	return 0;

}
