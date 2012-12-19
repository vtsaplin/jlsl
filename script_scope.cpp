#include "script_scope.h"

script_scope::script_scope () {
}

script_scope::~script_scope () {
}

void script_scope::append 
	(
	const char * key, 
	script_code_fragment * fragment
	) 
{
	_fragments [key] = fragment;
}

script_code_fragment * script_scope::get 
	(
	const char * key
	) 
{
	map<string, script_code_fragment *>::iterator pos = _fragments.find (key);
	if (pos != _fragments.end ()) {
		return (* pos).second;
	}
	return 0;
}
