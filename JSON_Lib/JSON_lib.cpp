#include "JSON_lib.h"

namespace JSON_Lib {
	// >----------<
	//     Link    
	// >----------<

	Link::Link(const Link& l) {
		key = l.key;
		if (l.val)
			val = l.val->copy();
		else
			val = nullptr;
		if (l.nxt)
			nxt = new Link(*l.nxt);
		else
			nxt = nullptr;
	}
	
	Link& Link::operator=(const Link& l) {
		if (this == &l)
			return *this;
		key = l.key;
		delete val;
		val = nullptr;
		if (l.val)
			val = l.val->copy();
		delete nxt;
		nxt = nullptr;
		if (l.nxt)
			nxt = new Link(*l.nxt);
		return *this;
	}
	
	// >---------------<
	//     ListValue    
	// >---------------<

	ListValue::ListValue(const ListValue& l) {
		if (l.start) {
			start = new Link(*l.start);
			last = start;
			while (last->nxt)
				last = last->nxt;
		}
		else {
			start = last = nullptr;
		}
	}

	ListValue& ListValue::operator=(const ListValue& l) {
		if (this == &l)
			return *this;
		clear();
		if (l.start) {
			start = new Link(*l.start);
			last = start;
			while (last->nxt)
				last = last->nxt;
		}
		else {
			start = last = nullptr;
		}
		return *this;
	}

	void ListValue::add(const std::string& key, IValue* val) {
		if (start) {
			last->nxt = new Link(key, val);
			last = last->nxt;
		}
		else {
			last = start = new Link(key, val);
		}
	}

	// >--------------------<
	//     read functions
	// >--------------------<

	std::string read_JSONstring(std::istream& in) {
		std::string res;
		char c;
		if (!(in >> c) || c != '\"')
			throw "read_JSONstring: '\"' expected";
		while (in.get(c) && c != '\"')
			res += c;
		if (c != '\"')
			throw "read_JSONstring: '\"' expected";
		return res;
	}

	IValue* read_IValue(std::istream& in) {
		char first_symbol;
		if (!(in >> first_symbol))
			throw "read_IValue: nothing to read";
		if (first_symbol == '{') { // ListValue
			ListValue* res = new ListValue{};
			char c;
			int count = 0;
			try {
				do {
					if (!(in >> c))
						throw "read_IValue: eof";
					if (c == ',' && count == 0)
						throw "read_IValue: '\"' expected";
					if (c == ',' && (!(in >> c) || c != '\"'))
						throw "read_IValue: '\"' expected";
					if (c != '}' && c != '\"')
						throw "read_IValue: unexpected symbol";
					if (c == '}')
						continue; // or break?
					in.unget();
					std::string key = read_JSONstring(in);
					if (!(in >> c) || c != ':')
						throw "read_IValue: ':' expected";
					IValue* iv = read_IValue(in);
					res->add(key, iv);
					count++;
				} while (c != '}');
			}
			catch (...) {
				delete res;
				throw;
			}
			return res;
		}
		else if (first_symbol == '\"') { // Value
			in.unget();
			std::string t = read_JSONstring(in);
			return new Value(t);
		}
		else {
			throw "read_IValue: wrong first symbol";
		}
	}

	// >----------------------------<
	//     IValue write functions    
	// >----------------------------<

	void Value::write(std::ostream& out, int level) // 'level' not used
	{
		out << '\"' << this->value << '\"';
	}

	void ListValue::write(std::ostream& out, int level)
	{
		std::string offset(level * 4, ' ');
		out << "{\n";
		for (Link* t = start; t != nullptr; t = t->nxt) {
			out << offset << "    \"" << t->key << "\": ";
			t->val->write(out, level + 1);
			if (t != last)
				out << ",";
			out << "\n";
		}
		out << offset << "}";
	}
}
