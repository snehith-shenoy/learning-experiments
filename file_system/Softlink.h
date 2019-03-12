#ifndef __SOFTLINK_H__
#define __SOFTLINK_H__

#include "Base.h"
#include "Folder.h"
#include "Document.h"

class Softlink: public Base

{
	public:

		Softlink(std::string name, Document * source, Folder* target): m_linkName(name), m_source(source), m_parent(target)
	{

		target->addChild(this);

	}

		~Softlink()
		{
			if(m_source) delete m_source;
		}

		void list()

		{
			std::cout<<name()<<" -> "<<m_source->name()<<"\n";
		}

		std::string name()
		{
			return m_linkName;
		}

		void moveto( Base * dest)
		{
			dest->addChild(this);
			m_parent->remChild(this);
			m_parent= (Folder *)dest;
		}

	private:
		std::string m_linkName;
		Document * m_source;
		Folder * m_parent;

};


#endif

