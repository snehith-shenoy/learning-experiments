#ifndef __BASE_H__
#define __BASE_H__
class Base

{
	public: 

		virtual void list() = 0;
		virtual std::string name() = 0;
		virtual void moveto(Base *) = 0;
		virtual ~Base(){}
	

		virtual void addChild(Base *){}


};

#endif
