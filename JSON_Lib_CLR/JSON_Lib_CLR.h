#ifndef _JSON_Lib_CLR
#define _JSON_Lib_CLR

#include "JSON_lib.h"

namespace JSON_Lib_CLR {
	public ref class JSON_CLR {
	public:
		static int test() {
			return JSON_Lib::JSON::test();
		}
	};
}

#endif // !__JSON_LIB_CLR
