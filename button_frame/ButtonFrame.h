#include "Button.h"
using namespace std;


class ButtonFrame{

	public:

		ButtonFrame(unsigned int count): m_buttons(count),m_clicks(count),m_total_clicks(0)	{
		for(unsigned int i=0; i<count;i++)
		{
			m_clicks[i] = 0;
			m_buttons[i].register_click_handler(on_click);
		}
	}

		
		static void on_click();
	



	//	private:
		vector<Button> m_buttons;
		vector<unsigned int> m_clicks;
		unsigned int m_total_clicks;

};

void ButtonFrame::on_click()
		{
		

cout<<"Hello!"<<endl;
//			m_buttons[i-1].fptr(i);
//			cout<<" | Button "<<" has been clicked "<<++m_clicks[i]<<" times"<<" | "<<"Total clicks: "<<++m_total_clicks<<endl<<endl;
		}


