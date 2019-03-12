#ifndef __ROOT_H__
#define __ROOT_H__

#include "Folder.h"

class Root: public Folder{

	public:
		static Root* Get();
		std::string name()
		{
			return m_rootName;
		}
	private:
		Root(std::string nm):m_rootName(nm){}
		Root (Root const &){};
		Root operator =(Root const&) {};
		static Root* m_rootPtr; // = new Root();
		std::string m_rootName;


};

Root* Root::m_rootPtr = NULL;

Root* Root::Get()
{	
	if(!m_rootPtr)
		 m_rootPtr = new Root("/");
	return m_rootPtr ;
}


#endif
