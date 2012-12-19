#include "script_code_fragment.h"

script_code_fragment::script_code_fragment () {
	_start_before = _start_after = _code_size = 0;
}

script_code_fragment::~script_code_fragment () {
}

void script_code_fragment::construct
	(
	vector<unsigned long>& dst, 
	vector<unsigned long>& src
	) 
{
	// do job
	_start_after = (unsigned long)dst.size ();
	if (_code_size > 0) {
		dst.insert (dst.end (), src.begin () + _start_before, src.begin () + _start_before + _code_size);
	}
	// repeat for children
	script_code_fragment * p = get_head ();
	while (p) {
		p->construct (dst, src); 
		p = p->get_next ();
	}
}

void script_code_fragment::resolve 
	(
	vector<unsigned long>& code
	) 
{
	// do job
	for (vector<script_jmp>::iterator i=_jmps.begin (); i!=_jmps.end (); i++) {
		code [_start_after + (* i)._offset] = (* i)._destination->_start_after;
	}
	// repeat for children
	script_code_fragment * p = get_head ();
	while (p) {
		p->resolve (code); 
		p = p->get_next ();
	}
}

void script_code_fragment::set_code_start 
	(
	unsigned long offset
	) 
{
	_start_before = offset; 
}

void script_code_fragment::set_code_end 
	(
	unsigned long offset
	) 
{ 
	_code_size = offset - _start_before;
}

void script_code_fragment::set_jmp 
	(
	unsigned long offset, 
	script_code_fragment * destination
	) 
{
	script_jmp jmp = 
		{ 
		offset - _start_before, 
		destination 
		};
	_jmps.push_back (jmp);
}
