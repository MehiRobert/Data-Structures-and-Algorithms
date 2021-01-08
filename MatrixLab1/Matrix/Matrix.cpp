#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {

	this->lines = nrLines;
	this->columns = nrCols;
	this->capacity = 2;
	this->size = 0;

	this->lin = new int[this->capacity];
	this->col = new int[this->capacity];
	this->val = new int[this->capacity];
}
//BC=WC=AC=Theta(n) , Complexity : O(n = number of elements)
void Matrix::Resize()
{
	this->capacity = this->capacity * 2;
	
	int* auxLine = new int[this->capacity];
	int* auxcol = new int[this->capacity];
	int* auxval = new int[this->capacity];
	
	for (int i = 0; i < this->size; i++)
	{
		auxLine[i] = this->lin[i];
		auxcol[i] = this->col[i];
		auxval[i] = this->val[i];
	}
	delete[] this->lin;

	delete[] this->col;

	delete[] this->val;

	this->lin = auxLine;
	
	this->col = auxcol;

	this->val = auxval;
}

//BC=WC=AC=Theta(1) Complexity:O(1)
int Matrix::nrLines() const {
	return this->lines;
}

//BC=WC=AC = Theta(1) Complexity:O(1)
int Matrix::nrColumns() const {
	return this->columns;
}

int Matrix::numberOFNonZeroRows(int line) const
{
	int cnt = 0;
	if (line < 0 || this->lines <= line)
	for (int i = 0; i < this->size; i++)
	{
		if (this->lin[i] == line)
			cnt++;
	}
	return cnt;
}

//BC = Theta(1) , WC=AC = Theta(n) Complexity:O(n)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->lines || j < 0 || j >= this->columns)
		throw exception();
	for (int k = 0; k < this->size; k++)
	{
		if (this->lin[k] == i && this->col[k] == j)
			return this->val[k];
	}
	return NULL_TELEM;

}
//BC=WC=AC = Theta(n) Complexity:O(n)
TElem Matrix::modify(int i, int j, TElem e) {
	int op = 0;
	int posvalue = -1;
	if (i < 0 || i >= this->lines || j < 0 || j >= this ->columns)
		throw exception();
	if (this->size == this->capacity)
		Resize();
	//first we are searching to see what we have on the positions received as an input
	for (int k = 0; k < this->size; k++)
	{
		if (this->lin[k] == i && this->col[k] == j)
		{
			posvalue = k;
			break;
		}
	}
	//if the value of the element on position i and j is 0 and e is not 0 then we perform the add operation
	if (posvalue == -1 and e != NULL_TELEM)
	{
		this->lin[this->size] = i;
		this->col[this->size] = j;
		this->val[this->size] = e;
		this->size++;
	}
	// if the value of the element on position i and j is not 0 and e is 0 then we perform the remove operation
	else if (posvalue != -1 and e == NULL_TELEM)
	{
		for (int k = posvalue; k < this->size - 1; k++)
		{
			this->lin[k] = this->lin[k + 1];
			this->col[k] = this->col[k + 1];
			this->val[k] = this->val[k + 1];
		}
		this->size--;
	}
	// if both, the value of the element on pos. i and j and e are different from 0 then we just modify it's value
	else if (posvalue != -1 and e != NULL_TELEM)
	{
		this->val[posvalue] = e;
	}
	
}


