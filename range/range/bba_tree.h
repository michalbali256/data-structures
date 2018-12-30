#ifndef DATA_STRUCTURES_RANGE_BBA_TREE_H
#define DATA_STRUCTURES_RANGE_BBA_TREE_H

namespace range 
{

struct node;

class bba_tree
{
public:
    bba_tree(double alpha) : alpha_(alpha) {}

    void insert(node * p);
    
    
private:
    void rebuild(node * to_rebuild);
	node * check_and_rebuild(size_t parent_size, node * child, node * to_insert);

    double alpha_;
    node * root_;
};

}

#endif