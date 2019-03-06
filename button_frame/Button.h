#include <iostream>
using namespace std;


class Button{


	static void on_click(unsigned int i)
	{
	cout<<"You clicked Button "<<i;
	}

	public:


		void (*fptr)(unsigned int) = on_click;

};
