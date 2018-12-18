#ifndef DATA_STRUCTURES_FIBB_LINKED_LIST_H
#define DATA_STRUCTURES_FIBB_LINKED_LIST_H

#include <stdint.h>



namespace fibb
{

struct node;

class node_list
{
	
public:
	//allocates space for the item and adds it to the list
	node * push_back(node && item);
	//adds item to the list, does not allocate anything
	node * push_back(node * item);
	//removes item and deallocates its memory
	void remove(node * item);
	//removes item from the list, does not deallocate
	void delete_child(node * item);
	//returns true if the list is empty
	bool empty();

	//deletes and deallocates all elements in the list
	void clear();
	//removes all elements from the list, but does not deallocate memory
	void make_empty();

	//returns number of elements in the list
	size_t size();

	node * first();
	node * last();

	~node_list();

private:
	node * first_ = nullptr;
	node * last_ = nullptr;
	size_t size_ = 0;
};

using key_t = uint32_t;
using id_t = uint32_t;

struct node
{
	node(key_t k, id_t i) : key(k), id(i) {}
	key_t key;
	id_t id;
	node * parent = nullptr;
	node * next;
	node * prev;
	bool marked = false;
	node_list children;

	void remove_from_parent()
	{
		parent->children.remove(this);
		parent = nullptr;
	}
};

}

#endif
