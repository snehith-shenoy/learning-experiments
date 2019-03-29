#ifndef __SIMPLE_LIST__
#define __SIMPLE_LIST__
#include <iostream>

using namespace std;


class simple_list
{

private:
	class node
	{
		public:
			node(): next(NULL), data(-1){}

			node *next;
			int data;
	} *n;
friend ostream& operator<<(ostream&, simple_list&);

public:

		simple_list();
		~simple_list();
		simple_list(const simple_list&);
		int front();
		void push_front(int);
		void erase_after(int);
		void insert_after(int,int);

		bool empty();
		unsigned int max_size();
		
		simple_list& operator=(const simple_list&);

		class iterator
		{
		public:
			//iterator(): m_refnode(){}
			iterator(node *nptr = nullptr): m_refnode(nptr){}
			iterator(const iterator &orig)
			{
				m_refnode = orig.m_refnode;
			}

			int * operator->()
			{
				return &(static_cast<node *>(m_refnode)->data);
			}

			int& operator *() const
			{
				if(m_refnode == NULL)
					std::cout<<"\nThis iterator cannot access the data\n";
				return (m_refnode->data);
			}

			iterator& operator ++() //Prefix
					{
				if(m_refnode)

					m_refnode = m_refnode->next;

				return *this;
					}


			iterator operator ++(int) //Postfix
			{
				iterator temp(*this);
				if(m_refnode)
					m_refnode = m_refnode->next;
				return temp;
			}

		bool operator!=(const iterator &orig) const
		{
			return m_refnode != orig.m_refnode;
		}

		bool operator==(const iterator &orig) const
		{
			return m_refnode == orig.m_refnode;
		}

		private:

			node *m_refnode;

		};

		class const_iterator
		{
		public:

			const_iterator(node *nptr = nullptr): m_refnode(nptr){}
			const_iterator(const const_iterator &orig)
			{
				m_refnode = orig.m_refnode;
			}


			const int& operator *() const
			{
				if(m_refnode == NULL)
					std::cout<<"\nThis iterator cannot access the data\n";
				return (m_refnode->data);

			}

			const_iterator& operator ++() //Prefix
			{
				if(m_refnode)

					m_refnode = m_refnode->next;

				return *this;
			}


			const_iterator operator ++(int) //Postfix
			{
				const_iterator temp(*this);
				if(m_refnode)
					m_refnode = m_refnode->next;
				return temp;
			}

		bool operator!=(const const_iterator &orig) const
		{
			return m_refnode != orig.m_refnode;
		}

		bool operator==(const const_iterator &orig) const
		{
			return m_refnode == orig.m_refnode;
		}



		private:

			node *m_refnode;

		};


		iterator end();
		iterator begin();
//To get const iterator
		const_iterator cend();
		const_iterator cbegin();



};



#endif
