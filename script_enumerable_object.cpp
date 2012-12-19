#include "script_enumerable_object.h"

void script_enumerable_object::begin () {
	throw script_exception (
		string ("retrieving of first element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::end () {
	throw script_exception (
		string ("retrieving of last element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::backward () {
	throw script_exception (
		string ("retrieving of previous element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::forward () {
	throw script_exception (
		string ("retrieving of next element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::get_current_key (script_container&) {
	throw script_exception (
		string ("retrieving of current key is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::current (script_container&) {
	throw script_exception (
		string ("retrieving of current element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

void script_enumerable_object::remove () {
	throw script_exception (
		string ("removing of current element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

bool script_enumerable_object::is_end () {
	throw script_exception (
		string ("checking for last element is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

unsigned long script_enumerable_object::count () {
	throw script_exception (
		string ("getting number of elements is not implemented for ") + 
		get_descriptor_as_string ()
		);
}

// begin
script_container enumerable_begin (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->begin ();
		return c;
	} else {
		throw script_exception ("begin (): accept enumerable.");
	}
}
script_predefined_function enumerable_begin_def ("begin", enumerable_begin, 1);

// end
script_container enumerable_end (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->end ();
		return c;
	} else {
		throw script_exception ("end (): accept enumerable.");
	}
}
script_predefined_function enumerable_end_def ("end", enumerable_end, 1);

// backward
script_container enumerable_backward (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->backward ();
		return c;
	} else {
		throw script_exception ("backward (): accept enumerable.");
	}
}
script_predefined_function enumerable_backward_def ("backward", enumerable_backward, 1);

// forward
script_container enumerable_forward (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->forward ();
		return c;
	} else {
		throw script_exception ("forward (): accept enumerable.");
	}
}
script_predefined_function enumerable_forward_def ("forward", enumerable_forward, 1);

// get current key
script_container collection_get_key (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->get_current_key (c);
		return c;
	} else {
		throw script_exception ("get_key (): accept enumerable.");
	}
}
script_predefined_function collection_get_key_def ("get_key", collection_get_key, 1);

// current
script_container enumerable_current (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->current (c);
		return c;
	} else {
		throw script_exception ("current (): accept enumerable.");
	}
}
script_predefined_function enumerable_current_def ("current", enumerable_current, 1);

// is_end
script_container enumerable_is_end (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		c.set_boolean (p->is_end ());
		return c;
	} else {
		throw script_exception ("is_end (): accept enumerable.");
	}
}
script_predefined_function enumerable_is_end_def ("is_end", enumerable_is_end, 1);

// remove
script_container enumerable_remove (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		p->remove ();
		return c;
	} else {
		throw script_exception ("remove (): accept enumerable.");
	}
}
script_predefined_function enumerable_remove_def ("remove", enumerable_remove, 1);

// count
script_container enumerable_count (vector<script_container>& args) {
	script_enumerable_object * p = dynamic_cast<script_enumerable_object *>(args [0].get_object ());
	if (p) {
		script_container c;
		c.set_integer (p->count ());
		return c;
	} else {
		throw script_exception ("count (): accept enumerable.");
	}
}
script_predefined_function enumerable_count_def ("count", enumerable_count, 1);
