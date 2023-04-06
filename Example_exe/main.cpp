#include <iostream>
#include <fstream>
#include "JSON_lib.h"
using namespace std;
using namespace JSON_Lib;

int main() {
	fstream in("test.txt");
	IValue* iv = read_IValue(in);
	iv->write(cout);
	cout << endl;
	return 0;
}
