#ifndef __script_collection_object_h__
#define __script_collection_object_h__

#include "script_string_object.h"
#include "script_enumerable_object.h"
#include "script_object.h"
#include "script_container.h"
#include "script_parser.h"

#include <map>
using namespace std;

#define __script_collection_object_descriptor			(110U)
#define __script_collection_object_descriptor_as_string	("collection")

class script_collection_object : virtual public script_enumerable_object, virtual public script_object {
protected:
	map<string, script_container>			_collection;
	map<string, script_container>::iterator _iter;

public:
	// constructors/destrustor
	script_collection_object ();
	virtual ~script_collection_object ();

	// operators
	void array_subscript (script_container&, const script_container&);
	void assignment (script_container&);
	virtual string to_string () const;

	// methods of collection object
	virtual void find_element (script_container&, script_container&);

	// methods of enumerable object
	virtual void begin ();
	virtual void end ();
	virtual void backward ();
	virtual void forward ();
	virtual void get_current_key (script_container&);
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

#endif /* __script_collection_object_h__ */
