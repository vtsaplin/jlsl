#ifndef __script_array_object_h__
#define __script_array_object_h__

#include "script_enumerable_object.h"
#include "script_object.h"
#include "script_container.h"
#include "script_parser.h"

#include <map>
using namespace std;

#define __script_array_object_descriptor			(120U)
#define __script_array_object_descriptor_as_string	("array")

class script_array_object : virtual public script_enumerable_object, virtual public script_object {
protected:
	vector<script_container>			_vector;
	vector<script_container>::iterator	_iter;

public:
	// constructors/destrustor
	script_array_object ();
	script_array_object (unsigned long);
	virtual ~script_array_object ();

	// operators
	void array_subscript (script_container&, const script_container&);
	void assignment (script_container&);
	virtual string to_string () const;

	// methods of enumerable object
	virtual void begin ();
	virtual void end ();
	virtual void backward ();
	virtual void forward ();
	virtual void current (script_container&);
	virtual void remove ();
	virtual bool is_end ();
	virtual unsigned long count ();

	// run-time type information enumerable
	unsigned long get_descriptor () const;
	const char * get_descriptor_as_string () const;

	// garbage collector
	virtual void collect (unsigned long);
};

#endif /* __script_array_object_h__ */
