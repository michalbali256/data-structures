#include <assert.h>

#include "node_list.h"
#include "vector.h"

namespace fibb
{

node * node_list::push_back(node && item)
{
	return push_back(new node(item));
}

node * node_list::push_back(node * item)
{
	if (empty())
	{
		assert(size_ == 0);
		first_ = item;
		first_->prev = nullptr;
		first_->next = nullptr;
		last_ = first_;
	}
	else
	{
		node * tmp = last_;
		last_ = item;
		last_->prev = tmp;
		last_->next = nullptr;
		tmp->next = last_;
	}
	++size_;
	return last_;
}

void node_list::remove(node * item)
{
	assert(item);
	if (item->prev != nullptr)
		item->prev->next = item->next;
	else
	{
		assert(item == first_);
		first_ = item->next;//first
	}
	if (item->next != nullptr)
		item->next->prev = item->prev;
	else
	{
		assert(item == last_);
		last_ = item->prev;//first
	}//last
	--size_;
}

void node_list::delete_child(node * item)
{
	remove(item);
	delete item;
}

bool node_list::empty()
{
	return first_ == nullptr;
}

void node_list::clear()
{
	vector<node *> stack;

	node * mom = first_;
	while (mom != nullptr)
	{
		stack.push_back(mom);
		mom = mom->next;
	}

	while (stack.size() != 0)
	{
		node * n = stack.back();
		stack.resize(stack.size() - 1);

		node * it = n->children.first();
		while (it != nullptr)
		{
			stack.push_back(it);
			it = it->next;
		}
		n->children.make_empty();
		delete n;
	}

	
	
	first_ = nullptr;
	last_ = nullptr;
	size_ = 0;
}

void node_list::make_empty()
{
	first_ = nullptr;
	last_ = nullptr;
	size_ = 0;
}

size_t node_list::size()
{
	return size_;
}

node * node_list::first()
{
	return first_;
}

node * node_list::last()
{
	return last_;
}

node_list::~node_list()
{
	clear();
}

}