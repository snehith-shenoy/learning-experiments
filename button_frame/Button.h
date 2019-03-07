#include <iostream>
#include <vector>

using namespace std;




class Button{


	public:
		static unsigned int m_button_num;


	void click(){
	   m_button_num = m_index;

	  m_fptr();
	  }

	typedef void (*fptr_t)(void);

	void register_click_handler(fptr_t f)
	{
		m_fptr =f;
		cout<<"You registered Button "<<endl;
	}
	Button()
	{
		m_button_num++;
	}


	private:
		unsigned int m_index;
		fptr_t m_fptr;


};

unsigned int Button::m_button_num=0;
