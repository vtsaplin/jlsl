#ifndef __script_predefined_function_h__
#define __script_predefined_function_h__

#include "script_container.h"

#include <string>
#include <vector>
#include <map>
using namespace std;

// ==========================================================
//	Script function wrapper
// ==========================================================
typedef script_container (* t_script_function_wrapper) (vector<script_container>&);

// ==========================================================
//	Script function declarator
// ==========================================================
class script_predefined_function {
public:
	t_script_function_wrapper	_ptr;
	unsigned long				_arg_count;

public:
	script_predefined_function (
		string, 
		t_script_function_wrapper, 
		unsigned long
		);
};

// ==========================================================
//	Used by parser to get a function information by name
// ==========================================================
script_predefined_function * get_predefined_function (string);

#endif /* __script_predefined_function_h__ */
