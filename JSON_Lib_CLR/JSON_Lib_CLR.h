#ifndef _JSON_Lib_CLR
#define _JSON_Lib_CLR

#include "JSON_lib.h"
#include <fstream>
#include <sstream>
#include <msclr\marshal_cppstd.h>

namespace JSON_Lib_CLR {
	using TreeNode = System::Windows::Forms::TreeNode;

	// recursive old version
	// array<System::Windows::Forms::TreeNode^>^ GenerateTreeNodeArray(JSON_Lib::IValue* iv);
	
	// iterative new version // TODO: pointer to string in Tag
	TreeNode^ GenerateTreeNode_from_JSON(JSON_Lib::JSON* js);

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
			try { js->read(in); }
			catch(...){}
		}
		void read_from_string(System::String^ _data) {
			std::string data = msclr::interop::marshal_as<std::string>(_data);
			std::stringstream ss(data);
			try { js->read(ss); }
			catch (...) {}
		}
		System::String^ write_to_string() {
			std::stringstream ss;
			try { js->write(ss); }
			catch (...) {}
			return gcnew System::String(ss.str().c_str());
		}
		System::String^ write_to_string_iterative() {
			std::stringstream ss;
			try { js->write_iterative(ss); }
			catch (...) {}
			return gcnew System::String(ss.str().c_str());
		}
		TreeNode^ GenerateTreeNode() {
			TreeNode^ tn = nullptr;
			try {
				// recursive old version
				// tn = gcnew TreeNode(gcnew System::String("JSON"), GenerateTreeNodeArray(js->get_root())); // JSON::get_root() is deleted
				// iterative new version
				tn = GenerateTreeNode_from_JSON(js);
				tn->ExpandAll();
			}
			catch (...) {}
			return tn;
		}
		~JSON() {
			delete js;
		}
	};
}

#endif // !__JSON_LIB_CLR
