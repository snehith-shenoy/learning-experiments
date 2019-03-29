#include "simple_list.h"
#include <iostream>

using namespace std;

int main()

{
	simple_list l;
	simple_list::iterator itr;
	simple_list::const_iterator const_itr;

	cout<<"Creating a new list\nInitial Size: "<<l.max_size()<<endl;
	cout<<"List empty? "<<(l.empty()?"Yes":"No")<<endl;
	l.push_front(5);
	l.push_front(2);
	l.push_front(1);
	l.push_front(0);
	const_itr = l.cbegin();
	itr = l.begin();
	cout<<"\nAdding some data...\nSize: "<<l.max_size()<<"\n"<<l;
	cout<<"Front :"<<l.front()<<endl;

	cout<<"\nAccessing second element using const iterator\n"<<*(++const_itr)<<"\n";
//	*const_itr = 3; //Can't; its const iterator

	std::cout<<"\nTrying to erase data following 7\n";
	l.erase_after(7);
	l.erase_after(2);

	cout<<"\nList after deleting 2 onwards.\nSize: "<<l.max_size()<<"\n";
	cout<<l;
	simple_list l2; l2 = l;
	cout<<"\nList created by copying above list\n";
	cout<<l2;

	l2.insert_after(2,10);
	cout<<"\nInserted 10 at end. List is now\nHead ";
	for(itr = l2.begin(); itr!=l2.end();itr++)
		{
			cout<<"-->"<<*itr;
		}
//	cout<<*itr; //causes segfault because itr = l2.end()
	l2.erase_after(1);
	cout<<"\n\nDeleted elements after 1. List is now\n"<<l2;
	simple_list l3(l2);
	cout<<"\nList created by copy-constructing above list\n"<<l3;

	return 0;
}

