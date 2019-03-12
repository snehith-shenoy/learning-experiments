#ifndef __FOLDER_H__
	 
#define __FOLDER_H__

#include <iostream>
#include <string>
#include <vector>
#include "Base.h"


class Folder: public Base{

	public:


		Folder(){}

		Folder(std::string name, Folder * parent): m_foldName(name), m_parent(parent)
		{
			m_parent->addFolder(this);
		} 


		~Folder()
		{
			for(auto iter= m_childDocs.begin(); iter!=m_childDocs.end();iter++)
			{
				delete (*iter);
			}

			for(auto iter= m_childFolders.begin(); iter!=m_childFolders.end();iter++)
			{
				delete (*iter);
			}


		}


		void list()
		{
			
			std::cout<<"\nContents of "<<m_foldName<<"\n";
			if(m_childDocs.empty() && m_childFolders.empty())
				std::cout<<"This directory is empty"<<std::endl;
			else 
			{
				for (auto it=m_childDocs.begin(); it!=m_childDocs.end();it++)
					std::cout<<(*it)->name()<<" ";
				for (auto it=m_childFolders.begin(); it!=m_childFolders.end();it++)
					std::cout<<(*it)->name()<<"/ ";

				std::cout<<std::endl;
			}

		}

		void addFile(Base* newDoc)
		{
			m_childDocs.push_back(newDoc);

		}

		void addFolder(Base * newFolder)
		{
			m_childFolders.push_back(newFolder);
		}

		std::string name()
		{
			return m_foldName;
		}
		
		void moveto(Base * dest)
		{
			dest->addFolder(this);
			m_parent->rmChildFolder(this);
			
		}

		void rmChildFolder( Base * trash)
		{
			auto it = m_childFolders.begin();
			while((*it)!=trash) it++;
			m_childFolders.erase(it);
		}

		void rmChildDoc( Base * trash)
		{
			auto it = m_childDocs.begin();
			while((*it)!=trash) it++;
			m_childDocs.erase(it);
		}
	
		private:
		
		std::vector<Base *> m_childFolders;
		std::vector<Base *> m_childDocs;
		Folder * m_parent;
		std::string m_foldName;

//		friend class Document;

};

#endif
