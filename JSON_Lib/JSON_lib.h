#ifndef _JSON_Lib
#define _JSON_Lib

#include <string>
#include <iostream>

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
	};

	class JSON {
	private:
		ListValue* iv;
	public:
		static int test();
		JSON() : iv(nullptr) {}
		JSON(const JSON& js) {
			if (js.iv) {
				iv = new ListValue(*js.iv);
			}
			else {
				iv = nullptr;
			}
		}
		void read(std::istream& in) {
			IValue* temp = read_IValue(in);
			if (temp->get_type() != ValueType::ListValue)
				throw "JSON.read(): expected LishValue";
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
		~JSON() {
			delete iv;
		}
	};
}

#endif // !_JSON_Lib
