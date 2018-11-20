#ifndef DATA_STRUCTURES_FIBB_FIBB_H
#define DATA_STRUCTURES_FIBB_FIBB_H

#include "vector.h"

namespace fibb
{

using key_t = uint32_t;
using id_t = uint32_t;



class fibb_heap
{


	void insert(key_t k, id_t id);

	void delete_min();

	void decrease_min(id_t id, key_t new_k);
};


}


#endif