#ifndef DATA_STRUCTURES_RANGE_NODE_H
#define DATA_STRUCTURES_RANGE_NODE_H

#include <cstddef> 
#include "bba_tree.h"
#include "vector.h"

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
    virtual void insert(const point & p) = 0;
	virtual void rebuild(const vector<node *> & nodes, size_t begin, size_t end) = 0;
	virtual ~node() = 0;

protected:
	node(const point & p, data_t key) : key(key), data(p), left(), right(), size() {}
};
struct x_node : public node
{
	x_node(const point & p, double alpha) : node(p, p.x), y_tree(alpha) {}

    bba_tree y_tree;
    
    virtual void insert(const point & p) override;
	virtual void rebuild(const vector<node *> & nodes, size_t begin, size_t end) override;
};

struct y_node : public node
{
	y_node(const point & p) : node(p, p.y) {}

    virtual void insert(const point & ) override {}
	virtual void rebuild(const vector<node *> &, size_t, size_t) override {};
};    

    
}

#endif