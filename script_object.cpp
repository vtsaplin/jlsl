#include "script_object.h"

script_object::script_object () {
	m_wave = 0;
	__gc_register (this);
//	cout << "object created" << endl;
}

script_object::~script_object () {
//	cout << "object deleted" << endl;
}

void script_object::array_subscript (script_container&, const script_container&) {
	throw script_exception (
		string ("ARRAY SUBSCRIPT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::increment (script_container&) {
	throw script_exception (
		string ("INCREMENT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::decrement (script_container&) {
	throw script_exception (
		string ("DECREMENT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::unary_minus (script_container&) {
	throw script_exception (
		string ("UNARY MINUS operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::logical_not (script_container&) {
	throw script_exception (
		string ("LOGICAL NOT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::bitwise_complement (script_container&) {
	throw script_exception (
		string ("BITWISE COMPLEMENT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::multiplication (script_container&, const script_container&) {
	throw script_exception (
		string ("MULTIPLICATION operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::division (script_container&, const script_container&) {
	throw script_exception (
		string ("DIVISION operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::modulus (script_container&, const script_container&) {
	throw script_exception (
		string ("MODULUS operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::addition (script_container&, const script_container&) {
	throw script_exception (
		string ("ADDITION operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::subtraction (script_container&, const script_container&) {
	throw script_exception (
		string ("SUBTRACTION operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::left_shift (script_container&, const script_container&) {
	throw script_exception (
		string ("LEFT SHIFT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::right_shift (script_container&, const script_container&) {
	throw script_exception (
		string ("RIGHT SHIFT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::less_than (script_container&, const script_container&) {
	throw script_exception (
		string ("LESS THAN operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::greater_than (script_container&, const script_container&) {
	throw script_exception (
		string ("GREATER THAN operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::less_than_or_equal_to (script_container&, const script_container&)
{
	throw script_exception (
		string ("LESS THAN OR EQUAL TO operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::greater_than_or_equal_to (script_container&, const script_container&)
{
	throw script_exception (
		string ("GREATER THAN OR EQUAL TO operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::equality (script_container&, const script_container&)
{
	throw script_exception (
		string ("EQUALITY operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::inequality (script_container&, const script_container&)
{
	throw script_exception (
		string ("INEQUALITY operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::bitwise_and (script_container&, const script_container&)
{
	throw script_exception (
		string ("BITWISE AND operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::bitwise_exclusive_or (script_container&, const script_container&)
{
	throw script_exception (
		string ("BITWISE EXCLUSIVE OR operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::bitwise_inclusive_or (script_container&, const script_container&)
{
	throw script_exception (
		string ("BITWISE INCLUSIVE OR operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::logical_and (script_container&, const script_container&)
{
	throw script_exception (
		string ("LOGICAL AND operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::logical_or (script_container&, const script_container&)
{
	throw script_exception (
		string ("LOGICAL OR operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

void script_object::assignment (script_container&) {
	throw script_exception (
		string ("ASSIGNMENT operator is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

long script_object::to_integer () const {
	throw script_exception (
		string ("implicit CONVERSION to integer is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

unsigned long script_object::to_unsigned_integer () const {
	throw script_exception (
		string ("implicit CONVERSION to unsigned integer is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

float script_object::to_single () const {
	throw script_exception (
		string ("implicit CONVERSION to single is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

bool script_object::to_boolean () const {
	throw script_exception (
		string ("implicit CONVERSION to boolean is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

string script_object::to_string () const {
	throw script_exception (
		string ("implicit CONVERSION to string is NOT IMPLEMENTED for ") + 
		get_descriptor_as_string ()
		);
}

//void * script_object::operator new (size_t size) {
//  return __gc_allocate (size); 
//}
//
//void script_object::operator delete (void * p) {
//  script_object * pc = static_cast<script_object *>(p); 
//  free (p);	
//}

void script_object::collect (unsigned long wave) {
	m_wave = wave;
}

bool script_object::is_locked (unsigned long wave) {
	return (m_wave == wave ? true : false);
}
//
//void script_object::set_locked_flag (bool locked) {
//	m_locked = locked;
//}
