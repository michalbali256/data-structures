#ifndef DATA_STRUCTURES_TRANSP_MATRIX_H
#define DATA_STRUCTURES_TRANSP_MATRIX_H

#include "vector.h"

namespace transp
{

class matrix
{
public:
	matrix(vector & data) : data_(data) {}


private:
	vector & data_;
};

}

#endif