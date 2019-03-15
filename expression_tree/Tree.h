#ifndef __TREE_H__
#define __TREE_H__

#include "Nodes.h"
#include <vector>


class Tree
	{ 

	public: Tree(Node *current,Tree* left=NULL,Tree* right=NULL): m_root(current),  m_lTree(left), m_rTree(right)
		{

		}

		Tree(std::vector<Node *> expr)
		{
			//To Do
		}
		
		Tree* left()
		{
			return m_lTree;
		} // Return left branch, NULL if empty
	
		Tree* right() // Return right branch, NULL if empty
		{
			return m_rTree;
		}
		// Note: right branch for unary operators is NULL

		Node* node()// Return current node reference
		{
			return m_root;
		}

		~Tree()
		{
			delete m_root;
			if(m_lTree)
			{
				delete m_lTree;
			}
			if(m_rTree)
			{
				delete m_rTree;
			}
		}

	friend	ostream& operator <<(ostream& out, Tree& t);

	private:
		Node * m_root;
		Tree * m_lTree;
		Tree * m_rTree;
	

};

ostream & operator <<(ostream & out, Tree & t)
{

	if(!t.left() && !t.right())
		{ 
		  std::cout<<t.node();
		  out<<"";
		}
	else
	{
		out<<"(";
		if(t.left())
		{

			out<<(*t.left());
		}
	
		std::cout<<t.node();
		
		if(t.right())
		{
			out<<(*t.right());

		}

		out<<")";

	}

	return out;

}

#endif
