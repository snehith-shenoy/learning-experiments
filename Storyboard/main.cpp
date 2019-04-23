#include "StoryBoard.h"

int main()
{
	Note n1 {"First Note","with sample text", {"first", "sample"}},
	n2 {"Second note", "with some text", {"second","sample"}};

	Storyboard b1;
	b1.addNote(n1);
	b1.addNote(n2);

	//Modifying a tag is currently problematic
	n2.m_tags.erase("sample");

	n1.m_title = "First Note 1";
	b1.searchByTitle("First Note");
	b1.searchByText("with some text");
	b1.searchByTag("sample");
	return 0;
}
