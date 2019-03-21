#include "simple_list.h"
#include <iostream>

using namespace std;

int main()

{
	simple_list l;
	cout<<"Initial Size: "<<l.max_size()<<endl;
	cout<<"List empty? "<<l.empty()<<endl;	
	l.push_front(5);
	l.push_front(2);
	l.push_front(1);
	l.push_front(0);
	cout<<"Size: "<<l.max_size()<<endl;
	cout<<"Front :"<<l.front()<<endl;
	cout<<"List is: "<<l<<endl;

	l.erase_after(7);
	l.erase_after(2);

	cout<<"List after deleting 2 onwards.\nSize: "<<l.max_size()<<endl;
	cout<<l;
	simple_list l2; l2 = l;
	cout<<"List created by copying above list\n";
	cout<<l2;

	l2.insert_after(2,10);
	cout<<"Inserted 10 at end. List is now\n"<<l2;
	l2.erase_after(1);
	cout<<"Deleted elements after 1. List is now\n"<<l2;
	simple_list l3(l2);
	cout<<"List created by copy-constructing above list\n"<<l3;
	return 0;
}

