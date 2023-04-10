#include "JSON_lib.h"

namespace JSON_Lib {
	// >----------<
	//     Link    
	// >----------<

	Link::Link(const Link& l) {
		prev = nullptr;
		key = l.key;
		if (l.val)
			val = l.val->copy();
		else
			val = nullptr;
		if (l.next) {
			next = new Link(*l.next);
			next->prev = this;
		}
		else
			next = nullptr;
	}
	
	Link& Link::operator=(const Link& l) {
		if (this == &l)
			return *this;
		prev = nullptr;
		key = l.key;
		delete val;
		val = nullptr;
		if (l.val)
			val = l.val->copy();
		delete next;
		next = nullptr;
		if (l.next) {
			next = new Link(*l.next);
			next->prev = this;
		}
		return *this;
	}
	
	// >---------------<
	//     ListValue    
	// >---------------<

	ListValue::ListValue(const ListValue& l) {
		if (l.start) {
			start = new Link(*l.start);
			last = start;
			while (last->next)
				last = last->next;
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
			while (last->next)
				last = last->next;
		}
		else {
			start = last = nullptr;
		}
		return *this;
	}

	void ListValue::add(const std::string& key, IValue* val) {
		if (last) {
			last->next = new Link(key, val, nullptr, last);
			last = last->next;
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
		for (Link* t = start; t != nullptr; t = t->next) {
			out << offset << "    \"" << t->key << "\": ";
			t->val->write(out, level + 1);
			if (t != last)
				out << ",";
			out << "\n";
		}
		out << offset << "}";
	}

	// >----------<
	//     JSON    
	// >----------<

	JSON_Iterator JSON::get_iterator() {
		if (root)
			return JSON_Iterator(root);
		else
			throw "JSON.get_iterator(): empty JSON";
	}

	void JSON::read(std::istream& in) {
		IValue* temp = read_IValue(in);
		if (temp->get_type() == IValueType::ListValue) {
			clear();
			root = static_cast<ListValue*>(temp);
		}
		else {
			throw "JSON.read(): expected ListValue";
		}
	}

	void JSON::write(std::ostream& out) {
		if (root == nullptr)
			throw "JSON.write(): empty JSON";
		root->write(out);
	}

	// >-------------------<
	//     JSON_Iterator    
	// >-------------------<

	bool JSON_Iterator::can_go_up() {
		return s.size() > 1;
	}

	void JSON_Iterator::go_up() {
		if (!can_go_up())
			throw "";
		s.pop();
	}

	bool JSON_Iterator::can_go_down() {
		return s.top().second != nullptr;
	}

	void JSON_Iterator::go_down() {
		if (!can_go_down())
			throw "";
		auto iv = s.top().second->val;
		if (iv->get_type() == IValueType::ListValue)
			s.push({ iv, static_cast<ListValue*>(iv)->start });
		else if (iv->get_type() == IValueType::Value)
			s.push({ iv, nullptr });
	}

	bool JSON_Iterator::can_go_prev() {
		if (s.top().second == nullptr)
			throw "";
		return s.top().second->prev != nullptr;
	}

	void JSON_Iterator::go_prev() {
		if (!can_go_prev())
			throw "";
		s.top().second = s.top().second->prev;
	}

	bool JSON_Iterator::can_go_next() {
		if (s.top().second == nullptr)
			throw "";
		return s.top().second->next != nullptr;
	}

	void JSON_Iterator::go_next() {
		if (!can_go_next())
			throw "";
		s.top().second = s.top().second->next;
	}
}
