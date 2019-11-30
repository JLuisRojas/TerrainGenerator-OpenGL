#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>

#include "objects.h"

using namespace std;

int main(int argc, char **argv) {
	vector<Object> objs = readObjFile(argv[1]);

	for(int i = 0; i < objs.size(); i++) {
		objs[i].Print();
		cout << endl;
	}
}
