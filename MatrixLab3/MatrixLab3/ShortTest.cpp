#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	m.modify(1, 3, 4);
	assert(m.element(1, 1) == 5);
	assert(m.element(1, 3) == 4);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
	assert(m.positionOf(4).first == 1);
	assert(m.positionOf(4).second == 3);
	assert(m.positionOf(2).first == -1);
	assert(m.positionOf(2).second == -1);

}