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

	cout << "TEST 5 (file4) :\n";
	in.open("test_files/test4.txt");
	js.read(in);
	JSON_Iterator ji = js.get_iterator();
	while (ji.has_next()) {
		auto v = ji.get_keys();
		for (auto s : v)
			cout << s << ":";
		cout << '\"' << ji.next() << '\"' << "\n";
	}
	cout << endl;
	in.close();

	cout << "TEST 6 (file2) :\n";
	in.open("test_files/test2.txt");
	js.read(in);
	JSON_Iterator ji2 = js.get_iterator();
	while (ji2.has_next()) {
		auto v = ji2.get_keys();
		for (auto s : v)
			cout << s << ":";
		cout << '\"' << ji2.next() << '\"' << "\n";
	}
	cout << endl;
	in.close();

	return 0;
}
