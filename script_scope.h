#ifndef __script_scope_h__
#define __script_scope_h__

#include "script_code_fragment.h"
#include "smart_pointer.h"

#include <map>
#include <string>
using namespace std;

class script_scope : public smart_pointer<script_scope>::countable {
protected:
	map<string, script_code_fragment *>	_fragments;

public:
	script_scope ();
	~script_scope ();

	void append (const char *, script_code_fragment *);
	script_code_fragment * get (const char *);
};

#endif /* __script_scope_h__ */
