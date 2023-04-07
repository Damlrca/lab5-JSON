#ifndef _JSON_Lib
#define _JSON_Lib

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <utility>

namespace JSON_Lib {
	enum class ValueType {
		Value,
		ListValue
	};

	class IValue {
	public:
		virtual ValueType get_type() = 0;
		virtual std::string get_val() = 0;
		virtual void write(std::ostream& out, int level = 0) = 0;
	};

	std::string read_key(std::istream& in);

	IValue* read_IValue(std::istream& in);

	class Value : public IValue {
	private:
		std::string value;
	public:
		Value() = default;
		Value(const Value&) = default;
		Value(const std::string& _val) : value(_val) {}
		Value(IValue* iv) {
			if (iv->get_type() != ValueType::Value)
				throw "Value(IValue*): IValue type isn't Value";
			value = iv->get_val();
		}
		ValueType get_type() { return ValueType::Value; }
		std::string get_val() { return value; }
		Value& operator=(const Value&) = default;
		~Value() = default;
		void write(std::ostream& out, int level = 0);
		friend class JSON_Iterator;
	};

	struct Link {
		std::string key;
		IValue* val;
		Link* nxt;
		Link(const std::string& _key, IValue* _val, Link* _nxt = nullptr)
			: key(_key), val(_val), nxt(_nxt) {}
		Link(const Link& l);
		Link& operator=(const Link& l);
		~Link() {
			delete nxt;
			delete val;
		}
	};

	class ListValue : public IValue {
	private:
		Link* start;
		Link* last;
	public:
		ValueType get_type() { return ValueType::ListValue; }
		std::string get_val() { throw "ListValue doesn't have value"; }
		ListValue() : start(nullptr), last(nullptr) {}
		ListValue(const ListValue& v);
		ListValue(IValue* iv);
		void add(const std::string& key, IValue* val);
		void clear() {
			delete start;
			start = last = nullptr;
		}
		~ListValue() {
			clear();
		}
		void write(std::ostream& out, int level = 0);
		friend class JSON_Iterator;
		Link* get_start() {
			return start;
		}
	};

	class JSON_Iterator {
		std::stack<std::pair<IValue*, Link*>> s;
		std::vector<std::string> keys;
	public:
		JSON_Iterator(IValue* _iv) {
			s.push({ _iv, nullptr });
		}
		void skip_to_next() {
			while (!s.empty() && s.top().first->get_type() != ValueType::Value) {
				if (s.top().second == nullptr) {
					s.top().second = ((ListValue*)s.top().first)->start;
					keys.push_back(s.top().second->key);
					s.push({ s.top().second->val, nullptr });
				}
				else {
					s.top().second = s.top().second->nxt;
					if (s.top().second == nullptr) {
						s.pop();
						if (!keys.empty())
							keys.pop_back();
					}
					else {
						keys.push_back(s.top().second->key);
						s.push({ s.top().second->val, nullptr });
					}
				}
			}
		}
		bool has_next() {
			skip_to_next();
			return !s.empty();
		}
		std::string next() {
			skip_to_next();
			std::string t = s.top().first->get_val();
			s.pop();
			if (!keys.empty())
				keys.pop_back();
			return t;
		}
		std::vector<std::string> get_keys() {
			return keys;
		}
	};

	class JSON {
	private:
		ListValue* iv;
	public:
		JSON() : iv(nullptr) {}
		JSON(const JSON& js) {
			if (js.iv) {
				iv = new ListValue(*js.iv);
			}
			else {
				iv = nullptr;
			}
		}
		JSON_Iterator get_iterator() {
			return JSON_Iterator(iv);
		}
		void read(std::istream& in) {
			IValue* temp = read_IValue(in);
			if (temp->get_type() != ValueType::ListValue)
				throw "JSON.read(): expected ListValue";
			delete iv;
			iv = (ListValue*)temp;
		}
		void write(std::ostream& out) {
			if (iv == nullptr)
				throw "JSON.write(): empty JSON";
			iv->write(out);
		}
		JSON& operator=(const JSON& js) {
			if (this == &js)
				return *this;
			delete iv;
			iv = nullptr;
			iv = new ListValue(*js.iv);
			return *this;
		}
		IValue* get_root() {
			return iv;
		}
		~JSON() {
			delete iv;
		}
	};
}

#endif // !_JSON_Lib
