#include <iostream>

class node{
public:
node *next;
node *prev;

};

class simple_list{

public:

simple_list();

~simple_list();

bool is_empty();
unsigned int max_size();

node* front();
void push_front(node *element);
void erase_after(node *element);
void insert_after(node *element);

simple_list operator << (simple_list obj);

private:

node *n;
};
