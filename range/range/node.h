#ifndef DATA_STRUCTURES_RANGE_NODE_H
#define DATA_STRUCTURES_RANGE_NODE_H

#include <cstddef> 
#include "bba_tree.h"

namespace range
{

using data_t = size_t;

struct point
{
    point(data_t x, data_t y) : x(x), y(y) {}
    data_t x;
    data_t y;
};

struct node
{
    data_t key;
    node * left;
    node * right;
    point data;
    size_t size;
    virtual void insert(const point & p);
    
    virtual ~node() {}
};
struct x_node : public node
{
    bba_tree y_tree;
    
    virtual void insert(const point & p) override;
};

struct y_node : public node
{
    virtual void insert(const point & p) override {}
};    

    
}

#endif