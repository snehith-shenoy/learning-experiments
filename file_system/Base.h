#ifndef __BASE_H__
#define __BASE_H__
class Base

{
	public: 

		virtual void list() {}
		virtual void addFile(Base *) {}
		virtual void addFolder(Base *) {}
		virtual std::string name() = 0;
		virtual void moveto(Base *) = 0;

};

#endif
