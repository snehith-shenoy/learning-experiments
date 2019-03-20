#ifndef __TREE_H__
#define __TREE_H__

#include "Nodes.h"
#include <vector>
#include <stack>


class Tree
{ 

	public: Tree(Node *current,Tree* left=NULL,Tree* right=NULL): m_root(current),  m_lTree(left), m_rTree(right)
		{

		}

		Tree(std::vector<Node *> expr)
		{
			//To Do
			std::stack <Tree *> infixStack;
			visitor nodeChecker;
			Tree * opr1, *opr2;
			for (int i= expr.size()-1; i>=0;i--)
			{
				expr[i]->accept(nodeChecker);

				switch(nodeChecker.get_type())
				{

					case NUMBER:
					case VARIABLE:
						{
							infixStack.push(new Tree(expr[i]));
							break;
						}

					default: 
						{ 


							opr1 = infixStack.top(); infixStack.pop();


							opr2 = infixStack.top(); infixStack.pop();

							infixStack.push(new Tree( expr[i],opr1, opr2));
							break;
						}
				}




			}
			Tree *temp = infixStack.top();
			infixStack.pop();
			if(infixStack.empty())
			{
				m_root = temp->node();
				m_lTree = temp->left();
				m_rTree = temp->right();
				return;
			}
		}

		Tree* left()
		{
			return m_lTree;
		} // Return left branch, NULL if empty

		void set_ltree(Tree * lt)
		{

			m_lTree = lt;
		}

		Tree* right() // Return right branch, NULL if empty
		{
			return m_rTree;
		}

		void set_rtree(Tree *rt)
		{
			m_rTree = rt;
		}
		// Note: right branch for unary operators is NULL

		Node* node()// Return current node reference
		{
			return m_root;
		}

		~Tree()
		{
			delete m_lTree;
			delete m_rTree;
		}

		void evaluate()
		{
			*this = *evalTree(this);
		}	



	private:
		Node * m_root;
		Tree * m_lTree;
		Tree * m_rTree;
		friend	ostream& operator <<(ostream& out, Tree& t);

		Tree * evalTree(Tree * t)
		{

			bool leftnum = false, rightnum = false;

			visitor nodeChecker;

			if(t->left() || t->right())
			{
				t->left()->node()->accept(nodeChecker);

				if(nodeChecker.get_type() == NUMBER)
				{
					leftnum =true;
				}

				t->right()->node()->accept(nodeChecker);
				if(nodeChecker.get_type() ==  NUMBER)
				{
					rightnum = true;
				}

				if( leftnum && rightnum)
				{
UPDATE_TREE:				int a = stoi(t->left()->node()->print());
					int b =	stoi(t->right()->node()->print());

					t->node()->accept(nodeChecker);
					switch(nodeChecker.get_type())
					{
						case PLUS:
							{
								return new Tree( new Num(a+b) );
							}

						case MINUS:
							{
								return new Tree( new Num(a-b) );

							}

						case MULTIPLY:
							{
								return new Tree( new Num(a*b) );

							}
						case DIVIDE:
							{
								if(b==0)
								{
									cerr<<"Divide by zero!";
									exit(1);	
								}
								return new Tree( new Num(a/b) );

							}

						default:
							{}

					}
				}

				else
				{
					if(leftnum)
					{				 
						t->set_rtree( evalTree(t->right()) );
						t->right()->node()->accept(nodeChecker);
						if(nodeChecker.get_type()==NUMBER)
							goto UPDATE_TREE;
					}

					else if(rightnum)
					{
						t->set_ltree( evalTree(t->left()) );
						t->left()->node()->accept(nodeChecker);
						if(nodeChecker.get_type()==NUMBER)
							goto UPDATE_TREE;

					}

					else
					{
						t->set_rtree( evalTree(t->right()) );
						t->set_ltree( evalTree(t->left()) );
					}
				}

			}

			return t;

		}

};

ostream & operator <<(ostream & out, Tree & t)
{

	if(t.left()==NULL && t.right()==NULL)
	{ 
		//		  cout<<"Root ";
		std::cout<<t.node();
		out<<"";
	}
	else
	{
		out<<"(";
		if(t.left())
		{
			//		cout<<"Left branch ";
			out<<*(t.left());
		}

		std::cout<<t.node();

		if(t.right())
		{
			//			cout<<"Right branch ";
			out<<(*t.right());

		}

		out<<")";

	}

	return out;

}

#endif
