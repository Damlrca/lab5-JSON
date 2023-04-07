#include <iostream>
#include <fstream>
#include "JSON_lib.h"
using namespace std;
using namespace JSON_Lib;

int main() {
	fstream in;

	JSON js{};

	cout << "TEST 1 :\n";
	in.open("test_files/test1.txt");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 2 :\n";
	in.open("test_files/test2.txt");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 3 :\n";
	in.open("test_files/test3.txt");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 4 :\n";
	in.open("test_files/test4.txt");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	return 0;
}
