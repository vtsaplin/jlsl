#include "script_container.h"

script_container::script_container () { 
	m_descriptor = dt_empty;
}

script_container::~script_container () {
}

void script_container::array_subscript (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		throw script_exception (
			"ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for integer."
			);
	} else if (m_descriptor == dt_unsigned_integer) {
		throw script_exception (
			"ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for unsigned integer."
			);
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for unsigned single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->array_subscript (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->array_subscript (r, v);
	} else {
		throw script_exception (
			"ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::increment (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () + 1);
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () + 1);
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () + 1);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"INCREMENT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->increment (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->increment (r);
	} else {
		throw script_exception (
			"INCREMENT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::decrement (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () - 1);
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () - 1);
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () - 1);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"DECREMENT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->decrement (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->decrement (r);
	} else {
		throw script_exception (
			"DECREMENT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::unary_minus (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (- to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		throw script_exception (
			"UNARY MINUS operator is NOT IMPLEMENTED for unsigned integer."
			);
	} else if (m_descriptor == dt_single) {
		r.set_single (- to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"UNARY MINUS operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->unary_minus (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->unary_minus (r);
	} else {
		throw script_exception (
			"UNARY MINUS operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::logical_not (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (!to_boolean ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (!to_boolean ());
	} else if (m_descriptor == dt_single) {
		r.set_single (!to_boolean ());
	} else if (m_descriptor == dt_boolean) {
		r.set_boolean (!to_boolean ());
	} else if (m_descriptor == dt_object) {
		m_object->logical_not (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->logical_not (r);
	} else {
		throw script_exception (
			"LOGICAL NOT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::bitwise_complement (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (~to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (~to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"BITWISE COMPLEMENT operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"BITWISE COMPLEMENT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->bitwise_complement (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->bitwise_complement (r);
	} else {
		throw script_exception (
			"BITWISE COMPLEMENT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::multiplication (script_container& r, const script_container& v) 
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () * v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () * v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () * v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"MULTIPLICATION operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->multiplication (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->multiplication (r, v);
	} else {
		throw script_exception (
			"MULTIPLICATION operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::division (script_container& r, const script_container& v) 
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () / v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () / v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () / v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"DIVISION operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->division (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->division (r, v);
	} else {
		throw script_exception (
			"DIVISION operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::modulus (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () % v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () % v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"MODULUS operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"MODULUS operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->modulus (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->modulus (r, v);
	} else {
		throw script_exception (
			"MODULUS operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::addition (script_container& r, const script_container& v) 
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () + v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () + v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () + v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"ADDITION operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->addition (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->addition (r, v);
	} else {
		throw script_exception (
			"ADDITION operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::subtraction (script_container& r, const script_container& v) 
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () - v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () - v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single () - v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"SUBTRACTION operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->subtraction (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->subtraction (r, v);
	} else {
		throw script_exception (
			"SUBTRACTION operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::left_shift (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () << v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () << v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"LEFT SHIFT operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"LEFT SHIFT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->left_shift (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->left_shift (r, v);
	} else {
		throw script_exception (
			"LEFT SHIFT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::right_shift (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () >> v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () >> v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"RIGHT SHIFT operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"RIGHT SHIFT operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->right_shift (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->right_shift (r, v);
	} else {
		throw script_exception (
			"RIGHT SHIFT operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::less_than (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () < v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () < v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () < v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"LESS THAN operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->less_than (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->less_than (r, v);
	} else {
		throw script_exception (
			"LESS THAN operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::greater_than (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () > v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () > v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () > v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"GREATER THAN operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->greater_than (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->greater_than (r, v);
	} else {
		throw script_exception (
			"GREATER THAN operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::less_than_or_equal_to (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () <= v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () <= v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () <= v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"LESS THAN OR EQUAL TO operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->less_than_or_equal_to (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->less_than_or_equal_to (r, v);
	} else {
		throw script_exception (
			"LESS THAN OR EQUAL TO operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::greater_than_or_equal_to (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () >= v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () >= v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () >= v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"GREATER THAN OR EQUAL TO operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->greater_than_or_equal_to (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->greater_than_or_equal_to (r, v);
	} else {
		throw script_exception (
			"GREATER THAN OR EQUAL TO operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::equality (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () == v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () == v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () == v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"EQUALITY operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->equality (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->equality (r, v);
	} else {
		throw script_exception (
			"EQUALITY operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::inequality (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_boolean (to_integer () != v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_boolean (to_unsigned_integer () != v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_boolean (to_single () != v.to_single ());
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"INEQUALITY operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->inequality (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->inequality (r, v);
	} else {
		throw script_exception (
			"INEQUALITY operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::bitwise_and (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () & v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () & v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"BITWISE AND operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"BITWISE AND operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->bitwise_and (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->bitwise_and (r, v);
	} else {
		throw script_exception (
			"BITWISE AND operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::bitwise_exclusive_or (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () ^ v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () ^ v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"BITWISE EXCLUSIVE OR operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"BITWISE EXCLUSIVE OR operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->bitwise_exclusive_or (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->bitwise_exclusive_or (r, v);
	} else {
		throw script_exception (
			"BITWISE EXCLUSIVE OR operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::bitwise_inclusive_or (script_container& r, const script_container& v)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer () | v.to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer () | v.to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		throw script_exception (
			"BITWISE INCLUSIVE OR operator is NOT IMPLEMENTED for single."
			);
	} else if (m_descriptor == dt_boolean) {
		throw script_exception (
			"BITWISE INCLUSIVE OR operator is NOT IMPLEMENTED for boolean."
			);
	} else if (m_descriptor == dt_object) {
		m_object->bitwise_inclusive_or (r, v);
	} else if (m_descriptor == dt_reference) {
		m_reference->bitwise_inclusive_or (r, v);
	} else {
		throw script_exception (
			"BITWISE INCLUSIVE OR operator is NOT IMPLEMENTED for empty."
			);
	}
}

void script_container::logical_and (script_container& r, const script_container& v)
{
	if (m_descriptor != dt_reference) {
		r.set_boolean (to_boolean () && v.to_boolean ());	
	} else {
		m_reference->logical_and (r, v);
	}
}

void script_container::logical_or (script_container& r, const script_container& v)
{
	if (m_descriptor != dt_reference) {
		r.set_boolean (to_boolean () || v.to_boolean ());
	} else {
		m_reference->logical_or (r, v);
	}
}

void script_container::assignment (script_container& r)
{
	if (m_descriptor == dt_integer) {
		r.set_integer (to_integer ());
	} else if (m_descriptor == dt_unsigned_integer) {
		r.set_unsigned_integer (to_unsigned_integer ());
	} else if (m_descriptor == dt_single) {
		r.set_single (to_single ());
	} else if (m_descriptor == dt_boolean) {
		r.set_boolean (to_boolean ());
	} else if (m_descriptor == dt_object) {
		m_object->assignment (r);
	} else if (m_descriptor == dt_reference) {
		m_reference->assignment (r);
	} else {
		r.m_descriptor = m_descriptor;
	}
}

long script_container::to_integer () const
{
	if (m_descriptor == dt_unsigned_integer) {
		return (long)m_unsigned_integer;
	} else if (m_descriptor == dt_single) {
		return (long)m_single;
	} else if (m_descriptor == dt_boolean) {
		return (long)m_boolean;
	} else if (m_descriptor == dt_object) {
		m_object->to_integer ();
	} else if (m_descriptor == dt_reference) {
		return m_reference->to_integer ();
	} else if (m_descriptor == dt_empty) {
		throw script_exception (
			"implicit CONVERSION to long is NOT IMPLEMENTED for empty."
			);
	}
	return m_integer;
}

void script_container::set_integer (const long v) 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_integer;
		m_integer = v;
	} else {
		m_reference->set_integer (v);
	}
}

unsigned long script_container::to_unsigned_integer () const
{
	if (m_descriptor == dt_integer) {
		return (unsigned long)m_integer;
	} else if (m_descriptor == dt_single) {
		return (unsigned long)m_single;
	} else if (m_descriptor == dt_boolean) {
		return (unsigned long)m_boolean;
	} else if (m_descriptor == dt_object) {
		m_object->to_unsigned_integer ();
	} else if (m_descriptor == dt_reference) {
		return m_reference->to_unsigned_integer ();
	} else if (m_descriptor == dt_empty) {
		throw script_exception (
			"implicit CONVERSION to unsigned long is NOT IMPLEMENTED for empty."
			);
	}
	return m_unsigned_integer;
}

void script_container::set_unsigned_integer (const unsigned long v) 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_unsigned_integer;
		m_unsigned_integer = v;
	} else {
		m_reference->set_unsigned_integer (v);
	}
}

float script_container::to_single () const
{
	if (m_descriptor == dt_integer) {
		return (float)m_integer;
	} else if (m_descriptor == dt_unsigned_integer) {
		return (float)m_unsigned_integer;
	} else if (m_descriptor == dt_boolean) {
		return (float)m_boolean;
	} else if (m_descriptor == dt_object) {
		m_object->to_single ();
	} else if (m_descriptor == dt_reference) {
		return m_reference->to_single ();
	} else if (m_descriptor == dt_empty) {
		throw script_exception (
			"implicit CONVERSION to float is NOT IMPLEMENTED for empty."
			);
	}
	return m_single;
}

void script_container::set_single (const float v) 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_single;
		m_single = v;
	} else {
		m_reference->set_single (v);
	}
}

bool script_container::to_boolean () const
{
	if (m_descriptor == dt_integer) {
		if (m_integer) return true;
		else return false;
	} else if (m_descriptor == dt_unsigned_integer) {
		if (m_unsigned_integer) return true;
		else return false;
	} else if (m_descriptor == dt_single) {
		if (m_single) return true;
		else return false;
	} else if (m_descriptor == dt_object) {
		m_object->to_boolean ();
	} else if (m_descriptor == dt_reference) {
		return m_reference->to_boolean ();
	} else if (m_descriptor == dt_empty) {
		throw script_exception (
			"implicit CONVERSION to bool is NOT IMPLEMENTED for empty."
			);
	}
	return m_boolean;
}

void script_container::set_boolean (const bool v) {
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_boolean;
		m_boolean = v;
	} else {
		m_reference->set_boolean (v);
	}
}

string script_container::to_string () const
{
	ostringstream ss;

	if (m_descriptor == dt_integer) {
		ss << m_integer;
	} else if (m_descriptor == dt_unsigned_integer) {
		ss << m_unsigned_integer;
	} else if (m_descriptor == dt_single) {
		ss << m_single;
	} else if (m_descriptor == dt_object) {
		ss << m_object->to_string ();
	} else if (m_descriptor == dt_reference) {
		ss << m_reference->to_string ();
	} else if (m_descriptor == dt_empty) {
		ss << "{empty}";
	}
	return ss.str ();
}

bool script_container::is_object () const
{
	if (m_descriptor != dt_object) {
		if (m_descriptor != dt_reference) {
			return m_reference->is_object ();
		} else {
			return false;
		}
	}
	return true;
}

script_object * script_container::get_object () const 
{
	if (m_descriptor != dt_object) {
		if (m_descriptor == dt_reference) {
			return m_reference->get_object ();
		} else {
			throw script_exception (string ("cannot CONVERT ") + 
				get_descriptor_as_string () + " to object."
				);
		}
	}
	return m_object;
}

void script_container::set_object (script_object * p) 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_object;
		m_object = p;
	} else {
		m_reference->set_object (p);
	}
}

bool script_container::is_reference () const 
{
	if (m_descriptor != dt_reference) {
		return false;
	}
	return true;
}

script_container& script_container::get_reference () 
{
	if (m_descriptor != dt_reference) {
		throw script_exception (string ("cannot CONVERT ") + 
			get_descriptor_as_string () + " to reference."
			);
	}
	return (* m_reference);
}

void script_container::set_reference (script_container& v) 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_reference;
		m_reference = &v;
	} else {
		m_reference->set_reference (v);
	}
}

script_container& script_container::dereference ()
{
	if (is_reference ()) {
		return m_reference->dereference ();
	}
	return (* this);
}

bool script_container::is_empty () const
{
	if (m_descriptor != dt_empty) {
		if (m_descriptor != dt_reference) {
			return m_reference->is_empty ();
		} else {
			return false;
		}
	}
	return true;
}

void script_container::set_empty_locally ()
{
	m_descriptor = dt_empty;
}

void script_container::set_empty () 
{
	if (m_descriptor != dt_reference) {
		m_descriptor = dt_empty;
	} else {
		m_reference->set_empty ();
	}
}

unsigned long script_container::get_descriptor () const
{
	return m_descriptor;
}

const char * script_container::get_descriptor_as_string () const
{
	if (m_descriptor == dt_integer) {
		return "integer";
	} else if (m_descriptor == dt_unsigned_integer) {
		return "unsigned integer";
	} else if (m_descriptor == dt_single) {
		return "single";
	} else if (m_descriptor == dt_boolean) {
		return "boolean";
	} else if (m_descriptor == dt_object) {
		return m_object->get_descriptor_as_string ();
	} else if (m_descriptor == dt_reference) {
		return m_reference->get_descriptor_as_string ();
	} else if (m_descriptor == dt_empty) {
		return "empty";
	} else {
		throw script_exception ("data type is UNKNOWN.");
	}
}

void script_container::collect (unsigned long wave) 
{
	if (m_descriptor == dt_object) {
		m_object->collect (wave);
	} else if (m_descriptor == dt_reference) {
		m_reference->collect (wave);
	}
}
