#include "script_predefined_function.h"

map<string, script_predefined_function *>& predefined_functions () {
	static map<string, script_predefined_function *> i; return i;
}

script_predefined_function::script_predefined_function 
	(
	string ident, 
	t_script_function_wrapper ptr, 
	unsigned long arg_count
	)
{
	_ptr = ptr;
	_arg_count = arg_count;
	predefined_functions () [ident] = (this);
}

script_predefined_function * get_predefined_function (string ident) 
{
	map<string, script_predefined_function *>::iterator iter;
	iter = predefined_functions().find (ident);
	if (iter != predefined_functions ().end ()) {
		return (* iter).second;
	}
	return 0;
}
