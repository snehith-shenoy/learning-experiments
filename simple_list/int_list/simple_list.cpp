#include "simple_list.h"



simple_list::simple_list()
{
	n = NULL;
}

simple_list::simple_list(const simple_list &ls)
{
	*this = ls;
}
simple_list::~simple_list()
{
	
	node * temp;
	while(n)
	   { temp =n->next;
#ifdef DEBUG
	     cout<<"Deleting "<<n->data<<" @"<<std::hex<<n<<" now"<<endl;
	     if(n->next) cout<<n->next<<" will deleted next" <<endl;
#endif
	     delete n;
	     n = temp;
	   }

}

class simple_list;	   
simple_list& simple_list::operator=(const simple_list& copy) //Deep copy
{
	if(this != &copy)
		{
			node *from = copy.n;
			n = new node;
			node *to = n;
			if(from)
			{
				n->data = from->data;
				from = from->next;
#ifdef DEBUG		
			 	cout<<"Copying "<<n->data<<endl;
#endif			
			}
			while(from)
			{
#ifdef DEBUG		
			 	cout<<"Copying "<<from->data << endl;
#endif			
				node *temp = new node;
				temp->data = from->data;
				
				if(from->next)
				{
				temp->next = new node;
				temp->next->data = from->next->data;
				}
				to->next = temp;
				to = to->next;
				from = from->next;

			}

		}
	return *this;
}

int simple_list::front()
{
	if(n!=NULL) return n->data;
	else return -1;
}



void simple_list::push_front(int d)
{
	node *temp = new node;
	temp->data=d;
	temp->next=n;
	n=temp;
}

void simple_list::erase_after(int d)
{
	node *temp1=n;
	while( temp1)
	{
		if (temp1->data ==d )
		{
#ifdef DEBUG
			std::cout<<"Elements will be deleted after "<<temp1->data<<std::endl;
#endif
		 	break; 
		}
		temp1 = temp1->next;
	}


	if(temp1!=NULL) 
		{
//Delete nodes after matching node
			node * temp= temp1->next;
			temp1->next=NULL; //Next node of matching node	
			node * temp2;

			while(temp) 
			   { temp2 =temp->next;
			     delete temp;
			     temp = temp2;		    
			   }
		}
	else
		std::cerr<<d<<" not found in list\n";

}

void simple_list::insert_after(int pos, int d)
{
	node * match =n;
	while(match)
		{
			if(match->data ==pos)
			{
#ifdef DEBUG
				std::cout<<"New element will be inserted after"<<match->data<<std::endl;
#endif
				break;
			}
			match = match->next; 
		}
	
	if(match) 
		{
			node *temp2 =new node;
			temp2->data=d;
			temp2->next= match->next;
#ifdef DEBUG
			std::cout<<temp2->data<<" is followed by ";
			(temp2->next)? std::cout<<temp2->next->data<<std::endl : std::cout<<std::endl;
#endif
			match->next = temp2;
#ifdef DEBUG
			std::cout<<match->data<<" is followed by "<<match->next->data<<std::endl;
#endif

			
		}
	else
		std::cerr<<pos<<" not found in list"<<std::endl;

}

simple_list::iterator simple_list::begin()
{
	return iterator(n);
}

simple_list::iterator simple_list::end()
{
	return iterator();

}

simple_list::const_iterator simple_list::cbegin()
{
	return const_iterator(n);
}


simple_list::const_iterator simple_list::cend()
{
	return const_iterator();
	
}


bool simple_list::empty()
{
	if(n==NULL) return true;
	else return false;
}

unsigned int simple_list::max_size()
{
	unsigned int size=0;
	node *t = new node;
	t = n;
	if(n) t->next=n->next;
	while(t!=NULL) { size++; t=t->next;}
	return size;
	
}

ostream& operator<<(ostream &out, simple_list &lst) 
{
	
	simple_list::node *temp = lst.n;
	out<<"Head ";
	while(temp)
	{
		out<<"-->"<<temp->data;
#ifdef DEBUG
		out<<" ( "<<temp<<" ) ";
#endif	
		temp=temp->next;
	}
	
	return out<<"\n";
	
}


