#include "collector.h"

vector<script_object *>						objects;
map<script_gc_client *, script_gc_client *>	clients;
unsigned long								object_limit = 2048;
unsigned long								wave = 0;

script_gc_client::script_gc_client () {
	clients [(this)] = (this);
}

script_gc_client::~script_gc_client () {
	clients.erase (this);
}

//void * __gc_allocate (size_t size) 
//{
//	if (objects.size () >= object_limit) {
//		__gc_collect ();
//	}
//	void * p = malloc (size);
//	if (p == 0) throw script_exception ("cannot allocate memory");
//	objects.push_back ((script_object *)p);
//	return p;
//}

void __gc_register (script_object * p)
{
	if (objects.size () >= object_limit) {
		__gc_collect ();
	}
	objects.push_back ((script_object *)p);
}

void __gc_collect () 
{
	vector<script_object *>::iterator						i1;
	map<script_gc_client *, script_gc_client *>::iterator	i2;

	cout << "---------------------" << endl;
	cout << "before: " << __gc_count () << endl;

	// check for objects that are still alive
	wave++;
	i2 = clients.begin ();
	for (i2; i2!=clients.end (); i2++) {
		(* i2).second->collect (wave);
	}
	// change upper limit
//	object_limit *= 2;

	// destroy dead objects
	i1 = objects.begin ();
	while (i1!=objects.end ()) {
		if (!(* i1)->is_locked (wave)) {
			delete (* i1);
			i1 = objects.erase (i1);
		} else {
			i1++;
		}
	}

	cout << "after: " << __gc_count () << endl;
	cout << "---------------------" << endl;
}

unsigned long __gc_count () {
	return (unsigned long)objects.size ();
}
