#include "script_exception.h"

script_exception::script_exception () {
}

script_exception::script_exception (const char * err) : _err (err) {
}

script_exception::script_exception (const string err) : _err (err) {
}

const char * script_exception::what () {
	return _err.c_str ();
}

script_exception::~script_exception () throw () {
}
