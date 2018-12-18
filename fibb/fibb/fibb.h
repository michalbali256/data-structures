#ifndef DATA_STRUCTURES_FIBB_FIBB_H
#define DATA_STRUCTURES_FIBB_FIBB_H
#include <iostream>
#include "vector.h"
#include "node_list.h"

namespace fibb
{

class heap_checker;

class fibb_heap
{
	node_list roots_;
	vector<node *> present_;
	node * min = nullptr;
public:

	fibb_heap(bool naive) : naive_(naive) {}

	void insert(key_t k, id_t id);

	void delete_min();

	void decrease(id_t id, key_t new_k);

	//removes and deallocates all elements from the heap
	void clear();

	double decrease_average();
	double delete_average();

	uint64_t decrease_max();
	uint64_t delete_max();
	
	

private:
	void make_root(node *);

	void balance();

	node * join(node * a, node * b);

	size_t size_ = 0;

	uint64_t decrease_count_ = 0;
	uint64_t delete_count_ = 0;

	uint64_t decrease_steps_ = 0;
	uint64_t delete_steps_ = 0;

	uint64_t decrease_max_ = 0;
	uint64_t delete_max_ = 0;

	bool naive_ = false;

	friend heap_checker;
};

class heap_checker
{
public:
	size_t size;

	bool check(fibb_heap & h)
	{
		size = 0;

		node * it = h.roots_.first();
		while (it)
		{
			++size;
			if (!check_children(it))
				return false;

			it = it->next;
		}
		assert(h.size_ == size);
		if (h.size_ != size)
		{
			std::cout << "79";
			return false;
		}
		
		return true;
	}

	bool check_children(node * root)
	{
		node * ch = root->children.first();
		while (ch)
		{
			if (ch->parent != root)
			{
				std::cout << "91";
				return false;
			}
			assert(ch->parent == root);
			if (ch->key < root->key)
			{
				std::cout << "94";
				return false;
			}
			assert(ch->key >= root->key);
			++size;
			if (!check_children(ch))
				return false;

			ch = ch->next;
		}
		return true;
	}


};

}


#endif