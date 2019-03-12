#ifndef __ROOT_H__
#define __ROOT_H__

#include "Folder.h"

class Root: public Folder{

	public:
		static Root* Get();
		~Root(){}

	private:
		Root():Folder("/"){}
		
		// Prevent acess to copy/assign constructors
		Root (Root const &);
		Root operator =(Root const&);
		static Root* m_rootPtr;
		
		// Restrict functions
		std::string name(){ return "Root!"; }
	//	void list(){}
		void moveto( Base *){}

};

Root* Root::m_rootPtr = NULL;

Root* Root::Get()
{	
	return m_rootPtr ? m_rootPtr : new Root();
}


#endif
