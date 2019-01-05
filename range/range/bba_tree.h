#ifndef DATA_STRUCTURES_RANGE_BBA_TREE_H
#define DATA_STRUCTURES_RANGE_BBA_TREE_H

#include "vector.h"

namespace range 
{

struct node;

using data_t = size_t;

class bba_tree
{
public:
    bba_tree(double alpha) : alpha_(alpha) {}

    void insert(node * p);
	void clear();
	void build_from_sorted(vector<node *> & nodes);

	size_t range_count(data_t x_begin, data_t x_end, data_t y_begin, data_t y_end) const;

	static bool in_range(data_t x, data_t begin, data_t end);

	~bba_tree();
private:
    void rebuild(node *& to_rebuild);
	bool check_bba_invariant(node * n);

    double alpha_;
    node * root_ = nullptr;
};

}

#endif