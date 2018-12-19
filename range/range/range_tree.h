#ifndef DATA_STRUCTURES_RANGE_RANGE_TREE_H
#define DATA_STRUCTURES_RANGE_RANGE_TREE_H

// range_tree::insert --> bba_tree::insert --> (x)node::insert --> bba_tree::insert --> (y)node::insert (nothing)
// 

namespace range
{

using data_t = size_t;

struct point
{
    data_t x;
    data_t y;
};

struct node;

class bba_tree
{
public:
    void insert(node * p);
private:
    void rebuild();    
};

struct node
{
    data_t key;
    node * left;
    node * right;
    point p;
    
    virtual void insert();
};

struct x_node : public node
{
    bba_tree y_tree;
    
    virtual void insert() override;
};

struct y_node : public node
{
    virtual void insert() override {}
};




class range_tree
{
    void insert(data_t x, data_t y);
    void range_count(data_t x_begin, data_t x_end, data_t y_begin, data_t y_end);
    
    
};



}

#endif