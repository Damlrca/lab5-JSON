#include <iostream>
#include <fstream>
#include "JSON_lib.h"
using namespace std;
using namespace JSON_Lib;

int main() {
	fstream in;
	IValue* iv;

	cout << "TEST 1 :\n";
	in.open("test_files/test1.txt");
	iv = read_IValue(in);
	iv->write(cout);
	cout << endl;
	delete iv;
	in.close();

	cout << "TEST 2 :\n";
	in.open("test_files/test2.txt");
	iv = read_IValue(in);
	iv->write(cout);
	cout << endl;
	delete iv;
	in.close();

	cout << "TEST 3 :\n";
	in.open("test_files/test3.txt");
	iv = read_IValue(in);
	iv->write(cout);
	cout << endl;
	delete iv;
	in.close();

	cout << "TEST 4 :\n";
	in.open("test_files/test4.txt");
	iv = read_IValue(in);
	iv->write(cout);
	cout << endl;
	delete iv;
	in.close();

	return 0;
}
