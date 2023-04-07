#include "JSON_lib.h"

namespace JSON_Lib {
	// Link

	Link::Link(const Link& l) {
		switch (l.val->get_type())
		{
		case ValueType::Value:
			val = new Value(l.val);
			break;
		case ValueType::ListValue:
			val = new ListValue(l.val);
			break;
		default:
			val = nullptr;
			break;
		}
		if (l.nxt) {
			nxt = new Link(*l.nxt);
		}
		else {
			nxt = nullptr;
		}
		key = l.key;
	}
	
	Link& Link::operator=(const Link& l) {
		if (this == &l)
			return *this;
		delete val;
		val = nullptr;
		switch (l.val->get_type())
		{
		case ValueType::Value:
			val = new Value(l.val);
			break;
		case ValueType::ListValue:
			val = new ListValue(l.val);
			break;
		default:
			val = nullptr;
			break;
		}
		delete nxt;
		nxt = nullptr;
		if (l.nxt) {
			nxt = new Link(*l.nxt);
		}
		key = l.key;
		return *this;
	}

	// ListValue

	ListValue::ListValue(const ListValue& v) {
		if (v.start) {
			start = new Link(*v.start);
			last = start;
			while (last->nxt)
				last = last->nxt;
		}
		else {
			start = last = nullptr;
		}
	}

	ListValue::ListValue(IValue* iv) {
		if (iv->get_type() != ValueType::ListValue)
			throw "ListValue(IValue*): IValue type isn't ListValue";
		if (((ListValue*)iv)->start) {
			start = new Link(*(((ListValue*)iv)->start));
			last = start;
			while (last->nxt)
				last = last->nxt;
		}
		else {
			start = last = nullptr;
		}
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

	std::string read_key(std::istream& in) {
		std::string res;
		char c;
		if (!(in >> c) || c != '\"')
			throw "read_key: '\"' expected";
		while (in.get(c) && c != '\"')
			res += c;
		if (c != '\"')
			throw "read_key: '\"' expected";
		return res;
	}

	IValue* read_IValue(std::istream& in) {
		char first_symbol;
		if (!(in >> first_symbol))
			throw "read_IValue: nothing to read";
		if (first_symbol == '{') {
			// ListValue
			ListValue* res = new ListValue{};
			char c;
			int cnt = 0;
			do {
				if (!(in >> c))
					throw "read_IValue: eof";
				if (c == ',' && cnt == 0)
					throw "read_IValue: '\"' expected";
				if (c == ',' && (!(in >> c) || c != '\"'))
					throw "read_IValue: '\"' expected";
				if (c != '}' && c != '\"')
					throw "read_IValue: unexpected symbol";
				if (c == '}')
					continue;
				in.unget();
				std::string key = read_key(in);
				if (!(in >> c) || c != ':')
					throw "read_IValue: ':' expected";
				IValue* iv = read_IValue(in);
				res->add(key, iv);
				cnt++;
			} while (c != '}');
			return res;
		}
		else if (first_symbol == '\"') {
			// Value
			in.unget();
			std::string t = read_key(in);
			Value* v = new Value(t);
			return v;
		}
		else {
			throw "read_IValue: wrong first symbol";
		}
	}

	void Value::write(std::ostream& out, int level)
	{
		out << '\"' << this->value << '\"';
	}

	void ListValue::write(std::ostream& out, int level)
	{
		std::string temp(level * 4, ' ');
		out << "{\n";
		for (Link* t = start; t != nullptr; t = t->nxt) {
			out << temp << "    " << "\"" << t->key << "\": ";
			t->val->write(out, level + 1);
			if (t != last)
				out << ",\n";
			else
				out << "\n";
		}
		out << temp << "}";
	}
}
