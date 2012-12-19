#ifndef __script_container_h__
#define __script_container_h__

#include "script_object.h"
#include "script_exception.h"

#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class script_object;

class script_container {
protected:

	// data types
	enum {
		dt_integer = 1,
		dt_unsigned_integer,
		dt_single,
		dt_boolean,
		dt_object,
		dt_reference,
		dt_empty
	};

	// data type descriptor
	unsigned long			m_descriptor;
	// data
	union {
		long				m_integer;
		unsigned long		m_unsigned_integer;
		float				m_single;
		bool				m_boolean;
		script_object *		m_object;
		script_container *	m_reference;
	};

public:

	// constructors/destructor
	script_container ();
	~script_container ();

	// member access operator
	void member_selection (script_container&);
	// subscript operators
	void array_subscript (script_container&, const script_container&);
	// function call operator
	void function_call (script_container&);
	// unary operators
	void increment (script_container&);
	void decrement (script_container&);
	void bitwise_complement (script_container&);
	void logical_not (script_container&);
	void unary_minus (script_container&);
	// multiplicative operators
	void multiplication (script_container&, const script_container&);
	void division (script_container&, const script_container&);
	void modulus (script_container&, const script_container&);
	// additive operators
	void addition (script_container&, const script_container&);
	void subtraction (script_container&, const script_container&);
	// shift operators
	void left_shift (script_container&, const script_container&);
	void right_shift (script_container&, const script_container&);
	// relational & equality operators
	void less_than (script_container&, const script_container&);
	void greater_than (script_container&, const script_container&);
	void less_than_or_equal_to (script_container&, const script_container&);
	void greater_than_or_equal_to (script_container&, const script_container&);
	void equality (script_container&, const script_container&);
	void inequality (script_container&, const script_container&);
	// bitwise operators
	void bitwise_and (script_container&, const script_container&);
	void bitwise_exclusive_or (script_container&, const script_container&);
	void bitwise_inclusive_or (script_container&, const script_container&);
	// logical operators
	void logical_and (script_container&, const script_container&);
	void logical_or (script_container&, const script_container&);
	// assignment operators
	void assignment (script_container&);

	// setters/getters for integer
	long to_integer () const;
	void set_integer (const long);
	// setters/getters for unsigned integer
	unsigned long to_unsigned_integer () const;
	void set_unsigned_integer (const unsigned long);
	// setters/getters for single
	float to_single () const;
	void set_single (const float);
	// setters/getters for boolean
	bool to_boolean () const;
	void set_boolean (const bool);
	// setters/getters for string
	string to_string () const;
	// setters/getters for object
	bool is_object () const;
	script_object * get_object () const;
	void set_object (script_object *);
	// setters/getters for reference
	bool is_reference () const;
	script_container& get_reference ();
	void set_reference (script_container&);
	script_container& dereference ();
	// setters/getters for empty
	bool is_empty () const;
	void set_empty_locally ();
	void set_empty ();

	// run-time type information
	unsigned long get_descriptor () const;
	const char * get_descriptor_as_string () const;

	// support for garbage collector
	void collect (unsigned long);
};

#endif /* __script_container_h__ */
