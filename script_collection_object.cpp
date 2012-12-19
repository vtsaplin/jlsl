#include "script_collection_object.h"

script_collection_object::script_collection_object () {
	_iter = _collection.begin ();
}

script_collection_object::~script_collection_object () {
}

void script_collection_object::array_subscript (script_container& r, const script_container& v) 
{
	_iter = _collection.find (v.to_string ());
	if (_iter != _collection.end ()) {
		r.set_reference ((* _iter).second);
	} else {
		r.set_reference (_collection [v.to_string ()] = script_container ());
	}
}

void script_collection_object::assignment (script_container& r) {
	r.set_object (this);
}

void script_collection_object::get_current_key (script_container& r) {
	if (_iter != _collection.end ()) {
		r.set_object (new script_string_object ((* _iter).first));
	} else {
		throw script_exception ("no current element selected.");
	}
}

void script_collection_object::find_element (script_container& r, script_container& v) {
	_iter = _collection.find (v.to_string ());
	if (_iter != _collection.end ()) {
		r.set_boolean (true);
	} else {
		r.set_boolean (false);
	}
}

void script_collection_object::begin () {
	_iter = _collection.begin ();
}

void script_collection_object::end () {
	_iter = _collection.end ();
}

void script_collection_object::backward () {
	_iter--;
}

void script_collection_object::forward () {
	_iter++;
}

void script_collection_object::current (script_container& r) {
	(* _iter).second.assignment (r);
}

void script_collection_object::remove () {
//#ifdef linux
	_collection.erase (_iter);
//#else
//	_iter = _collection.erase (_iter);
//#endif
}

bool script_collection_object::is_end () {
	if (_iter == _collection.end ()) return true;
	return false;
}

unsigned long script_collection_object::count () {
	return (unsigned long)_collection.size ();
}

string script_collection_object::to_string () const {
	return "";
}

unsigned long script_collection_object::get_descriptor () const {
	return __script_collection_object_descriptor;
}

const char * script_collection_object::get_descriptor_as_string () const {
	return __script_collection_object_descriptor_as_string;
}

void script_collection_object::collect (unsigned long wave) 
{
	if (!is_locked (wave)) {
		script_object::collect (wave);
		map<string, script_container>::iterator iter;
		for (iter=_collection.begin (); iter!=_collection.end (); iter++) {
			(* iter).second.collect (wave);
		}
	}
}

// find
script_container collection_find (vector<script_container>& args) {
	script_collection_object * p = dynamic_cast<script_collection_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->find_element (c, args [1]);
		return c;
	} else {
		throw script_exception ("find (collection, key): arguments are incorrect .");
	}
}
script_predefined_function collection_find_def ("find", collection_find, 2);
