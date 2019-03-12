#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__
#include <string>
#include "Base.h"
#include "Folder.h"



class Document: public Base

{
	public:

		Document(std::string name, Folder * parent): m_docName(name), m_parent(parent)
		{
			m_parent->addChild(this);
		}

		void list()
		{
			std::cout<<name();
		}

		std::string name()

		{
			return m_docName+" ";
		}

		void moveto( Base * dest)
		{
			dest->addChild(this);
			m_parent->remChild(this);
			m_parent= (Folder *)dest;
		}


	private:
		std::string m_docName;
		Folder * m_parent;
};

#endif
