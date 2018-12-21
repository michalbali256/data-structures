#include "bba_tree.h"
#include "node.h"

namespace range
{

void bba_tree::insert(node * p)
{
    if(root_ == nullptr)
    {
        root_ = p;
        p->left = nullptr;
        p->right = nullptr;
        p->size = 1;
        p->insert(p->data);
        return;
    }
    
    node * mom = root_;
    node * prev;
    
    while(mom)
    {
        prev = mom;
        mom->insert(p->data);
        if(p->key > mom->key)
            mom = mom->right;//rebuild?
        else
            mom = mom->left;
        
        
    }
}

    

}