#ifndef __SIMPLE_LIST__
#define __SIMPLE_LIST__
#include <iostream>

using namespace std;

class node
{
	public:
		node(): next(NULL){}
		~node()
		{
		//	if(next) delete next;
		}
		node *next;
		int data;
};

class simple_list
{
	public:

		simple_list();
		~simple_list();
		simple_list(const simple_list&);
		int front();
		void push_front(int);
		void erase_after(int);
		void insert_after(int,int);
		node* begin();
		node* begin() const;
		node* end();
		bool empty();
		unsigned int max_size();
		
		simple_list& operator=(const simple_list&);

	private:
		node *n; 
	friend ostream& operator<<(ostream&, simple_list&);


};


#endif
