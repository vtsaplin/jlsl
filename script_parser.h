#ifndef __script_parser_h__
#define __script_parser_h__

#include "script_collection_object.h"
#include "script_array_object.h"
#include "script_string_object.h"
#include "script_enumerable_object.h"
#include "script_object.h"
#include "script_container.h"
#include "script_predefined_function.h"
#include "script_code_fragment.h"
#include "script_scope.h"
#include "script_exception.h"
#include "tree_helper.h"
#include "smart_pointer.h"

#include <stdio.h>

#include <map>
#include <vector>
#include <deque>
#include <string>
#include <iostream>
using namespace std;

// #define __DEBUG__

// =================================================================
//	TOKEN CLASS
// =================================================================

enum {
	tc_delimiter = 1,
	tc_constant,
	tc_keyword,
	tc_identifier
};

// =================================================================
//	TOKEN TYPE
// =================================================================

enum {
	tt_end_of_table = 0,
	// Unary Operators
	tt_logical_negation,
	tt_bitwise_complement,
	tt_increment,
	tt_decrement,
	// Multiplicative Operators
	tt_multiplication,
	tt_division,
	tt_modulus,
	// Additive Operators
	tt_addition,
	tt_subtraction,
	// Shift operators
	tt_right_shift,
	tt_left_shift,
	// Relational and Equality Operators
	tt_less_then,
	tt_less_then_or_equal_to,
	tt_greater_then,
	tt_greater_then_or_equal_to,
	tt_equality,
	tt_inequality,
	// Logical Operators
	tt_logical_and,
	tt_logical_or,
	// Bitwise Operators
	tt_bitwise_and,
	tt_bitwise_exclusive_or,
	tt_bitwise_inclusive_or,
	// Assignment Operators
	tt_assignment,
	tt_addition_assignment,
	tt_subtraction_assignment,
	tt_multiplication_assignment,
	tt_division_assignment,
	tt_modulus_assignment,
	// 
	tt_opened_round_bracket,
	tt_closed_round_bracket,
	tt_opened_square_bracket,
	tt_closed_square_bracket,
	tt_opened_brace,
	tt_closed_brace,
	tt_colon,
	tt_semicolon,
	tt_comma,
	tt_dot,
	tt_integer,
	tt_unsigned_integer,
	tt_single,
	tt_string,
	tt_identifier,
	tt_eof, // 36
	// =====================
	tt_kw_true = 100,
	tt_kw_false,
	tt_kw_empty,
	tt_kw_collection,
	tt_kw_array,
	tt_kw_is_empty,
//	tt_kw_echo = 200,
	tt_kw_var = 200,
	tt_kw_local,
	tt_kw_function,
	tt_kw_return,
	tt_kw_while,
	tt_kw_do,
	tt_kw_for,
	tt_kw_break,
	tt_kw_continue,
	tt_kw_select,
	tt_kw_case,
	tt_kw_default,
	tt_kw_if,
	tt_kw_else
};

// =================================================================
//	OPCODES
// =================================================================

enum {
	opcode_echo = 1,

	opcode_pop,						// pop topmost element to variable
	opcode_pop_ref,						// pop topmost element to variable

	opcode_push,					// push variable value to stack
	opcode_push_ref,				// push reference to variable to stack
	opcode_push_local_ref,

	opcode_pop_local,
	opcode_push_local,

	opcode_dereference,

	opcode_swap,					// swap two topmost elements

	// stack opcodes
	opcode_load_empty,
	opcode_duplicate_topmost,
	opcode_delete_topmost,
	opcode_allocate_stack_space,
	opcode_roll_stack_back,			

	opcode_custom_function_call,
	opcode_predefined_function_call,
	opcode_return,

	opcode_jump,
	opcode_jump_if_false,
	opcode_jump_if_true,

	opcode_quit,					// exit program

	opcode_iter_begin,
	opcode_iter_end,
	opcode_iter_backward,
	opcode_iter_forward,
	opcode_iter_current,			
	opcode_is_end,			

	// subscript operators
	opcode_array_subscript,

	// unary operators
	opcode_increment,
	opcode_decrement,
	opcode_unary_negation,
	opcode_logical_not,
	opcode_bitwise_complement,

	// multiplicative operators
	opcode_multiplication,
	opcode_division,
	opcode_modulus,

	// additive operators
	opcode_addition,
	opcode_subtraction,

