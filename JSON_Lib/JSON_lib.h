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
		Link* next;
		Link* prev;

		Link(const std::string& _key, IValue* _val, Link* _nxt = nullptr, Link* _prv = nullptr)
			: key(_key), val(_val), next(_nxt), prev(_prv) {}
		Link(const Link& l);
		Link& operator=(const Link& l);
		~Link() {
			delete next;
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

		bool is_empty() { return start == nullptr; }
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
		// ListValue: {IValue* , start}
		// Value: {IValue* , nullptr}
	public:
		JSON_Iterator(IValue* root) {
			if (root->get_type() == IValueType::ListValue)
				s.push({ root, static_cast<ListValue*>(root)->start });
			else if (root->get_type() == IValueType::Value)
				s.push({ root, nullptr });
		}
		// it is not safe to copy JSON_Iterator because another iterator can change something
		JSON_Iterator(const JSON_Iterator&) = default;
		// it is not safe to copy JSON_Iterator because another iterator can change something
		JSON_Iterator& operator=(const JSON_Iterator&) = default;
		~JSON_Iterator() = default;
		/*
		//TODO
		void back_to_root();
		void go_to_key(const std::string&)();
		}*/
		IValueType current_type() {
			return s.top().first->get_type();
		}
		bool current_list_is_empty() {
			if (current_type() != IValueType::ListValue)
				throw "current_list_is_empty(): expected that current_type() is ListValue";
			return static_cast<ListValue*>(s.top().first)->is_empty();
		}
		std::vector<std::string> current_list() {
			if (current_type() != IValueType::ListValue)
				throw "current_list(): expected that current_type() is ListValue";
			std::vector<std::string> ret;
			for (auto it = static_cast<ListValue*>(s.top().first)->start; it != nullptr; it = it->next)
				ret.push_back(it->key);
			return ret;
		}
		std::string& current_key() {
			if (current_type() != IValueType::ListValue)
				throw "current_key(): expected that current_type() is ListValue";
			if (current_list_is_empty())
				throw "current_key(): current list is empty";
			return s.top().second->key;
		}
		std::string& current_value() {
			if (current_type() != IValueType::Value)
				throw "current_value(): expected that current_type() is Value";
			return static_cast<Value*>(s.top().first)->value;
		}

		bool can_go_up();
		void go_up();
		bool can_go_down();
		void go_down();
		bool can_go_prev();
		void go_prev();
		bool can_go_next();
		void go_next();
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
		// Recursive write JSON
		void write(std::ostream& out);
		// Non-recursive (iterative) write JSON
		void write_iterative(std::ostream& out);
		IValue* get_root() { // delete later!
			return root;
		}
	};
}

#endif // !_JSON_Lib
