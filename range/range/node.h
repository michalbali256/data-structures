#ifndef DATA_STRUCTURES_RANGE_NODE_H
#define DATA_STRUCTURES_RANGE_NODE_H

#include <cstddef> 
#include "bba_tree.h"
#include "vector.h"

namespace range
{



struct point
{
	point() : x(), y() {}
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
    virtual void insert(const point & p, size_t & steps) = 0;
	virtual void rebuild(const vector<node *> & nodes, size_t begin, size_t end, size_t & steps) = 0;

	virtual bool y_satisfies(data_t y_begin, data_t y_end) = 0;
	virtual size_t count(data_t y_begin, data_t y_end, size_t & steps) = 0;
	virtual ~node() = 0;

protected:
	node(const point & p, data_t key) : key(key), data(p), left(), right(), size() {}
};
struct x_node : public node
{
	x_node(const point & p, double alpha) : node(p, p.x), y_tree(alpha) {}

    bba_tree y_tree;
    
    virtual void insert(const point & p, size_t & steps) override;
	virtual void rebuild(const vector<node *> & nodes, size_t begin, size_t end, size_t & steps) override;
	virtual bool y_satisfies(data_t y_begin, data_t y_end) override;
	virtual size_t count(data_t y_begin, data_t y_end, size_t & steps) override;

};

struct y_node : public node
{
	y_node(const point & p) : node(p, p.y) {}

    virtual void insert(const point &, size_t &) override {}
	virtual void rebuild(const vector<node *> &, size_t, size_t, size_t &) override {};
	virtual bool y_satisfies(data_t, data_t) override { return true; };
	virtual size_t count(data_t, data_t, size_t &) override { return size; };
};    

    
}

#endif