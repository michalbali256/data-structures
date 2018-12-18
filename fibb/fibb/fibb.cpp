#include <cmath>

#include "fibb.h"

namespace fibb
{

void fibb_heap::insert(key_t k, id_t id)
{
	present_.stretch_to_fit(id, nullptr);
	
	assert(present_[id] == nullptr);
	node * added = roots_.push_back({ k, id });
	present_[id] = added;

	if (min == nullptr || min->key > k)
		min = added;

	++size_;
}

void fibb_heap::delete_min()
{
	if (size_ == 0)
		return;
	auto delete_begin_steps = delete_steps_;
	assert(min->parent == nullptr);

	//move all children of minimum to the heap forest
	while (min->children.first())
	{
		++delete_steps_;
		make_root(min->children.first());
	}


	assert(present_[min->id] != nullptr);
	assert(present_[min->id] == min);
	//deallocate the minimum
	present_[min->id] = nullptr;
	roots_.delete_child(min);
	min = nullptr;
	--size_;

	if (size_ > 1)
		balance();
	else if (size_ == 1)
		min = roots_.first();
	assert(present_[min->id] != nullptr);
	assert(present_[min->id] == min);

	if (delete_steps_ - delete_begin_steps > delete_max_)
		delete_max_ = delete_steps_ - delete_begin_steps;
	++delete_count_;
}

//joins two trees. takes their roots as parameters
node * fibb_heap::join(node * a, node * b)
{
	if (a->key < b->key)
	{
		a->children.push_back(b);
		b->parent = a;
		return a;
	}
	else
	{
		b->children.push_back(a);
		a->parent = b;
		return b;
	}
}

//consolidates the trees in heap and chooses new minimum
void fibb_heap::balance()
{
	vector<node *> neu;
	//consolidate
	node * mom = roots_.first();
	while (mom)
	{
		node * nxt = mom->next;
		size_t deg = mom->children.size();
		node * joined = mom;

		neu.stretch_to_fit(deg, nullptr);
		while (neu[deg] != nullptr)
		{
			joined = join(neu[deg], joined);
			neu[deg] = nullptr;
			++deg;

			neu.stretch_to_fit(deg, nullptr);
			++delete_steps_;
		}
		neu[deg] = joined;

		mom = nxt;
	}
	
	//return the trees from the array to the roots and find new minimum
	min = nullptr;
	roots_.make_empty();
	for (size_t i = 0; i < neu.size(); ++i)
		if (neu[i] != nullptr)
		{
			roots_.push_back(neu[i]);
			if (min == nullptr || min->key > neu[i]->key)
				min = neu[i];
		}
	
}

void fibb_heap::decrease(id_t id, key_t new_k)
{
	node * to_dec = present_[id];
	if (to_dec == nullptr || to_dec->key <= new_k)//if the request is valid
		return;
	++decrease_count_;
	auto decrease_begin_steps = decrease_steps_;



	to_dec->key = new_k;

	if (min->key > new_k)
		min = to_dec;

	if (to_dec->parent == nullptr || to_dec->parent->key <= new_k)
		return; 
	

	node * mom = to_dec->parent;
	
	make_root(to_dec);
	++decrease_steps_;
	
	if (!naive_)
	{
		//move parents of the decreased node to heap if they already lost a son and are marked
		while (mom->parent != nullptr && mom->marked)
		{
			
			node * p = mom->parent;
			make_root(mom);
			mom = p;

			++decrease_steps_;
		}

		if (mom->parent != nullptr)
			mom->marked = true;
	}

	if (decrease_steps_ - decrease_begin_steps > decrease_max_)
		decrease_max_ = decrease_steps_ - decrease_begin_steps;
}

void fibb_heap::clear()
{
	roots_.clear();
	for (size_t i = 0; i < present_.size(); ++i)
		present_[i] = nullptr;

	decrease_count_ = 0;
	decrease_max_ = 0;
	decrease_steps_ = 0;

	delete_count_ = 0;
	delete_max_ = 0;
	delete_steps_ = 0;

	size_ = 0;
	min = nullptr;
}

double fibb_heap::decrease_average()
{
	return (double) decrease_steps_ / (double)decrease_count_;
}

double fibb_heap::delete_average()
{
	return (double)delete_steps_ / delete_count_;
}

uint64_t fibb_heap::decrease_max()
{
	return decrease_max_;
}

uint64_t fibb_heap::delete_max()
{
	return delete_max_;
}

void fibb_heap::make_root(node * n)
{
	assert(n);
	n->remove_from_parent();
	roots_.push_back(n);
	n->marked = false;
}


}