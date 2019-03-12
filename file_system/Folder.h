#ifndef __FOLDER_H__
	 
#define __FOLDER_H__

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Base.h"


class Folder: public Base{


	protected:	Folder(std::string nm): m_foldName(nm), m_parent(this){}

	public:


		Folder(std::string name, Folder * parent): m_foldName(name), m_parent(parent)
		{
			m_parent->addChild(this);
		} 


		~Folder()
		{
			for(auto iter= m_children.begin(); iter!=m_children.end();iter++)
			{
				delete (*iter);
			}

		}


		void list()
		{
			
			std::cout<<"\nContents of "<<m_foldName<<"\n";
			if(m_children.empty())
				std::cout<<"This directory is empty"<<std::endl;
			else 
			{
				for (auto it=m_children.begin(); it!=m_children.end();it++)
					std::cout<<(*it)->name()<<" ";
				std::cout<<std::endl;
			}

		}

		std::string name()
		{
			return m_foldName+"/ ";
		}
		
		void moveto(Base * dest)
		{
			dest->addChild(this);
			m_parent->remChild(this);
			m_parent = (Folder*) dest;
			
		}

		void addChild(Base* child)
		{
			m_children.push_back(child);

		}

		void remChild( Base * trash)
		{
			auto it = m_children.begin();
			while((*it)!=trash) it++;
			m_children.erase(it);
		}

	
		private:

		std::list<Base *> m_children;
		std::string m_foldName;
		Folder * m_parent;

};

#endif
