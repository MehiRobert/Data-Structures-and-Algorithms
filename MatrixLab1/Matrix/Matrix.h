#pragma once
#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	//dimensions of the matrix
	int lines, columns;
	//the capacity of the dynamyc arrays
	int capacity;
	//the number of elements in the dynamic array
	int size;

	//the three dynamic arrays
	int* lin;
	int* col;
	int* val;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//reallocating when the memory becomes too small
	void Resize();

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	int numberOFNonZeroRows(int line) const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};
