#include <iostream>
#include <fstream>
#include "JSON_lib.h"
using namespace std;
using namespace JSON_Lib;

void write_using_iterator(JSON& js) {
	auto it = js.get_iterator();
	stack<int> was;
	was.push(0);
	while (!was.empty()) {
		if (it.current_type() == IValueType::Value) {
			cout << '\"' << it.current_value() << "\"";
			it.go_up();
			was.pop();
			if (it.can_go_next())
				cout << ',';
			cout << '\n';
		}
		else if (it.current_type() == IValueType::ListValue) {
			if (was.top()) {
				if (it.can_go_next()) {
					it.go_next();
					was.top() = 0;
				}
				else {
					was.pop();
					if (it.can_go_up())
						it.go_up();
					cout << string(was.size() * 4, ' ');
					cout << '}';
					if (it.can_go_next())
						cout << ',';
					cout << '\n';
				}
			}
			else {
				if (!it.can_go_prev())
					cout << "{\n";
				cout << string(was.size() * 4, ' ');
				cout << '\"' << it.current_key() << "\": ";
				was.top() = 1;
				was.push(0);
				it.go_down();
			}
		}
	}
}

int main() {
	fstream in;

	JSON js{};

	cout << "TEST 1 :\n";
	in.open("test_files/test1.json");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 2 :\n";
	in.open("test_files/test2.json");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 3 :\n";
	in.open("test_files/test3.json");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 4 :\n";
	in.open("test_files/test4.json");
	js.read(in);
	js.write(cout);
	cout << endl;
	in.close();

	cout << "TEST 5: (file 4)" << endl;
	in.open("test_files/test4.json");
	js.read(in);
	write_using_iterator(js);
	//js.write(cout);
	cout << endl;
	in.close();

	JSON_Iterator iter = js.get_iterator();
	cout << "List of commands: \n";
	cout << "0.current_type  1.current_list  2.current_key  3.current_value \n";
	cout << "4.can_go_up     5.can_go_down   6.can_go_prev  7.can_go_next   \n";
	cout << "8.go_up         9.go_down      10.go_prev     11.go_next       \n";
	while (true) {
		cout << "input command: "; cout.flush();
		int c; cin >> c;
		try {
			switch (c)
			{
			case 0: {
				auto o = iter.current_type();
				cout << "current type: ";
				if (o == IValueType::Value)
					cout << "Value" << endl;
				else
					cout << "ListValue" << endl;
			}
				break;
			case 1: {
				auto v = iter.current_list();
				cout << "current list:\n";
				for (auto& s : v)
					cout << '\"' << s << '\"' << endl;
			}
				break;
			case 2: {
				auto k = iter.current_key();
				cout << "current key:\n";
				cout << '\"' << k << '\"' << endl;
			}
				break;
			case 3: {
				auto v = iter.current_value();
				cout << "current value:\n";
				cout << '\"' << v << '\"' << endl;
			}
				break;
			case 4: {
				cout << (iter.can_go_up() ? "True" : "False") << "\n";
			}
				break;
			case 5: {
				cout << (iter.can_go_down() ? "True" : "False") << "\n";
			}
				break;
			case 6: {
				cout << (iter.can_go_prev() ? "True" : "False") << "\n";
			}
				break;
			case 7: {
				cout << (iter.can_go_next() ? "True" : "False") << "\n";
			}
				break;
			case 8: {
				iter.go_up();
			}
				break;
			case 9: {
				iter.go_down();
			}
				break;
			case 10: {
				iter.go_prev();
			}
				break;
			case 11: {
				iter.go_next();
			}
				break;
			default:
				cout << "wrong_command\n";
				break;
			}
		}
		catch (const char* x) {
			cout << "error: " << x << "\n";
		}
	}

	return 0;
}
