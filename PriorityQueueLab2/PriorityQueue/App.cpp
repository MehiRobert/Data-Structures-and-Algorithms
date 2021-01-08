#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <crtdbg.h>

using namespace std;




int main() {
	testAll();
	testAllExtended();
	_CrtDumpMemoryLeaks();
	cout << "End" << endl;
	system("pause");

}
