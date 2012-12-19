#include "script_array_object.h"

script_array_object::script_array_object () {
	_iter = _vector.begin ();
}

script_array_object::script_array_object (unsigned long size) {
	_vector.resize (size);
	_iter = _vector.begin ();
}

script_array_object::~script_array_object () {
}

void script_array_object::array_subscript (script_container& r, const script_container& v) {
	unsigned long i = v.to_unsigned_integer ();
	if (i >= 0 && i < _vector.size ()) {
		r.set_reference (_vector [v.to_integer ()]);
	} else {
		throw script_exception ("array object: ouf of range.");
	}
}

void script_array_object::assignment (script_container& r) {
	r.set_object (this);
}

void script_array_object::begin () {
	_iter = _vector.begin ();
}

void script_array_object::end () {
	_iter = _vector.end ();
}

void script_array_object::backward () {
	_iter--;
}

void script_array_object::forward () {
	_iter++;
}

void script_array_object::current (script_container& r) {
	(* _iter).assignment (r);
}

void script_array_object::remove () {
	_iter = _vector.erase (_iter);
}

bool script_array_object::is_end () {
	if (_iter == _vector.end ()) return true;
	return false;
}

unsigned long script_array_object::count () {
	return (unsigned long)_vector.size ();
}

string script_array_object::to_string () const {
	return "";
}

unsigned long script_array_object::get_descriptor () const {
	return __script_array_object_descriptor;
}

const char * script_array_object::get_descriptor_as_string () const {
	return __script_array_object_descriptor_as_string;
}

void script_array_object::collect (unsigned long wave) 
{
	if (!is_locked (wave)) {
		script_object::collect (wave);
		vector<script_container>::iterator iter;
		for (iter=_vector.begin (); iter!=_vector.end (); iter++) {
			(* iter).collect (wave);
		}
	}
}

// function: CreateArray
script_container collection_CreateArray (vector<script_container>& args) {
	script_container c;
	c.set_object (new script_array_object (args [0].to_integer ()));
	return c;
}
script_predefined_function collection_CreateArray_def ("createarray", collection_CreateArray, 1);
