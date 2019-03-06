#include "Button.h"
#include <vector>
using namespace std;

class ButtonFrame{

	public:

		ButtonFrame(unsigned int count): m_buttons(count),m_clicks(count),m_total_clicks(0)
	{

		for(unsigned int i=0; i<count;i++)
			m_clicks[i] = 0;

	}

		void click(unsigned int i)
		{
			m_buttons[i-1].fptr(i);
			cout<<" | Button "<<i<<" has been clicked "<<++m_clicks[i]<<" times"<<" | "<<"Total clicks: "<<++m_total_clicks<<endl<<endl;
		}

//	private:
		vector<Button> m_buttons;
		vector<unsigned int> m_clicks;
		unsigned int m_total_clicks;

};
