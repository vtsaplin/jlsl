#ifndef __script_object_h__
#define __script_object_h__

#include "script_container.h"
#include "script_exception.h"
#include "collector.h"

#include <new>
using namespace std;

class script_container;

class script_object {
protected:
	unsigned long	m_wave;

public:

	// constructors/destrustor
	script_object ();
	virtual ~script_object ();

	// subscript operators
	virtual void array_subscript (script_container&, const script_container&);
	// unary operators
	virtual void increment (script_container&);
	virtual void decrement (script_container&);
	virtual void unary_minus (script_container&);
	virtual void logical_not (script_container&);
	virtual void bitwise_complement (script_container&);
	// multiplicative operators
	virtual void multiplication (script_container&, const script_container&);
	virtual void division (script_container&, const script_container&);
	virtual void modulus (script_container&, const script_container&);
	// additive operators
	virtual void addition (script_container&, const script_container&);
	virtual void subtraction (script_container&, const script_container&);
	// shift operators
	virtual void left_shift (script_container&, const script_container&);
	virtual void right_shift (script_container&, const script_container&);
	// relational & equality operators
	virtual void less_than (script_container&, const script_container&);
	virtual void greater_than (script_container&, const script_container&);
	virtual void less_than_or_equal_to (script_container&, const script_container&);
	virtual void greater_than_or_equal_to (script_container&, const script_container&);
	virtual void equality (script_container&, const script_container&);
	virtual void inequality (script_container&, const script_container&);
	// bitwise operators
	void bitwise_and (script_container&, const script_container&);
	void bitwise_exclusive_or (script_container&, const script_container&);
	void bitwise_inclusive_or (script_container&, const script_container&);
	// logical operators
	void logical_and (script_container&, const script_container&);
	void logical_or (script_container&, const script_container&);
	// assignment operators
	virtual void assignment (script_container&);

	// getters/setters
	virtual long to_integer () const;
	virtual unsigned long to_unsigned_integer () const;
	virtual float to_single () const;
	virtual bool to_boolean () const;
	virtual string to_string () const;

	// run-time type information
	virtual unsigned long get_descriptor () const = 0;
	virtual const char * get_descriptor_as_string () const = 0;

	// garbage collector
//	void * operator new (size_t size);
//	void operator delete (void *p);
	virtual void collect (unsigned long);
	bool is_locked (unsigned long);
//	virtual void set_locked_flag (bool);
};

#endif /* __script_object_h__ */
