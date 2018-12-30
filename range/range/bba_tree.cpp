#include "bba_tree.h"
#include "node.h"

namespace range
{
void bba_tree::rebuild(node * to_rebuild)
{

}

node * bba_tree::check_and_rebuild(size_t parent_size, node * child, node * to_insert)
{
	if (parent_size * alpha_ >= child->size + 1)
		return; //bb alpha invariant holds, no rebuilding
	
	//now take all child points, put them into array

	//return rebuild(array)
}

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
    node * parent;
	node *& rebuild_root = root_;
	node *& child_ptr = root_;
	bool rebuild = false;
    while(mom)
    {
		++mom->size;
		
		if (!rebuild && parent->size * alpha_ >= mom->size)
		{
			rebuild = true;
			rebuild_root = child_ptr;//bb alpha invariant holds after the insertion, no rebuilding
		}

        parent = mom;
        mom->insert(p->data);
		
		if (p->key > mom->key)
		{
			child_ptr = mom->right;
			mom = mom->right;
		}
		else
		{
			child_ptr = mom->left;
			mom = mom->left;
		}
        
		
        
    }

	child_ptr = p;

	if (rebuild_root)
		rebuild(rebuild_root);


}

    

}