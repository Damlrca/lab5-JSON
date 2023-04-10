#ifndef _JSON_Lib
#define _JSON_Lib

#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <utility>

namespace JSON_Lib {
	enum class IValueType {
		Value,
		ListValue
	};

	class IValue {
	public:
		virtual void write(std::ostream& out, int level = 0) = 0;
		virtual IValue* copy() = 0;
		virtual IValueType get_type() = 0;
	};

	std::string read_JSONstring(std::istream& in);

	IValue* read_IValue(std::istream& in);

	class Value : public IValue {
	private:
		std::string value;
	public:
		Value() = default;
		Value(const Value&) = default;
		Value(const std::string& _val) : value(_val) {}
		Value& operator=(const Value&) = default;
		~Value() = default;

		std::string get_val() { return value; }

		void write(std::ostream& out, int level = 0);
		IValue* copy() { return new Value(*this); }
		IValueType get_type() { return IValueType::Value; }

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
		ListValue(const ListValue& l);
		ListValue& operator=(const ListValue& l);
		~ListValue() { clear(); }

		void add(const std::string& key, IValue* val);
		void clear() {
			delete start;
			start = last = nullptr;
		}

		void write(std::ostream& out, int level = 0);
		IValue* copy() { return new ListValue(*this); }
		IValueType get_type() { return IValueType::ListValue; }

		friend class JSON_Iterator;
		Link* get_start() { // delete later!
			return start;
		}
	};

	class JSON_Iterator {
	private:
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
		ListValue* root;
	public:
		JSON() : root(nullptr) {}
		JSON(const JSON& js) {
			if (js.root)
				root = new ListValue(*js.root);
			else
				root = nullptr;
		}
		JSON& operator=(const JSON& js) {
			if (this == &js)
				return *this;
			clear();
			if (js.root)
				root = new ListValue(*js.root);
			return *this;
		}
		~JSON() { clear(); }

		void clear() {
			delete root;
			root = nullptr;
		}
		JSON_Iterator get_iterator();
		void read(std::istream& in);
		void write(std::ostream& out);
		IValue* get_root() { // delete later!
			return root;
		}
	};
}

#endif // !_JSON_Lib
