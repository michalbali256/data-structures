#ifndef DATA_STRUCTURES_SPLAY_SPLAY_TREE_H
#define DATA_STRUCTURES_SPLAY_SPLAY_TREE_H

#include "tree.h"

namespace splay
{

class splay_tree : public tree
{
    
    /*
    *       A              X
    *      / \            / \
    *     B  T4          T1  B
    *    / \       ->       / \
    *   X  T3              T2  A
    *  / \                    / \
    * T1 T2                  T3 T4
    */
    
    void zig_zig_right(node * a, node * x)
    {
        node * b, * t2, * t3;
        assert(a);
        assert(x);
        b = a->left;
        assert(b);
        t2 = x->right;
        t3 = b->right;
        
        x->right = b;
        b->left = t2;
        b->right = a;
        a->left = t3;
    }
    
    /*
    *    A                X
    *   / \              / \
    *  T1  B            B  T4
    *     / \    ->    / \
    *    T2  X        A  T3 
    *       / \      / \
    *      T3 T4    T1 T2
    */
    
    void zig_zig_left(node * a, node * x)
    {
        node * b, * t2, * t3;
        assert(a);
        assert(x);
        b = a->right;
        assert(b);
		t2 = b->left;
        t3 = x->left;
        
        x->left = b;
        b->left = a;
        b->right = t3;
        a->right = t2;
    }
    
    
    
public:
    //splays the node at the back of locate_path up the path
    virtual void splay() override
    {
        assert(locate_path.size() > 0);
        node * new_tree = locate_path[locate_path.size() - 1].n;
        size_t i;
        for(i = locate_path.size() - 3; i != (size_t)-1 && i != (size_t)-2; i -= 2)
        {
            if(locate_path[i].d == dir::L && locate_path[i+1].d == dir::L)
                zig_zig_right(locate_path[i].n, new_tree);
            else if (locate_path[i].d == dir::R && locate_path[i+1].d == dir::R)
                zig_zig_left(locate_path[i].n, new_tree);
            else if (locate_path[i].d == dir::R && locate_path[i+1].d == dir::L)
            {
                rotate_right(locate_path[i+1].n, new_tree);
                rotate_left(locate_path[i].n, new_tree);
            }
            else // if (locate_path[i].d == dir::L && locate_path[i+1].d == dir::R)
            {
                rotate_left(locate_path[i+1].n, new_tree);
                rotate_right(locate_path[i].n, new_tree);                
            }
        }
        
        if(i == (size_t)-1)
        {
            if(locate_path[0].d == dir::L)
                rotate_right(root_, new_tree);
            else
                rotate_left(root_, new_tree);
        }
        
		root_ = new_tree;
    }
private:
};

}

#endif