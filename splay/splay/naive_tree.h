#ifndef DATA_STRUCTURES_SPLAY_NAIVE_TREE_H
#define DATA_STRUCTURES_SPLAY_NAIVE_TREE_H

#include "tree.h"

namespace splay
{

class naive_tree : public tree
{
public:
    
    //splays the node at the back of locate_path up the path
    virtual void splay() override
    {
        assert(locate_path.size() > 0);
        node * new_tree = locate_path[locate_path.size() - 1].n;
        for(size_t i = locate_path.size() - 2; i != (size_t)-1; --i)
        {
            if(locate_path[i].d == dir::L)
			    rotate_right(locate_path[i].n, new_tree);
            else
                rotate_left(locate_path[i].n, new_tree);
        }

		root_ = new_tree;
    }
private:
};

}

#endif