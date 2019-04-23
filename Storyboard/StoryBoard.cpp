#include "StoryBoard.h"

Note::Note(const std::string& title, const std::string &body = "", const  std::set<std::string> &tags= {""}):
m_title{title}, m_text{body}, m_tags{tags}
{
}

std::ostream& operator<<(std::ostream& out, Note const &printnote)
{
	out<<"===== "<<printnote.m_title<<" =====\n"<<printnote.m_text<<"\n======= End =======\nTags: ";
	for(std::string tag  :printnote.m_tags)
		out<<" [ "<<tag<<" ]";

	return out<<"\n\n";
}



void Storyboard::addNote(Note const &newnote)
{
	m_notes.insert(newnote);
	for(auto it = newnote.m_tags.begin(); it!= newnote.m_tags.end(); it++)
	{
			m_tagMap.insert(mypair((std::string *)&(*it), const_cast<Note*>(&newnote)));
	}

	m_titleMap.insert(mypair((std::string *)&(newnote.m_title), const_cast<Note*>(&newnote) ));
	m_textMap.insert(mypair((std::string *)&(newnote.m_text), const_cast<Note *>(&newnote) ));

}


void Storyboard::deleteNote(Note const &thatnote)
{
	for(auto it = thatnote.m_tags.begin(); it!= thatnote.m_tags.end(); it++)
	{
		typedef mymultimap::iterator iterator;
		std::pair<iterator,iterator> targrange = m_tagMap.equal_range((std::string *)&(*it));

		for(iterator my_it = targrange.first; my_it!=targrange.second; my_it++)
		{
			if(my_it->second == &thatnote)
				m_tagMap.erase(my_it);
		}
	}

	m_notes.erase(thatnote);

}

void Storyboard::searchByTitle(std::string const &title) const
{
	auto it = m_titleMap.find((std::string *)&title);
	if(it != m_titleMap.end())
		std::cout<<*(it->second)<<std::endl;
	else
		std::cout<<"No note found with title: "<<title<<"\n\n";
}

void Storyboard::searchByText(std::string const &text) const
{
	auto it = m_textMap.find((std::string *)&text);
	if(it != m_textMap.end())
	{
		std::cout<<"Found the following note with matching text:\n\n"<<
				*(it->second)<<"\n\n";
	}
	else
		std::cout<<"No note found !"<<std::endl;
}


void Storyboard::searchByTag(std::string const &tag)
{
	typedef mymultimap::iterator iterator;
	std::pair<iterator,iterator> targrange = m_tagMap.equal_range((std::string *)&tag);

	iterator my_it = targrange.first;
	if(my_it!=m_tagMap.end() )
	{

		std::cout<<"Found following notes tagged with '"<<tag<<"'\n\n";
		for(; my_it!=targrange.second; my_it++)
		{
			std::cout<<*(my_it->second);
		}

		std::cout<<"'\n\n";
	}
}

void Storyboard::searchByTag(std::list<std::string> const &vtag) const
{
	// To do after fixing search by single tag
}



