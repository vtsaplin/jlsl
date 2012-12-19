#ifndef __script_string_object_h__
#define __script_string_object_h__

#include "script_object.h"

#include <string>
using namespace std;

#define __script_string_object_descriptor			(100U)
#define __script_string_object_descriptor_as_string	("string")

class script_string_object : public script_object {
protected:
	string	m_string;

public:
	script_string_object ();
	script_string_object (const char *);
	script_string_object (const string);
	virtual ~script_string_object ();

	// additive operators
	void addition (script_container&, const script_container&);
	// relational & equality operators
	void less_than (script_container&, const script_container&);
	void greater_than (script_container&, const script_container&);
	void less_than_or_equal_to (script_container&, const script_container&);
	void greater_than_or_equal_to (script_container&, const script_container&);
	void equality (script_container&, const script_container&);
	void inequality (script_container&, const script_container&);
	// assignment operators
	void assignment (script_container&);

	// conversion
	string to_string () const;

	// run-time type information
	unsigned long get_descriptor () const;
	const char * get_descriptor_as_string () const;
};

#endif /* __script_string_object_h__ */
