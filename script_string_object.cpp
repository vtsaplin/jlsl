#include "script_string_object.h"

script_string_object::script_string_object () {
}

script_string_object::script_string_object (const char * str) {
	m_string = str;
}

script_string_object::script_string_object (const string str) {
	m_string = str;
}

script_string_object::~script_string_object () {
}

void script_string_object::addition (script_container& r, const script_container& v) {
	r.set_object (new script_string_object (m_string + v.to_string ()));
}

void script_string_object::less_than (script_container& r, const script_container& v) {
	r.set_boolean (m_string < v.to_string ());
}

void script_string_object::greater_than (script_container& r, const script_container& v) {
	r.set_boolean (m_string > v.to_string ());
}

void script_string_object::less_than_or_equal_to (script_container& r, const script_container& v) {
	r.set_boolean (m_string <= v.to_string ());
}

void script_string_object::greater_than_or_equal_to (script_container& r, const script_container& v) {
	r.set_boolean (m_string >= v.to_string ());
}

void script_string_object::equality (script_container& r, const script_container& v) {
	r.set_boolean (m_string == v.to_string ());
}

void script_string_object::inequality (script_container& r, const script_container& v) {
	r.set_boolean (m_string != v.to_string ());
}

void script_string_object::assignment (script_container& r) {
	script_string_object * p = new script_string_object (m_string);
	r.set_object (p);
}

string script_string_object::to_string () const {
	return m_string;
}

unsigned long script_string_object::get_descriptor () const {
	return __script_string_object_descriptor;
}

const char * script_string_object::get_descriptor_as_string () const {
	return __script_string_object_descriptor_as_string;
}
