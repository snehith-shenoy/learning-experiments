/* In this exercise we want to design a Storyboard. Our version of the Storyboard
 * contains arbitrary many notes (imagine it like putting sticky notes on a board).
 * Every note has a title, a text and a set of tags. E.g.
 * 	- title: "Test Traceplayer"
 * 	- text: "Implement a unit test for the class Traceplayer of the spark core framework."
 * 	- tags: {"unit test", "traceplayer", "testing", "spark core"}
 * 
 * Our Storyboard should enable us to search for notes by title, text and tags.
 * E.g.:
 *      searchByTitle("Test Traceplayer")
 *      searchByTag({"testing", "unit test"})
 *   	searchByText("Implement a unit test for the class Traceplayer of the spark core framework.")
 * For the sake of simplicity we don't want to do any similiarity or prefix matching when
 * searching for a title, tag or text. Only an exact match should give results.
 * 
 * The skeleton code below can be used as a starting point but doesn't have to.
 * The comments "fill in" are placeholders where you definitely have to put in some code when 
 * you use this skeleton code. But this doesn't mean that you shouldn't or can't put code anywhere else.
 * 
 * Also write some simple unit tests to show how you would test the functionality of the Storyboard.
 * Don't use any testing framework. Simple if-statements are sufficient for this exercise.
 * 
 * Hint: Think about performance versus memory tradeoffs in your design, so you can give good 
 *       reasons for your decision. 
 */


#ifndef __STORYBOARD_H
#define __STORYBOARD_H

#include <iostream>
#include <map>
#include <set>
#include <list>
#include <string>



//Assuming titles are unique which makes each note unique


struct Note
{
   explicit Note(const std::string&, const std::string&, const std::set<std::string>&);
   std::string m_title, m_text;
   std::set<std::string> m_tags;

   bool operator<(Note const &right) const
   {
	   return m_title < right.m_title;
   }
friend std::ostream& operator<<(std::ostream& out, Note const &printnote);

};

struct ptr_less
{
	bool operator()(std::string const * lhs, std::string const  * rhs) const
	{
        return ( *lhs < *rhs);
    }
};


typedef std::pair<std::string*, Note *> mypair;
typedef std::map<std::string*, Note *,ptr_less> mymap;
typedef std::multimap <std::string*, Note *,ptr_less> mymultimap;


class Storyboard
{
public:
	void addNote(Note const &a);
	void deleteNote(Note const &a);
	void searchByTitle(std::string const &title) const;
	void searchByText(std::string const &text) const;
	void searchByTag(std::string const &tag);
	void searchByTag(std::list<std::string> const &vtag) const;
	
private:
	//Choosing set because insertions/deletions are cheaper,especially
	// for large number of elements as compared to vector
	std::set <Note> m_notes;
	// Maps are faster for searching than other containers
	// Using multimap to map a tag to multiple notes since same tag can be shared
	// across notes
	mymultimap m_tagMap;
	mymap m_textMap;
	mymap m_titleMap;

};




#endif /*__STORYBOARD_H */
