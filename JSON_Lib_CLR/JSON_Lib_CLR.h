#ifndef _JSON_Lib_CLR
#define _JSON_Lib_CLR

#include "JSON_lib.h"
#include <fstream>
#include <sstream>
#include <msclr\marshal_cppstd.h>

namespace JSON_Lib_CLR {
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;

	array<TreeNode^>^ GenerateTreeNodeArray(JSON_Lib::IValue* iv) {
		if (auto v = dynamic_cast<JSON_Lib::Value*>(iv))
			return gcnew array<TreeNode^>{
			gcnew TreeNode(gcnew System::String(v->get_val().c_str()))};
		else if (auto v = dynamic_cast<JSON_Lib::ListValue*>(iv)) {
			JSON_Lib::Link* st = v->get_start();
			List<TreeNode^>^ lst = gcnew List<TreeNode^>(0);
			while (st) {
				lst->Add(gcnew TreeNode(
					gcnew System::String(st->key.c_str()),
					GenerateTreeNodeArray(st->val)
				));
				st = st->next;
			}
			array<TreeNode^>^ res = gcnew array<TreeNode^>(lst->Count);
			int i = 0;
			for each (TreeNode^ tn in lst)
			{
				res[i] = tn;
				i++;
			}
			return res;
		}
		else {
			throw "";
		}
	}

	public ref class JSON {
	private:
		JSON_Lib::JSON* js;
		
	public:
		JSON() {
			js = new JSON_Lib::JSON();
		}
		void read_file(System::String^ _filename) {
			std::string name = msclr::interop::marshal_as<std::string>(_filename);
			std::ifstream in(name);
			js->read(in);
			in.close();
		}
		System::String^ write_to_string() {
			std::stringstream ss;
			js->write(ss);
			return gcnew System::String(ss.str().c_str());
		}
		TreeNode^ GenerateTreeNode() {
			auto tn = gcnew TreeNode(gcnew System::String("JSON"), GenerateTreeNodeArray(js->get_root()));
			tn->ExpandAll();
			return tn;
			
		}
		~JSON() {
			delete js;
		}
	};
}

#endif // !__JSON_LIB_CLR
