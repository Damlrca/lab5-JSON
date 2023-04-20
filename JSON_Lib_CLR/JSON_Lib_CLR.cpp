#include "JSON_Lib_CLR.h"
#include <stack>

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace JSON_Lib_CLR;

// recursive old version
/*
array<TreeNode^>^ JSON_Lib_CLR::GenerateTreeNodeArray(JSON_Lib::IValue* iv) {
	if (auto v = dynamic_cast<JSON_Lib::Value*>(iv))
		return gcnew array<TreeNode^>{
		gcnew TreeNode(gcnew System::String(v->get_val().c_str()))};
	else if (auto v = dynamic_cast<JSON_Lib::ListValue*>(iv)) {
		JSON_Lib::Link* st = v->get_start(); // ListValue::get_start() is deleted
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
		for each (TreeNode ^ tn in lst)
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
*/

TreeNode^ JSON_Lib_CLR::GenerateTreeNode_from_JSON(JSON_Lib::JSON* js) {
	using namespace JSON_Lib;
	JSON_Iterator it = js->get_iterator();
	TreeNode^ root = gcnew TreeNode(gcnew System::String("JSON"));
	Stack<TreeNode^>^ tn_stack = gcnew Stack<TreeNode^>();
	tn_stack->Push(root);
	std::stack<bool> was;
	was.push(false);
	while (!was.empty()) {
		if (it.current_type() == IValueType::Value) {
			TreeNode^ tn = gcnew TreeNode(gcnew System::String(it.current_value().c_str()));
			tn->Tag = System::IntPtr(&it.current_value());
			tn_stack->Peek()->Nodes->Add(tn);
			was.pop();
			if (it.can_go_up())
				it.go_up();
		}
		else { // it.current_type() == IValueType::ListValue
			if (was.top()) {
				if (!it.current_list_is_empty()) {
					TreeNode^ temp = tn_stack->Pop();
					tn_stack->Peek()->Nodes->Add(temp);
				}
				if (!it.current_list_is_empty() && it.can_go_next()) {
					was.top() = false;
					it.go_next();
				}
				else {
					was.pop();
					if (it.can_go_up())
						it.go_up();
				}
			}
			else {
				was.top() = true;
				if (it.current_list_is_empty()) {
					// ?
				}
				else {
					TreeNode^ tn = gcnew TreeNode(gcnew System::String(it.current_key().c_str()));
					tn->Tag = System::IntPtr(&it.current_key());
					tn_stack->Push(tn);
					was.push(false);
					it.go_down();
				}
			}
		}
	}
	return root;
}

void JSON_Lib_CLR::JSON::UpdateKeyOrValue(TreeNode^ tn, System::String^ new_string) {
	std::string* s = (std::string*)(System::IntPtr(tn->Tag)).ToPointer();
	*s = msclr::interop::marshal_as<std::string>(new_string);
}
