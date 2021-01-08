#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() {
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 3, 6);
	m.modify(1, 3, 0);
	assert(m.element(1, 3) == NULL_TELEM);
	assert(m.element(1, 2) == NULL_TELEM);
	m.modify(1, 5, 2);
	m.modify(1, 4, 5);
	assert(m.numberOFNonZeroRows(1) == 3);
}