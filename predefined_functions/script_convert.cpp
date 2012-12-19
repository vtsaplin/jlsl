#include "../script_parser.h"

script_container convert_stoi (vector<script_container>& args) {
	script_container c;
	script_string_object * p = (script_string_object *)args [0].get_object ();
	if (p->get_descriptor () == __script_string_object_descriptor) {
		c.set_integer (strtol (p->to_string ().c_str (), NULL, 0));
		return c;
	} else {
		throw script_exception ("stoi (): accept string.");
	}
}
script_predefined_function convert_stoi_def ("stoi", convert_stoi, 1);
