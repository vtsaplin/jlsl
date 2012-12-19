#include "../script_parser.h"

const unsigned long vmeStartAddress = 0xDE000000;

unsigned long vmeReadDword (unsigned long offset) {
	unsigned long * p = (unsigned long *)(vmeStartAddress + offset);
	return (* p);
}

void vmeWriteDword (unsigned long offset, unsigned long val) {
	unsigned long * p = (unsigned long *)(vmeStartAddress + offset);
	(* p) = val;
}

script_container vme_peek (vector<script_container>& args) {
	script_container c;
	unsigned long p = args [0].to_unsigned_integer ();
	if (p % 2) {
		throw script_exception ("peek (): memory alignment fault.");
	}
	c.set_unsigned_integer (vmeReadDword (p));
	return c;
}
script_predefined_function vme_peek_def ("peek", vme_peek, 1);

script_container vme_poke (vector<script_container>& args) {
	script_container c;
	unsigned long p = args [0].to_unsigned_integer ();
	if (p % 2) {
		throw script_exception ("poke (): memory alignment fault.");
	}
	vmeWriteDword (p, args [1].to_unsigned_integer ());
	return c;
}
script_predefined_function vme_poke_def ("poke", vme_poke, 2);
