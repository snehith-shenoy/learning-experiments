#include <iostream>
#include <vector>
#include <functional>	


using namespace std;




class Button{


	public:

		void click()
		{
			m_func();
		}

		void register_click_handler(function<void(void)> f)
		{
			m_func =f;
//			cout<<"You registered a button "<<endl;
		}


	private:
		function<void(void)> m_func;


};


