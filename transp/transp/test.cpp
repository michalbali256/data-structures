#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "matrix.h"

using namespace transp;

class Matrix {
	//transpose imput matrix
private:
	int LIMIT = 2;
	int* matrix;
	int size;
	std::string filename;
	bool writeToFile;

public:
	//transpose matrix *m of size s
	//boolean wtf - whether write to file specified in filename
	//boolean transSimple determines whether transpose matrix simple or recursively
	void transpose(int *m, int s, bool wft, bool transSimple);
	std::ofstream fileWriter;
private:
	//transpose matrix recursively
	void transposeMatrix(int fromRow, int toRow, int fromColumn, int toColumn) {
		if (toRow - fromRow < LIMIT || toColumn - fromColumn < LIMIT) {
			transposeSimpleSubmatrix(fromRow, toRow, fromColumn, toColumn);
		}
		else
		{
			int middleRow = (toRow + fromRow) / 2;
			int middleColumn = (toColumn + fromColumn) / 2;

			transposeMatrix(fromRow, middleRow, fromColumn, middleColumn);
			transposeAndSwap(middleRow, toRow, fromColumn, middleColumn); //, fromRow, middleRow, middleColumn+1, toColumn);
			transposeMatrix(middleRow, toRow, middleColumn, toColumn);

		}
	}

	//simple submatrix transposition
	void transposeSimpleSubmatrix(int fromRow, int toRow, int fromColumn, int toColumn)
	{
		for (int i = fromRow; i < toRow; i++)
		{
			for (int j = fromColumn; j < toColumn; j++)
			{
				if (i != j)
				{
					swap(i, j);
				}
			}
		}
	}

	//swap elements on position i and j in matrix
	void swap(int i, int j)
	{
		if (writeToFile)
		{
			fileWriter << "X " << i << " " << j << " " << j << " " << i << "\n";
		}
		else
		{
			int tmp = matrix[i*size + j];
			matrix[i*size + j] = matrix[j*size + i];
			matrix[j*size + i] = tmp;

		}
	}

	//simple matrix transposition
	void transposeSimpleMatrix(int fromRow, int toRow, int fromColumn, int toColumn) {

		for (int i = fromRow; i < toRow; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(i, j);
			}
		}
	}

	//transpose and swap recursively
	void transposeAndSwap(int fromRow, int toRow, int fromColumn, int toColumn)
	{
		if (toRow - fromRow < LIMIT || toColumn - fromColumn < LIMIT)
		{
			transposeSimpleSubmatrix(fromRow, toRow, fromColumn, toColumn);
		}
		else
		{
			int middleRow = (toRow + fromRow) / 2;
			int middleColumn = (toColumn + fromColumn) / 2;

			transposeAndSwap(fromRow, middleRow, fromColumn, middleColumn);
			transposeAndSwap(fromRow, middleRow, middleColumn, toColumn);
			transposeAndSwap(middleRow, toRow, fromColumn, middleColumn);
			transposeAndSwap(middleRow, toRow, middleColumn, toColumn);
		}
	}
};


void Matrix::transpose(int *m, int s, bool wtf, bool transSimple)
{
	size = s;
	matrix = m;
	writeToFile = wtf;
	if (transSimple) {
		transposeSimpleMatrix(0, size, 0, size);
	}
	else {
		transposeMatrix(0, size, 0, size);
	}
}

int main(int argc, char * * argv)
{   
    vector<uint32_t> data;
	vector<uint32_t> check;
	for (size_t n = 5; n < 1000; ++n)
	{
		std::cout << n << "\n";
		data.resize(n*n);
		check.resize(n*n);
		for (int i = 0; i < data.size(); ++i)
		{
			data[i] = i;
			check[i] = i;
		}

		Matrix mt;
		
		mt.transpose((int *)&data[0], n, false, false);

		

		matrix<noop_writer> mtn(&check, n);
		mtn.naive_transpose();

		for (size_t i = 0; i < n*n; ++i)
		{
			if (check[i] != data[i])
				std::cout << "error" << "\n";
		}

		/*for(int i = 0; i < n; ++i)
		{

			for(size_t j = 0; j < n; j++)
			{
				std::cout << m.at(j, i) << " ";
			}
			std::cout << "\n";
		}*/

		
	}

}
