#ifndef __NODES_H__
#define __NODES_H__

#include <iostream>
using namespace std;

class Node
{
	public:
	


	virtual ~Node(){}
	
	void setname(string nm) { m_nodename = nm; }
	
	string print()
		{
			return m_nodename;
		}

	
	private:
		string m_nodename;

	friend	ostream & operator<<(ostream & out, Node* n);

};


ostream & operator<<(ostream & out, Node* n)
		{
		   out<<n->print();
		   return out;
		} 


class Num:public Node
{
	public: 
		Num(int n){ setname(to_string(n));}
};


class Var: public Node
{
	public:
		Var(string variable) {setname(variable);}
		~Var(){}

	
};

class OpPlus: public Node
{
	public:
		OpPlus(){ setname("+"); }

		~OpPlus(){}
		
};

class OpMinus: public Node
{
	public:
		OpMinus() { setname("-"); }

		~OpMinus(){}
};

class OpMul: public Node
{
	public:
		OpMul() { setname("*");}

		~OpMul(){}


};
class OpDiv: public Node
{
	public:
		OpDiv() { setname("/"); }

		~OpDiv(){}

};


#endif