	// shift operators
	opcode_right_shift,
	opcode_left_shift,

	// relational and equality operators
	opcode_less_then,
	opcode_less_then_or_equal_to,
	opcode_greater_then,
	opcode_greater_then_or_equal_to,
	opcode_equality,
	opcode_inequality,

	// bitwise operators
	opcode_bitwise_and,
	opcode_bitwise_exclusive_or,
	opcode_bitwise_inclusive_or,

	// logical operators
	opcode_logical_and,
	opcode_logical_or
};

// =================================================================
//	SCRIPT PARSER
// =================================================================

#define __ENCODE_OPCODE(op, row) (((row & 0xFFFF) << 16) | (op & 0xFFFF))
#define __DECODE_OPCODE(enc) (enc & 0xFFFF)
#define __DECODE_ROW(enc) ((enc >> 16) & 0xFFFF)

struct script_keyword {
	unsigned long	token_type;
	string			content;
};

struct script_token {
	unsigned long	token_class;
	unsigned long	token_type;
	unsigned long	row, column;
	string			content;
};

struct script_custom_function {
	script_code_fragment *	entry_point;
	unsigned long			arg_count;
};

class script_parser : public script_gc_client {
protected:

	// for tokenizer
	unsigned char							lookahead;
	unsigned char							row, column;
	script_token							token;
//	deque<script_token>						cache;

	// symbolic tables
	map<string, unsigned long>				stbl_global;
	map<string, unsigned long>				stbl_local;

	// custom functions
	map<string, script_custom_function>		_custom_functions;
	unsigned long							_func_args_count;
	bool									_function_scope;

	script_code_fragment					memory_map;
	vector<smart_pointer<script_scope> >	scope_stack;
	vector<unsigned long>					code_buffer;
	vector<unsigned long>					script;

	// for parser
	vector<script_container>				heap;
	vector<script_container>				stack;

protected:

	// for tokenizer
	void read_character (istream&);
	void skip_comment (istream&);
	void read_identifier (istream&);
	void read_number (istream&);
	void read_string (istream&);
	void read_next_token (istream&);

	// for tokenizer
	//script_token * read (istream&);
	//script_token * get (istream&);
	//script_token * peek (istream&);

	// for parser
	void var_expr (istream& is, string);

	// for parser
	long func_args_stmt (istream&, script_code_fragment *);
	void return_stmt (istream&, script_code_fragment *);
	void custom_func_expr (istream&, script_custom_function *, script_code_fragment *);
	void predefined_func_expr (istream&, script_predefined_function *, script_code_fragment *);
	void func_expr (istream&, string ident, script_code_fragment *);

	// for parser
	void primary_expr (istream&, script_code_fragment *);
	void postfix_expr (istream&, script_code_fragment *);
	void unary_expr (istream&, script_code_fragment *);
	void multiplicative_expr (istream&, script_code_fragment *);
	void additive_expr (istream&, script_code_fragment *);
	void shift_expr (istream&, script_code_fragment *);
	void relational_expr (istream&, script_code_fragment *);
	void bitwise_expr (istream&, script_code_fragment *);
	void logical_expr (istream&, script_code_fragment *);
	void assignment_expr (istream&, script_code_fragment *);

	// for parser
	void function_decl (istream&, script_code_fragment *);
	void continue_stmt (istream&, script_code_fragment *);
	void break_stmt (istream&, script_code_fragment *);
	void do_while_stmt (istream&, script_code_fragment *);
	void while_stmt (istream&, script_code_fragment *);
	void for_stmt (istream&, script_code_fragment *);
	void select_stmt (istream&, script_code_fragment *);
	void case_stmt (istream&, script_code_fragment *);
	void default_stmt (istream&, script_code_fragment *);
	void if_else_stmt (istream&, script_code_fragment *);
	void expression_stmt (istream&, script_code_fragment *);
//	void echo_stmt (istream&, script_code_fragment *);
	void compound_stmt (istream&, script_code_fragment *);
	void single_stmt (istream&, script_code_fragment *);
	void statement (istream&, script_code_fragment *);
	void program (istream&, script_code_fragment *);

	// for garbage collector
	void collect (unsigned long);

	// for parser
	void execute (unsigned long);

public:

	script_parser ();
	~script_parser ();

	void evaluate (istream&);
};

#endif /* __script_parser_h__ */
