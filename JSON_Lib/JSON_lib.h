#ifndef _JSON_Lib
#define _JSON_Lib

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <utility>

namespace JSON_Lib {
	class IValue {
	public:
		virtual void write(std::ostream& out, int level = 0) = 0;
		virtual IValue* copy() = 0;
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
		std::string get_val() { return value; }
		Value& operator=(const Value&) = default;
		~Value() = default;
		void write(std::ostream& out, int level = 0);
		IValue* copy() { return new Value(*this); }
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
		ListValue() : start(nullptr), last(nullptr) {}
		ListValue(const ListValue& v);
		void add(const std::string& key, IValue* val);
		void clear() {
			delete start;
			start = last = nullptr;
		}
		~ListValue() {
			clear();
		}
		void write(std::ostream& out, int level = 0);
		IValue* copy() { return new ListValue(*this); }
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
			while (!s.empty() && dynamic_cast<Value*>(s.top().first) == nullptr) {
				if (s.top().second == nullptr) {
					s.top().second = dynamic_cast<ListValue*>(s.top().first)->start;
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
			std::string t;
			if (auto v = dynamic_cast<Value*>(s.top().first)) {
				t = v->get_val();
			}
			else {
				throw "";
			}
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
			if (auto lv = dynamic_cast<ListValue*>(temp)) {
				delete iv;
				iv = lv;
			}
			else {
				throw "JSON.read(): expected ListValue";
			}
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
