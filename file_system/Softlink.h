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
			
			target->addFile(this);
				
		}
		
		~Softlink()
		{
			if(m_source) delete m_source;
		}
		
		std::string name()
		{
		  return m_linkName;
		}

		void moveto( Base * dest)
		{
			dest->addFile(this);
			m_parent->rmChildDoc(this);
		}

	private:
		
		Document * m_source;
		std::string m_linkName;
		Folder * m_parent;

};


#endif

