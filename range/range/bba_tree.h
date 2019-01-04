#ifndef DATA_STRUCTURES_RANGE_BBA_TREE_H
#define DATA_STRUCTURES_RANGE_BBA_TREE_H

#include "vector.h"

namespace range 
{

struct node;

class bba_tree
{
public:
    bba_tree(double alpha) : alpha_(alpha) {}

    void insert(node * p);
	void clear();
	void build_from_sorted(vector<node *> & nodes);

	~bba_tree();
private:
    void rebuild(node *& to_rebuild);
	bool check_bba_invariant(node * n);

    double alpha_;
    node * root_ = nullptr;
};

}

#endif