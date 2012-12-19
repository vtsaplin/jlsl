#ifndef __collector_h__
#define __collector_h__

#include "script_object.h"

#include <map>
#include <vector>
using namespace std;

class script_object;

class script_gc_client {
public:
	script_gc_client ();
	virtual ~script_gc_client ();
	virtual void collect (unsigned long) = 0;
};

//void * __gc_allocate (size_t size);

void __gc_register (script_object *);
void __gc_collect ();
unsigned long __gc_count ();

#endif /* __collector_h__ */
