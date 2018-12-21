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
    void insert(data_t x, data_t y);
    void range_count(data_t x_begin, data_t x_end, data_t y_begin, data_t y_end);
};



}

#endif