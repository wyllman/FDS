#include <iostream>

#include "Test.h"
#include "Deposit.h"

int main(int argc, char **argv) {
	Deposit dep(19, 20, 0.4, 0.1);
	Test t(dep, 5 * 60 * 60);
	t.run();
	t.plot();	
}
