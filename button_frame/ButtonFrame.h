#include "Button.h"

using namespace std;


class ButtonFrame{

	public:
		
		vector<Button> m_buttons;

		ButtonFrame(unsigned int count): m_buttons(count),m_clicks(count),m_total_clicks(0)
		{
			for(unsigned int i=0; i<count;i++)
			{
				m_clicks[i] = 0;

				m_buttons[i].register_click_handler(std::bind(&ButtonFrame::on_click,this,i));
			}
		}

/*		void operator()(unsigned int i)
		{
			on_click(i);
		}
*/
		void on_click(unsigned int bIndex)
		{
			cout<<"You clicked Button "<<bIndex+1<<" & Button "<<bIndex+1<<" has been clicked "<<++m_clicks[bIndex]<<" times"<<" | "<<"Total clicks: "<<++m_total_clicks<<endl<<endl;
		}

	private:
		vector<unsigned int> m_clicks;
		unsigned int m_total_clicks;

};


