
#include "Root.h"
#include "Document.h"
#include "Folder.h"
#include "Softlink.h"

int main(int argc, char* argv[])
{
	// Get access to the root directory

	Folder* root=Root::Get();
	// Create some folders inside root// Arguments are: file name and parent
	Folder* f_etc=new Folder("etc",root);
	Folder* f_bin=new Folder("bin",root);
	Folder* f_usr=new Folder("usr",root);

	// List contents of root
	// Should print (order and whitespaces can be different)://   etc/ bin/ usr/

	root->list();
	// Create some files and sub-folders in /etc 

	Document *f_etc_foo=new Document("foo",f_etc);
	Document *f_etc_bar=new Document("bar",f_etc);
	Folder *f_etc_init=new Folder("init",f_etc);
	Document *f_etc_init_cron=new Document("cron.conf",f_etc_init);

	// List contents of /etc// Should print (order and whitespaces can be different)://    foo bar init/
	Softlink * f_etc_foo_dup = new Softlink("foo.ln",f_etc_foo,f_usr);

	f_usr->list();

	f_etc->list();
	f_etc_init->list();

	f_etc->moveto(f_usr);
	
	std::cout<<"\nAfter moving etc/ \n";
	root->list();
	
	f_usr->list();

	std::cout<<"\nMoving link from usr/ and file from etc/int/ to etc/\n"; 

	f_etc_foo_dup->moveto(f_etc);
	f_etc_init_cron->moveto(f_etc);

	f_etc->list();
	f_bin->list();


	// Delete a folder (and all its children) */

	//delete root;
	return 0;
}
