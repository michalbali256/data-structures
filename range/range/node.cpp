#include "node.h"
#include "bba_tree.h"
#include "vector.h"


namespace range
{
void x_node::insert(const point & p)
{
	y_node * y_point = new y_node(p);
	y_tree.insert(y_point);
}

template<typename T>
void swap(T & a, T & b)
{
	T & tmp = a;
	a = b;
	b = tmp;
}

void sort(vector<node *> & nodes, size_t begin, size_t end)
{
	if (end - begin <= 1)
		return;
	
	data_t pivot = nodes[begin]->key;
	size_t lower = begin;
	for (size_t i = begin; i < end; ++i)
	{
		if (nodes[i]->key < pivot)
			swap(nodes[lower++], nodes[i]);
	}

	sort(nodes, begin, lower);
	sort(nodes, lower, end);
}

void x_node::rebuild(const vector<node *> & nodes, size_t begin, size_t end)
{
	y_tree.clear();

	vector<node *> y_nodes;
	y_nodes.reserve(end - begin);

	for (size_t i = begin; i < end; ++i)
	{
		assert(nodes[i]);
		y_nodes.push_back(new y_node(nodes[i]->data));
	}

	sort(y_nodes, 0, y_nodes.size());

	y_tree.build_from_sorted(y_nodes);
}

node::~node()
{
	delete left;
	delete right;
}

}