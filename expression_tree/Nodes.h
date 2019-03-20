#ifndef __NODES_H__
#define __NODES_H__

#include <iostream>
using namespace std;
enum m_nodeType { NUMBER, VARIABLE, PLUS, MINUS, MULTIPLY, DIVIDE };

class Num;
class Var;
class OpPlus;
class OpMinus;
class OpMul;
class OpDiv;

class visitorHome
{
	public: 
		virtual void visit(Num & n) =0;
		virtual void visit(Var & n) =0;
		virtual void visit(OpPlus & n) =0;
		virtual void visit(OpMinus & n) =0;
		virtual void visit(OpMul &n) =0;
		virtual void visit(OpDiv &n) =0;


};

class visitor : public visitorHome
{
	public:
		void visit(Num &n) 
		{
			t = NUMBER;			
		}
		void visit(Var &n)
		{
			t = VARIABLE;	
		}
		void visit(OpPlus &n)
		{
			t = PLUS;
		}
		void visit(OpMinus &n) 
		{

			t = MINUS;
		}
		void visit(OpMul &n) 
		{

			t = MULTIPLY;
		}
		void visit(OpDiv & n) 
		{

			t = DIVIDE;
		}
		m_nodeType get_type()
		{
			return t;
		} 
	private:
		m_nodeType t;

};


class Node
{
	public:



		~Node(){};

		virtual void accept(visitorHome &v) =0;
		Node(){}

		virtual string print() =0;


	private:
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
		Num(int n): m_num(to_string(n)){}

		string print(){
			return m_num;
		}

		void accept( visitorHome &v)
		{ v.visit(*this); }

	private: string m_num;

};


class Var: public Node
{
	public:
		Var(string variable): m_varname(variable){}

		string print()
		{
			return m_varname;
		}

		void accept( visitorHome &v)
		{ v.visit(*this); }


	private:
		string m_varname;


};

class OpPlus: public Node
{
	public:
		OpPlus(): m_opname("+") { }

		string print()
		{
			return m_opname;
		}

		void accept( visitorHome &v)
		{ v.visit(*this); }

	private: string m_opname;

};

class OpMinus: public Node
{
	public:
		OpMinus(): m_opname("-"){}

		string print()
		{
			return m_opname;
		}

		void accept( visitorHome &v)
		{ 
			v.visit(*this);
		}

	private: string m_opname;

};

class OpMul: public Node
{
	public:
		OpMul():  m_opname("*"){}

		string print()
		{
			return m_opname;
		}

		void accept( visitorHome &v)
		{ v.visit(*this); }

	private: string m_opname;

};
class OpDiv: public Node
{
	public:
		OpDiv(): m_opname("/") {}

		string print()
		{
			return m_opname;
		}

		void accept( visitorHome &v)
		{ v.visit(*this); }

	private: string m_opname;
};


#endif
