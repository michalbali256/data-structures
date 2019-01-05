#ifndef DATA_STRUCTURES_RANGE_RANGE_TREE_H
#define DATA_STRUCTURES_RANGE_RANGE_TREE_H

// range_tree::insert --> bba_tree::insert --> (x)node::insert --> bba_tree::insert --> (y)node::insert (nothing)
// 

#include "bba_tree.h"
#include "node.h"

namespace range
{

class range_tree
{
	bba_tree x_tree;

public:
	range_tree(double alpha) : x_tree(alpha), alpha_(alpha) {}

    void insert(data_t x, data_t y);
    size_t range_count(data_t x_begin, data_t x_end, data_t y_begin, data_t y_end);

	double insert_avg();
	uint64_t insert_max();

	double count_avg();
	uint64_t count_max();

	void clear();
private:

	uint64_t insert_steps_ = 0;
	uint64_t insert_count_ = 0;
	uint64_t insert_max_ = 0;

	uint64_t count_steps_ = 0;
	uint64_t count_count_ = 0;
	uint64_t count_max_ = 0;
	

	double alpha_;
};



}

#endif