#include "node.h"
#include "bba_tree.h"
#include "vector.h"
#include <utility>

namespace range
{
void x_node::insert(const point & p, size_t & steps)
{
	y_node * y_point = new y_node(p);
	y_tree.insert(y_point, steps);
}

void sort(vector<node *> & nodes, size_t begin, size_t end)
{
	if (end - begin <= 1)
		return;
	size_t mid = (begin + end) / 2;

	data_t pivot = nodes[mid]->key;
	std::swap(nodes[mid], nodes[end - 1]);
	size_t lower = begin;
	for (size_t i = begin; i < end - 1; ++i)
	{
		if (nodes[i]->key < pivot)
			std::swap(nodes[lower++], nodes[i]);
	}

	std::swap(nodes[lower], nodes[end - 1]);

	sort(nodes, begin, lower);
	sort(nodes, lower+1, end);
}

void x_node::rebuild(const vector<node *> & nodes, size_t begin, size_t end, size_t & steps)
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
	steps += end - begin; //we created that much nodes and visited them all during rebuild
}

bool x_node::y_satisfies(data_t y_begin, data_t y_end)
{
	return bba_tree::in_range(data.y, y_begin, y_end);
}

size_t x_node::count(data_t y_begin, data_t y_end, size_t & steps)
{
	return y_tree.range_count(y_begin, y_end, 0, 0, steps);
	//the y_begin and y_end are never used in the y tree
}

node::~node()
{
	delete left;
	delete right;
}

}