#include "script_parser.h"

script_keyword keywords [] = 
	{	
		{ tt_kw_true,		"true" },
		{ tt_kw_false,		"false" } ,
		{ tt_kw_empty,		"empty" },
		{ tt_kw_collection,	"collection" },
		{ tt_kw_array,		"array" },
		{ tt_kw_is_empty,	"is_empty" },
//		{ tt_kw_echo,		"echo" },
		{ tt_kw_var,		"var" },
		{ tt_kw_local,		"local" },
		{ tt_kw_function,	"function" },
		{ tt_kw_return,		"return" },
		{ tt_kw_while,		"while" },
		{ tt_kw_do,			"do" },
		{ tt_kw_for,		"for" },
		{ tt_kw_break,		"break" },
		{ tt_kw_continue,	"continue" },
		{ tt_kw_select,		"select" },
		{ tt_kw_case,		"case" },
		{ tt_kw_default,	"default" },
		{ tt_kw_if,			"if" },
		{ tt_kw_else,		"else" },
		{ tt_end_of_table,	"" }
	};

void _EXPECT (int test, int expected)
{
	if (test != expected) {
		throw script_exception ("Illegal token");
	}
}

script_parser::script_parser () : stack (5000)
{
	stack.resize (0);
}

script_parser::~script_parser () {
}

void script_parser::read_character (istream& is)
{
	lookahead = is.get ();
	if (lookahead == '\n') {
		row++;
		column = 0;
	} else if (lookahead == '\t') {
		column += 4;
	} else {
		column++;
	}
}

void script_parser::skip_comment (istream& is)
{
	do {
		read_character (is);
	} while (lookahead != '\r' && lookahead != '\n' && !(is.eof ()));
	read_character (is);	
	if (lookahead == '\n') {
		read_character (is);
	}
}

void script_parser::read_identifier (istream& is)
{
	while (isdigit (lookahead) || 
	   isalpha (lookahead) || 
	   lookahead == '_')
	{
		token.content += tolower (lookahead);
		read_character (is);
	}
	for (int i=0; keywords [i].token_type != tt_end_of_table; i++) {
		if (keywords [i].content == token.content) { 
			token.token_class = tc_keyword;
			token.token_type = keywords [i].token_type;
			return;
		}
	}
	token.token_class = tc_identifier;
	token.token_type = tt_identifier;
}

void script_parser::read_number (istream& is)
{
	if (lookahead == '0' && (is.peek () == 'X' || is.peek () == 'x')) {
		token.content += lookahead; read_character (is);
		token.content += lookahead; read_character (is);
		while (isxdigit (lookahead)) {
			token.content += lookahead; 
			read_character (is);
		}
	} else {
		while (isdigit (lookahead)) {
			token.content += lookahead; 
			read_character (is);
		}
		if (lookahead == '.') {
			token.content += lookahead; 
			read_character (is);
			while (isdigit (lookahead)) {
				token.content += lookahead; 
				read_character (is);
			}
			token.token_type = tt_single;
			token.token_class = tc_constant;
			return;
		}
	}
	if (lookahead == 'U' || lookahead == 'u') {
		token.token_type = tt_unsigned_integer;
		read_character (is);
	} else {
		token.token_type = tt_integer;
	}
	token.token_class = tc_constant;
}

void script_parser::read_string (istream& is)
{
	read_character (is);
	while (lookahead != '\"') {
		if (lookahead == '\\') {
			read_character (is);
			if (lookahead == 'n') {
				token.content += "\n";
				read_character (is);
				continue;
			} else if (lookahead == 't') {
				token.content += "\t";
				read_character (is);
				continue;
			}
		}
		token.content += lookahead;
		read_character (is);
	}
	read_character (is);
	token.token_class = tc_constant;
	token.token_type = tt_string;
}

void script_parser::read_next_token (istream& is)
{
	token.content = "";
	while (1) {
		if (is.eof () || lookahead == 0) { 
			token.token_class = tc_delimiter; 
			token.token_type = tt_eof;
			return;
		} else if (isspace (lookahead)) {
			while (isspace (lookahead)) read_character (is);
			continue;
		} else if (lookahead == '#') {
			skip_comment (is);
			continue;
		}
		token.row = row; token.column = column;
		if (lookahead == '~') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_bitwise_complement; 
		} else if (lookahead == '^') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_bitwise_exclusive_or; 
		} else if (lookahead == '*') { 
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_multiplication_assignment;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_multiplication; 
			}
		} else if (lookahead == '/') { 
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_division_assignment;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_division; 
			}
		} else if (lookahead == '%') {
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_modulus_assignment;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_modulus; 
			}
		} else if (lookahead == '+') { 
			if (is.peek () == '+') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_increment;
			} else if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_addition_assignment;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_addition; 
			}
		} else if (lookahead == '-') {
			if (is.peek () == '-') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_decrement;
			} else if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_subtraction_assignment;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_subtraction; 
			}
		} else if (lookahead == '>') { 
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_greater_then_or_equal_to;
			} else if (is.peek () == '>') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_right_shift;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_greater_then; 
			}
		} else if (lookahead == '<') {
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_less_then_or_equal_to;
			} else if (is.peek () == '<') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_left_shift;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_less_then; 
			}
		} else if (lookahead == '!') { 
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_inequality;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_logical_negation;
			}
		} else if (lookahead == '&') { 
			if (is.peek () == '&') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_logical_and;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_bitwise_and;
			}
		} else if (lookahead == '|') { 
			if (is.peek () == '|') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_logical_or;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_bitwise_inclusive_or;
			}
		} else if (lookahead == '(') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_opened_round_bracket;
		} else if (lookahead == ')') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_closed_round_bracket;
		} else if (lookahead == '[') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_opened_square_bracket;
		} else if (lookahead == ']') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_closed_square_bracket;
		} else if (lookahead == '{') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_opened_brace;
		} else if (lookahead == '}') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_closed_brace;
		} else if (lookahead == '=') {
			if (is.peek () == '=') {
				read_character (is);
				token.token_class = tc_delimiter; 
				token.token_type = tt_equality;
			} else {
				token.token_class = tc_delimiter; 
				token.token_type = tt_assignment;
			}
		} else if (lookahead == ':') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_colon;
		} else if (lookahead == ';') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_semicolon;
		} else if (lookahead == ',') {
			token.token_class = tc_delimiter; 
			token.token_type = tt_comma;
		} else if (lookahead == '.') {
			if (isdigit (is.peek ())) {
				read_number (is);
				return;
			} else if (isalpha (is.peek ()) || is.peek () == '_') {
				token.token_type = tt_dot;
			}
			throw script_exception ("illegal character");
		} else if (lookahead == '\"') {
			read_string (is);
			return;
		} else if (isdigit (lookahead)) {
			read_number (is);
			return;
		} else if (isalpha (lookahead) || lookahead == '_') {
			read_identifier (is);
			return;
		} else {
//			cout << "code: " << hex << (unsigned long)lookahead << endl;
//			cout << "eof: " << hex << (unsigned long)is.eof () << endl;
			throw script_exception ("illegal character");
		}
		read_character (is);
		return; 
	}
}

/*
script_token * script_parser::read (istream& is)
{
	if (cache.size () > 0) {
		cache.pop_front ();
	}
	if (cache.size () > 0) {
		return &cache.front ();
	}
	return peek (is);
}

script_token * script_parser::get (istream& is)
{
	if (cache.size () > 0) {
		return &cache.front ();
	}
	return read (is);
}

script_token * script_parser::peek (istream& is)
{
	read_next_token (is);
	cache.push_back (token);
	return &cache.back ();
}
*/

void script_parser::var_expr 
	(
	istream& is, 
	string ident
	)
{
	script_container	var;
	long				offset;

	if (_function_scope) {
		// try to find an ident in the LOCAL symbolic table
		map<string, unsigned long>::iterator pos = stbl_local.find (ident);
		if (pos != stbl_local.end ()) {
#ifdef __DEBUG__
			cout << "local variable found: " << ident << endl;
#endif
			code_buffer.push_back (__ENCODE_OPCODE (opcode_push_local_ref, token.row));
			code_buffer.push_back ((* pos).second);
		} else {
			// create local variable
#ifdef __DEBUG__
			cout << "local variable created: " << ident << endl;
#endif
			offset = (long)stbl_local.size () - _func_args_count;
			stbl_local [ident] = offset;
			code_buffer.push_back (__ENCODE_OPCODE (opcode_push_local_ref, token.row));
			code_buffer.push_back (offset);
		}
	} else {
		// try to find an ident in the GLOBAL symbolic table
		map<string, unsigned long>::iterator pos = stbl_global.find (ident);
		if (pos != stbl_global.end ()) {
#ifdef __DEBUG__			
			cout << "global variable found: " << ident << endl;
#endif
			code_buffer.push_back (__ENCODE_OPCODE (opcode_push_ref, token.row));
			code_buffer.push_back ((* pos).second);
		} else {
			if (!_function_scope) {
				// create global variable
#ifdef __DEBUG__
				cout << "global variable created: " << ident << endl;
#endif
				heap.resize (heap.size () + 1);
				offset = (long)(heap.size () - 1);
				stbl_global [ident] = offset;
				code_buffer.push_back (__ENCODE_OPCODE (opcode_push_ref, token.row));
				code_buffer.push_back (offset);
			}
		}
	}
}

long script_parser::func_args_stmt 
	(
	istream& is, 
	script_code_fragment * fragment
	)
{
	long	count = 0;

	_EXPECT (token.token_type, tt_opened_round_bracket);
	read_next_token (is);

	if (token.token_type != tt_closed_round_bracket) {
		if (token.token_type != tt_closed_round_bracket) {
			for (;;) {
				assignment_expr (is, fragment);
				count++;
				if (token.token_type != tt_comma) {
					break;
				}
				read_next_token (is);
			}
		}
	}
	_EXPECT (token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	return count;
}

void script_parser::return_stmt 
	(
	istream& is, 
	script_code_fragment * fragment
	)
{
	map<string, unsigned long>::iterator	p;

#ifdef __DEBUG__
	cout << "return" << endl;
#endif

	script_code_fragment * statement_fr	= new script_code_fragment ();
	fragment->attach (statement_fr);

	if (_function_scope) {
		if (token.token_type != tt_semicolon) {
			statement_fr->set_code_start ((unsigned long)code_buffer.size ());
			var_expr (is, "return");
			assignment_expr (is, statement_fr);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_pop_local, token.row));
			code_buffer.push_back (__ENCODE_OPCODE (opcode_return, token.row));
			statement_fr->set_code_end ((unsigned long)code_buffer.size ());
		}
		_EXPECT(token.token_type, tt_semicolon);
		read_next_token (is);
	} else {
		throw script_exception ("return statement is outside of function statement.");
	}
}

void script_parser::custom_func_expr
	(
	istream& is, 
	script_custom_function * scfunc, 
	script_code_fragment * fragment
	)
{
	long	count;

	// reserve space on stack for result
	code_buffer.push_back (__ENCODE_OPCODE (opcode_load_empty, token.row));

	// collect arguments
	count = func_args_stmt (is, fragment);

	// check for argument number
	if (count != scfunc->arg_count) {
		throw script_exception ("wrong number of arguments.");
	}

	// call the function
	code_buffer.push_back (__ENCODE_OPCODE (opcode_custom_function_call, token.row));
	fragment->set_jmp ((unsigned long)code_buffer.size (), scfunc->entry_point);
	code_buffer.push_back (0);

	// clean stack after function call
	code_buffer.push_back (__ENCODE_OPCODE (opcode_roll_stack_back, token.row));
	code_buffer.push_back (count);
}

void script_parser::predefined_func_expr 
	(
	istream& is, 
	script_predefined_function * spfunc, 
	script_code_fragment * fragment
	)
{
	long			count;

	// collect arguments
	count = func_args_stmt (is, fragment);

	// check for argument number
	if (count < spfunc->_arg_count) {
		throw script_exception ("wrong number of arguments.");
	}

	// call the function
	code_buffer.push_back (__ENCODE_OPCODE (opcode_predefined_function_call, token.row));
	code_buffer.push_back ((unsigned long)spfunc);
	code_buffer.push_back (count);
}

void script_parser::func_expr 
	(
	istream& is, 
	string ident, 
	script_code_fragment * fragment
	)
{
	map<string, script_custom_function>::iterator		p1;
	script_predefined_function *						p2;

	p1 = _custom_functions.find (ident);
	if (p1 != _custom_functions.end ()) {
		custom_func_expr (is, &(* p1).second, fragment);
	} else {
		p2 = get_predefined_function (ident);
		if (p2) {
			predefined_func_expr (is, p2, fragment);
		} else {
			throw script_exception ("function not found.");
		}
	}
}

void script_parser::primary_expr (istream& is, script_code_fragment * fragment)
{
	script_container	c;

	if (token.token_type == tt_increment) {
#ifdef __DEBUG__
		cout << "prefix++" << endl;
#endif
		read_next_token (is);
		primary_expr (is, fragment);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_increment, token.row));
	} else if (token.token_type == tt_decrement) {
#ifdef __DEBUG__
		cout << "prefix--" << endl;
#endif
		read_next_token (is);
		primary_expr (is, fragment);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_decrement, token.row));
	} else if (token.token_type == tt_identifier) {
		string ident = token.content;
		read_next_token (is);
		if (token.token_type == tt_opened_round_bracket) {
#ifdef __DEBUG__
			cout << "--- function_expr ---" << endl;
#endif
			func_expr (is, ident, fragment);
		} else if (token.token_type == tt_opened_square_bracket) { 
#ifdef __DEBUG__
			cout << "[]" << endl;
#endif
			var_expr (is, ident);
			_EXPECT(token.token_type, tt_opened_square_bracket);
			read_next_token (is);
			assignment_expr (is, fragment);
			
			_EXPECT(token.token_type, tt_closed_square_bracket);
			read_next_token (is);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_array_subscript, token.row));
		} else {
#ifdef __DEBUG__
			cout << "ident: " << token.content << endl;
#endif
			var_expr (is, ident);
		}
	} else if (token.token_type == tt_integer) {
		int val = strtol (token.content.c_str (), NULL, 0);
		read_next_token (is);
		c.set_integer (val);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "integer: " << val << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
	} else if (token.token_type == tt_unsigned_integer) {
		unsigned long val = (unsigned long)strtol (token.content.c_str (), NULL, 0);
		read_next_token (is);
		script_container c;
		c.set_unsigned_integer (val);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << hex << val << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
	} else if (token.token_type == tt_single) {
		float val = (float)atof (token.content.c_str ());
		read_next_token (is);
		script_container c;
		c.set_single (val);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "single: " << val << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
	} else if (token.token_type == tt_string) {
		script_container c;
		c.set_object (new script_string_object (token.content));
		read_next_token (is);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "string: " << c.to_string () << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
	} else if (token.token_type == tt_kw_true) {
		script_container c;
		c.set_boolean (true);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "boolean: " << c.to_boolean () << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
		read_next_token (is);
	} else if (token.token_type == tt_kw_false) {
		script_container c;
		c.set_boolean (false);
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "boolean: " << c.to_boolean () << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
		read_next_token (is);

	// create collection
	} else if (token.token_type == tt_kw_collection) {
		script_container c;
		c.set_object (new script_collection_object ());
		heap.push_back (c);
#ifdef __DEBUG__
		cout << "collection created" << endl;
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
		read_next_token (is);

	// create array
	} else if (token.token_type == tt_kw_array) {
		script_container c;
		c.set_object (new script_array_object ());
		heap.push_back (c);
#ifdef __DEBUG__
		printf ("array created\n");
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
		read_next_token (is);

	} else if (token.token_type == tt_kw_empty) {
		script_container c;
		heap.push_back (c);
#ifdef __DEBUG__
		printf ("empty\n");
#endif
		code_buffer.push_back (__ENCODE_OPCODE (opcode_push, token.row));
		code_buffer.push_back ((long)(heap.size () - 1));
		read_next_token (is);
	} else if (token.token_type == tt_opened_round_bracket) {
		read_next_token (is);
#ifdef __DEBUG__
		printf ("(\n");
#endif
		assignment_expr (is, fragment);
		_EXPECT(token.token_type, tt_closed_round_bracket);
		read_next_token (is);
#ifdef __DEBUG__
		printf (")\n");
#endif
	} else {
		throw script_exception("No operand found.");
	}
}

void script_parser::postfix_expr (istream& is, script_code_fragment * fragment) 
{
	primary_expr (is, fragment);
	
	if (token.token_type == tt_increment) {
#ifdef __DEBUG__
		printf ("postfix++\n");
#endif
		read_next_token (is);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_duplicate_topmost, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_dereference, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_swap, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_increment, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_delete_topmost, token.row));
	} else if (token.token_type == tt_decrement) {
#ifdef __DEBUG__
		printf ("postfix--\n");
#endif
		read_next_token (is);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_duplicate_topmost, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_dereference, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_swap, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_decrement, token.row));
		code_buffer.push_back (__ENCODE_OPCODE (opcode_delete_topmost, token.row));
	}
}

void script_parser::unary_expr (istream& is, script_code_fragment * fragment)
{
	// unary plus
	if (token.token_type == tt_addition) {
		read_next_token (is);
		postfix_expr (is, fragment);
#ifdef __DEBUG__
		printf ("(+)\n");
#endif

	// unary minus
	} else if (token.token_type == tt_subtraction) {
		read_next_token (is);
		postfix_expr (is, fragment);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_unary_negation, token.row));
#ifdef __DEBUG__
		printf ("(-)\n");
#endif

	// logical negation
	} else if (token.token_type == tt_logical_negation) {
		read_next_token (is);
		postfix_expr (is, fragment);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_logical_not, token.row));
#ifdef __DEBUG__
		printf ("!\n");
#endif

	// bitwise complement
	} else if (token.token_type == tt_bitwise_complement) {
		read_next_token (is);
		postfix_expr (is, fragment);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_bitwise_complement, token.row));
#ifdef __DEBUG__
		printf ("~\n");
#endif

	//// address-of
	//} else if (token.token_type == tt_bitwise_and) {
	//	read_next_token (is);
	//	postfix_expr (is, fragment);
	//	code_buffer.push_back (__ENCODE_OPCODE (opcode_bitwise_complement, token.row));
	//	printf ("~\n");

	} else {
		postfix_expr (is, fragment);
	}
}

void script_parser::multiplicative_expr (istream& is, script_code_fragment * fragment)
{
	unary_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_multiplication) {
			read_next_token (is);
			unary_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_multiplication, token.row));
#ifdef __DEBUG__
			printf ("*\n");
#endif
		} else if (token.token_type == tt_division) {
			read_next_token (is);
			unary_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_division, token.row));
#ifdef __DEBUG__
			printf ("/\n");
#endif
		} else if (token.token_type == tt_modulus) {
			read_next_token (is);
			unary_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_modulus, token.row));
#ifdef __DEBUG__
			printf ("%\n");
#endif
		} else {
			break;
		}
	}
}

void script_parser::additive_expr (istream& is, script_code_fragment * fragment)
{
	multiplicative_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_addition) {
			read_next_token (is);
			multiplicative_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_addition, token.row));
#ifdef __DEBUG__
			cout << "+" << endl;
#endif
		} else if (token.token_type == tt_subtraction) {
			read_next_token (is);
			multiplicative_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_subtraction, token.row));
#ifdef __DEBUG__
			cout << "-" << endl;
#endif
		} else {
			break;
		}
	}
}

void script_parser::shift_expr (istream& is, script_code_fragment * fragment)
{
	additive_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_right_shift) {
			read_next_token (is);
			additive_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_right_shift, token.row));
#ifdef __DEBUG__
			printf (">>\n");
#endif
		} else if (token.token_type == tt_left_shift) {
			read_next_token (is);
			additive_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_left_shift, token.row));
#ifdef __DEBUG__
			printf ("<<\n");
#endif
		} else {
			break;
		}
	}
}

void script_parser::relational_expr (istream& is, script_code_fragment * fragment) 
{
	shift_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_less_then) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_less_then, token.row));
#ifdef __DEBUG__
			printf ("<\n");
#endif
		} else if (token.token_type == tt_less_then_or_equal_to) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_less_then_or_equal_to, token.row));
#ifdef __DEBUG__
			printf ("<=\n");
#endif
		} else if (token.token_type == tt_greater_then) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_greater_then, token.row));
#ifdef __DEBUG__
			printf (">\n");
#endif
		} else if (token.token_type == tt_greater_then_or_equal_to) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_greater_then_or_equal_to, token.row));
#ifdef __DEBUG__
			printf (">=\n");
#endif
		} else if (token.token_type == tt_equality) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_equality, token.row));
#ifdef __DEBUG__
			printf ("==\n");
#endif
		} else if (token.token_type == tt_inequality) {
			read_next_token (is);
			shift_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_inequality, token.row));
#ifdef __DEBUG__
			printf ("!=\n");
#endif
		} else {
			break;
		}
	}
}

void script_parser::bitwise_expr (istream& is, script_code_fragment * fragment)
{
	relational_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_bitwise_and) {
			read_next_token (is);
			relational_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_bitwise_and, token.row));
#ifdef __DEBUG__
			printf ("&\n");
#endif
		} else if (token.token_type == tt_bitwise_exclusive_or) {
			read_next_token (is);
			relational_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_bitwise_exclusive_or, token.row));
#ifdef __DEBUG__
			printf ("^\n");
#endif
		} else if (token.token_type == tt_bitwise_inclusive_or) {
			read_next_token (is);
			relational_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_bitwise_inclusive_or, token.row));
#ifdef __DEBUG__
			printf ("|\n");
#endif
		} else {
			break;
		}
	}
}

void script_parser::logical_expr (istream& is, script_code_fragment * fragment)
{
	bitwise_expr (is, fragment);
	
	while (1) {
		if (token.token_type == tt_logical_and) {
			read_next_token (is);
			bitwise_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_logical_and, token.row));
#ifdef __DEBUG__
			printf ("&&\n");
#endif
		} else if (token.token_type == tt_logical_or) {
			read_next_token (is);
			bitwise_expr (is, fragment);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_logical_or, token.row));
#ifdef __DEBUG__
			printf ("||\n");
#endif
		} else {
			break;
		}
	}
}

void script_parser::assignment_expr (istream& is, script_code_fragment * fragment)
{
	unsigned long	op;
	
	logical_expr (is, fragment);
	
	if (token.token_type == tt_assignment) {
		op = __ENCODE_OPCODE (opcode_pop, token.row);
		read_next_token (is);
		assignment_expr (is, fragment);
		code_buffer.push_back (op);
#ifdef __DEBUG__
		cout << "=" << endl;
#endif
	}
}

void script_parser::function_decl (istream& is, script_code_fragment * fragment)
{
	script_custom_function	cust_func;
	vector<string>			args;

	// enter to the local scope
	_function_scope = true;
//	b_return = false;

	// clear local symbolic table
	stbl_local.clear ();

	script_code_fragment * prolog_code_fr = new script_code_fragment ();
	script_code_fragment * function_body_fr = new script_code_fragment ();
	script_code_fragment * epilog_code_fr = new script_code_fragment ();

	fragment->attach (prolog_code_fr);
	fragment->attach (function_body_fr);
	fragment->attach (epilog_code_fr);
	
	
	string ident = token.content;
#ifdef __DEBUG__	
	cout << "creating function: " << ident << endl;
#endif

	map<string, script_custom_function>::iterator pos = _custom_functions.find (ident);
	if (pos != _custom_functions.end ()) {
		throw script_exception ("function already exist.");
	}

	read_next_token (is);
	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);

	if (token.token_type != tt_closed_round_bracket) {
		for (;;) {
			if (token.token_type == tt_identifier) {
#ifdef __DEBUG__
				cout << "function parameter " << (long)args.size () << ": " << token.content << endl;
#endif
				args.push_back (token.content);
				read_next_token (is);
			} else {
				throw script_exception ("an identifier expected.");
			}
			if (token.token_type != tt_comma) {
				break;
			}
			read_next_token (is);
		}
	}

	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);
	_EXPECT(token.token_type, tt_opened_brace);

	// create local vars from arguments
	for (int i=0; i<(int)args.size (); i++) {
		stbl_local [args [i]] = - ((int)args.size () - i);
	}
	stbl_local ["return"] = - ((int)args.size () + 1);
#ifdef __DEBUG__
	cout << (int)args.size () << " arguments found" << endl;
#endif
	_func_args_count = (long)stbl_local.size ();

	// register function
	cust_func.entry_point = prolog_code_fr;
	cust_func.arg_count = (unsigned long)args.size ();
	_custom_functions [ident] = cust_func;

	// function body statement
	compound_stmt (is, function_body_fr);

	// create prolog code
	prolog_code_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_allocate_stack_space, token.row));
	code_buffer.push_back ((unsigned long)(stbl_local.size () - args.size () - 1));
	prolog_code_fr->set_code_end ((unsigned long)code_buffer.size ());

	// create epilog code
	epilog_code_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_return, token.row));
	epilog_code_fr->set_code_end ((unsigned long)code_buffer.size ());

	// exit from the local scope
	_function_scope = false;
}

void script_parser::continue_stmt (istream& is, script_code_fragment * fragment)
{
#ifdef __DEBUG__	
	cout << "--- continue_stmt ---" << endl;
#endif

	script_code_fragment * st = new script_code_fragment ();
	fragment->attach (st);

	script_code_fragment * repeat = scope_stack.back ()->get ("repeat");
	if (repeat) {
		st->set_code_start ((unsigned long)code_buffer.size ());
		code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
		st->set_jmp ((unsigned long)code_buffer.size (), repeat);
		code_buffer.push_back (0);
		st->set_code_end ((unsigned long)code_buffer.size ());
	} else {
		throw script_exception ("Continue statement is outside of while/do/for statement.");
	}
	
	_EXPECT(token.token_type, tt_semicolon);
	read_next_token (is);
}

void script_parser::break_stmt (istream& is, script_code_fragment * fragment)
{
#ifdef __DEBUG__
	cout << "--- break_stmt ---" << endl;
#endif

	script_code_fragment * st = new script_code_fragment ();
	fragment->attach (st);

	if (scope_stack.size () > 0) {
		script_code_fragment * exit_point = scope_stack.back ()->get ("exit");
		if (exit_point) {
			st->set_code_start ((unsigned long)code_buffer.size ());
			code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
			st->set_jmp ((unsigned long)code_buffer.size (), exit_point);
			code_buffer.push_back (0);
			st->set_code_end ((unsigned long)code_buffer.size ());
		} else {
			throw script_exception ("Break statement is outside of while/do/for/select statement.");
		}
	} else {
		throw script_exception ("Break statement is outside of while/do/for/select statement.");
	}
	
	_EXPECT(token.token_type, tt_semicolon);
	read_next_token (is);
}

void script_parser::do_while_stmt (istream& is, script_code_fragment * fragment)
{
	script_scope * scope;

	// code fragments
	script_code_fragment * statement_fr	= new script_code_fragment ();
	script_code_fragment * expression_fr = new script_code_fragment ();
	script_code_fragment * exit_fr = new script_code_fragment ();

	// create memory map
	fragment->attach (statement_fr);
	fragment->attach (expression_fr);
	fragment->attach (exit_fr);

	scope = new script_scope ();
	scope_stack.push_back (scope);
	scope->append ("repeat", expression_fr);
	scope->append ("exit", exit_fr);

	// statement
	statement (is, statement_fr);
	// statement
	
	_EXPECT(token.token_type, tt_kw_while);
	read_next_token (is);

	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);
	// expression
	expression_fr->set_code_start ((unsigned long)code_buffer.size ());
	assignment_expr (is, expression_fr);
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump_if_true, token.row));
	expression_fr->set_jmp ((unsigned long)code_buffer.size (), statement_fr);
	code_buffer.push_back (0);
	expression_fr->set_code_end ((unsigned long)code_buffer.size ());
	// expression
	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	scope_stack.pop_back ();
}

void script_parser::while_stmt (istream& is, script_code_fragment * fragment)
{
	script_scope * scope;

	// code fragments
	script_code_fragment * expression_fr = new script_code_fragment ();
	script_code_fragment * statement_fr	= new script_code_fragment ();
	script_code_fragment * jump_fr = new script_code_fragment ();
	script_code_fragment * exit_fr = new script_code_fragment ();

	// create memory map
	fragment->attach (expression_fr);
	fragment->attach (statement_fr);
	fragment->attach (jump_fr);
	fragment->attach (exit_fr);

	scope = new script_scope ();
	scope_stack.push_back (scope);
	scope->append ("repeat", expression_fr);
	scope->append ("exit", exit_fr);

	
	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);
	// expression
	expression_fr->set_code_start ((unsigned long)code_buffer.size ());
	assignment_expr (is, expression_fr);
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump_if_false, token.row));
	expression_fr->set_jmp ((unsigned long)code_buffer.size (), exit_fr);
	code_buffer.push_back (0);
	expression_fr->set_code_end ((unsigned long)code_buffer.size ());
	// expression
	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	// statement
	statement (is, statement_fr);

	jump_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
	jump_fr->set_jmp ((unsigned long)code_buffer.size (), expression_fr);
	code_buffer.push_back (0);
	jump_fr->set_code_end ((unsigned long)code_buffer.size ());

	scope_stack.pop_back ();
}

void script_parser::for_stmt (istream& is, script_code_fragment * fragment)
{
	script_scope * scope;

	// code fragments
	script_code_fragment * init		= new script_code_fragment ();
	script_code_fragment * cond		= new script_code_fragment ();
	script_code_fragment * iter		= new script_code_fragment ();
	script_code_fragment * st		= new script_code_fragment ();
	script_code_fragment * exit_lbl = new script_code_fragment ();

	// create memory map
	fragment->attach (init);
	fragment->attach (cond);
	fragment->attach (st);
	fragment->attach (iter);
	fragment->attach (exit_lbl);

	scope = new script_scope ();
	scope_stack.push_back (scope);
	scope->append ("repeat", iter);
	scope->append ("exit", exit_lbl);

	read_next_token (is);
	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);

	// initialization
	if (token.token_type != tt_semicolon) {
		init->set_code_start ((unsigned long)code_buffer.size ());
		assignment_expr (is, init);
		init->set_code_end ((unsigned long)code_buffer.size ());
	}
	
	_EXPECT(token.token_type, tt_semicolon);
	read_next_token (is);

	// condition
	if (token.token_type != tt_semicolon) {
		cond->set_code_start ((unsigned long)code_buffer.size ());
		assignment_expr (is, cond);
		code_buffer.push_back (__ENCODE_OPCODE (opcode_jump_if_false, token.row));
		cond->set_jmp ((unsigned long)code_buffer.size (), exit_lbl);
		code_buffer.push_back (0);
		cond->set_code_end ((unsigned long)code_buffer.size ());
	}
	
	_EXPECT(token.token_type, tt_semicolon);
	read_next_token (is);

	// step calculation
	iter->set_code_start ((unsigned long)code_buffer.size ());
	if (token.token_type != tt_closed_round_bracket) {
		assignment_expr (is, iter);
	}
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
	iter->set_jmp ((unsigned long)code_buffer.size (), cond);
	code_buffer.push_back (0);
	iter->set_code_end ((unsigned long)code_buffer.size ());
	
	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	// statement
	statement (is, st);

	scope_stack.pop_back ();
}

void script_parser::select_stmt (istream& is, script_code_fragment * fragment)
{
	script_scope * scope;

	// create code fragments
	script_code_fragment * expression_fr = new script_code_fragment ();
	script_code_fragment * jump_fr = new script_code_fragment ();
	script_code_fragment * statement_fr = new script_code_fragment ();
	script_code_fragment * exit_fr = new script_code_fragment ();

	// create memory map
	fragment->attach (expression_fr);
	fragment->attach (jump_fr);
	fragment->attach (statement_fr);
	fragment->attach (exit_fr);

	// create current scope information
	scope = new script_scope ();
	scope_stack.push_back (scope);
	scope->append ("expression", expression_fr);
	scope->append ("default", jump_fr);
	scope->append ("exit", exit_fr);

	// generate expression code
	
	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);
	expression_fr->set_code_start ((unsigned long)code_buffer.size ());
	assignment_expr (is, expression_fr);
	expression_fr->set_code_end ((unsigned long)code_buffer.size ());
	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	// generate jump code
	jump_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
	jump_fr->set_jmp ((unsigned long)code_buffer.size (), exit_fr);
	code_buffer.push_back (0);
	jump_fr->set_code_end ((unsigned long)code_buffer.size ());

	// parse statement
	statement (is, statement_fr);

	// generate exit code
	exit_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_delete_topmost, token.row));
	exit_fr->set_code_start ((unsigned long)code_buffer.size ());
}

void script_parser::case_stmt (istream& is, script_code_fragment * fragment)
{
	if (token.token_class != tc_constant) {
		throw script_exception ("Case statement argument have to be a constant value.");
	}

	if (scope_stack.size () > 0) {
		script_code_fragment * expression_fr = scope_stack.back ()->get ("expression");
		if (expression_fr) 
		{
			script_code_fragment * condition_fr = new script_code_fragment ();
			expression_fr->insert_after (condition_fr);
			script_code_fragment * statement_fr = new script_code_fragment ();
			fragment->attach (statement_fr);
	
			condition_fr->set_code_start ((unsigned long)code_buffer.size ());
			code_buffer.push_back (__ENCODE_OPCODE (opcode_duplicate_topmost, token.row));
			primary_expr (is, condition_fr);
			code_buffer.push_back (__ENCODE_OPCODE (opcode_equality, token.row));
			code_buffer.push_back (__ENCODE_OPCODE (opcode_jump_if_true, token.row));
			condition_fr->set_jmp ((unsigned long)code_buffer.size (), statement_fr);
			code_buffer.push_back (0);
			condition_fr->set_code_end ((unsigned long)code_buffer.size ());

			
			_EXPECT(token.token_type, tt_colon);
			read_next_token (is);

			statement (is, statement_fr);
		} 
		else 
		{
			throw script_exception ("Case statement is outside of select statement.");
		}
	} else {
		throw script_exception ("Case statement is outside of select statement.");
	}
}

void script_parser::default_stmt (istream& is, script_code_fragment * fragment)
{
	if (scope_stack.size () > 0) {
		script_code_fragment * jump_fr = scope_stack.back ()->get ("default");
		if (jump_fr) 
		{
			
			_EXPECT(token.token_type, tt_colon);
			read_next_token (is);

			script_code_fragment * default_fr = new script_code_fragment ();
			jump_fr->insert_before (default_fr);
			script_code_fragment * statement_fr = new script_code_fragment ();
			fragment->attach (statement_fr);
	
			default_fr->set_code_start ((unsigned long)code_buffer.size ());
			code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
			default_fr->set_jmp ((unsigned long)code_buffer.size (), statement_fr);
			code_buffer.push_back (0);
			default_fr->set_code_end ((unsigned long)code_buffer.size ());

			statement (is, statement_fr);
		} 
		else 
		{
			throw script_exception ("Default statement is outside of select statement.");
		}
	} else {
		throw script_exception ("Default statement is outside of select statement.");
	}
}

void script_parser::if_else_stmt (istream& is, script_code_fragment * fragment)
{
	// create code fragments
	script_code_fragment * expression_fr = new script_code_fragment ();
	script_code_fragment * statement1_fr = new script_code_fragment ();
	script_code_fragment * jump_fr = new script_code_fragment ();
	script_code_fragment * statement2_fr = new script_code_fragment ();
	script_code_fragment * exit_fr = new script_code_fragment ();

	// create memory map
	fragment->attach (expression_fr);
	fragment->attach (statement1_fr);
	fragment->attach (jump_fr);
	fragment->attach (statement2_fr);
	fragment->attach (exit_fr);

	
	_EXPECT(token.token_type, tt_opened_round_bracket);
	read_next_token (is);
	// expression
	expression_fr->set_code_start ((unsigned long)code_buffer.size ());
	assignment_expr (is, expression_fr);
	code_buffer.push_back (__ENCODE_OPCODE (opcode_jump_if_false, token.row));
	expression_fr->set_jmp ((unsigned long)code_buffer.size (), statement2_fr);
	code_buffer.push_back (0);
	expression_fr->set_code_end ((unsigned long)code_buffer.size ());
	// expression
	_EXPECT(token.token_type, tt_closed_round_bracket);
	read_next_token (is);

	// statement
	statement (is, statement1_fr);

	
	if (token.token_type == tt_kw_else) {
		read_next_token (is);
		jump_fr->set_code_start ((unsigned long)code_buffer.size ());
		code_buffer.push_back (__ENCODE_OPCODE (opcode_jump, token.row));
		jump_fr->set_jmp ((unsigned long)code_buffer.size (), exit_fr);
		code_buffer.push_back (0);
		jump_fr->set_code_end ((unsigned long)code_buffer.size ());
		// statement
		statement (is, statement2_fr);
		// statement
	}
}

void script_parser::expression_stmt (istream& is, script_code_fragment * fragment)
{
	script_code_fragment *	st;

	st = new script_code_fragment ();
	fragment->attach (st);

	st->set_code_start ((unsigned long)code_buffer.size ());
	assignment_expr (is, st);
	code_buffer.push_back (__ENCODE_OPCODE (opcode_delete_topmost, token.row));
	st->set_code_end ((unsigned long)code_buffer.size ());

	
	_EXPECT(token.token_type, tt_semicolon);
	read_next_token (is);
}

//void script_parser::echo_stmt (istream& is, script_code_fragment * fragment)
//{
//	script_code_fragment *	st;
//
//#ifdef __DEBUG__
//	cout << "--- echo_stmt ---" << endl;
//#endif
//
//	st = new script_code_fragment ();
//	fragment->attach (st);
//
//	st->set_code_start ((unsigned long)code_buffer.size ());
//	assignment_expr (is, st);
//	code_buffer.push_back (__ENCODE_OPCODE (opcode_echo, token.row));
//	
//	while (token.token_type == tt_comma) {
//		read_next_token (is);
//		assignment_expr (is, st);
//		code_buffer.push_back (__ENCODE_OPCODE (opcode_echo, token.row));
//		
//	}
//	st->set_code_end ((unsigned long)code_buffer.size ());
//
//#ifdef __DEBUG__
//	cout << "echo" << endl;
//#endif
//	_EXPECT(token.token_type, tt_semicolon);
//	read_next_token (is);
//}

void script_parser::compound_stmt (istream& is, script_code_fragment * fragment)
{
	read_next_token (is);
	while (token.token_type != tt_closed_brace) {
		statement (is, fragment);
	}
	_EXPECT(token.token_type, tt_closed_brace);
	read_next_token (is);
}

void script_parser::single_stmt (istream& is, script_code_fragment * fragment)
{
	//if (token.token_type == tt_kw_echo) {
	//	read_next_token (is);
	//	echo_stmt (is, fragment);
	if (token.token_type == tt_kw_continue) {
		read_next_token (is);
		continue_stmt (is, fragment);
	} else if (token.token_type == tt_kw_break) {
#ifdef __DEBUG__
		cout << "--- break_stmt ---" << endl;
#endif
		read_next_token (is);
		break_stmt (is, fragment);
	} else if (token.token_type == tt_kw_return) {
#ifdef __DEBUG__
		cout << "--- return_stmt ---" << endl;
#endif
		read_next_token (is);
		return_stmt (is, fragment);
	} else if (token.token_type == tt_kw_local) {
#ifdef __DEBUG__
		cout << "--- local_stmt ---" << endl;
#endif
//		local_stmt (iter);
	} else if (token.token_type == tt_kw_while) {
#ifdef __DEBUG__
		cout << "--- while_stmt ---" << endl;
#endif
		read_next_token (is);
		while_stmt (is, fragment);
	} else if (token.token_type == tt_kw_do) {
#ifdef __DEBUG__
		cout << "--- do_while_stmt ---" << endl;
#endif
		read_next_token (is);
		do_while_stmt (is, fragment);
	} else if (token.token_type == tt_kw_for) {
#ifdef __DEBUG__
		cout << "--- for_stmt ---" << endl;
#endif
		for_stmt (is, fragment);
	} else if (token.token_type == tt_kw_if) {
#ifdef __DEBUG__
		cout << "--- if_else_stmt ---" << endl;
#endif
		read_next_token (is);
		if_else_stmt (is, fragment);
	} else if (token.token_type == tt_kw_select) {
#ifdef __DEBUG__
		cout << "--- select_stmt ---" << endl;
#endif
		read_next_token (is);
		select_stmt (is, fragment);
	} else if (token.token_type == tt_kw_case) {
#ifdef __DEBUG__
		cout << "--- case_stmt ---" << endl;
#endif
		read_next_token (is);
		case_stmt (is, fragment);
	} else if (token.token_type == tt_kw_default) {
#ifdef __DEBUG__
		cout << "--- default_stmt ---" << endl;
#endif
		read_next_token (is);
		default_stmt (is, fragment);
	} else if (token.token_type == tt_semicolon) {
#ifdef __DEBUG__
		cout << "--- empty statement ---" << endl;
#endif
		read_next_token (is);
	} else {
#ifdef __DEBUG__
		cout << "--- expression_stmt ---" << endl;
#endif
		expression_stmt (is, fragment);
	}
}

void script_parser::statement (istream& is, script_code_fragment * fragment)
{
	if (token.token_type == tt_opened_brace) {
		compound_stmt (is, fragment);
	} else {
		single_stmt (is, fragment);
	}
}

void script_parser::program (istream& is, script_code_fragment * fragment)
{
	script_code_fragment * code_fr = new script_code_fragment ();
	script_code_fragment * quit_fr = new script_code_fragment ();
	script_code_fragment * functions_fr = new script_code_fragment ();

	fragment->attach (code_fr);
	fragment->attach (quit_fr);
	fragment->attach (functions_fr);

	
	while (token.token_type != tt_eof) {
		if (token.token_type == tt_kw_function) {
#ifdef __DEBUG__
			cout << "--- function_decl ---" << endl;
#endif
			read_next_token (is);
			function_decl (is, functions_fr);
		} else {
			statement (is, code_fr);
		}
		
	}

	// the program will stop here
	quit_fr->set_code_start ((unsigned long)code_buffer.size ());
	code_buffer.push_back (__ENCODE_OPCODE (opcode_quit, token.row));
	quit_fr->set_code_end ((unsigned long)code_buffer.size ());
}

void script_parser::collect (unsigned long wave)
{
	for (int i=0; i<heap.size (); i++) {
		heap [i].collect (wave);
	}
	for (int i=0; i<stack.size (); i++) {
		stack [i].collect (wave);
	}
}

void script_parser::execute (unsigned long position)
{
	long	local_stack_start;
	script_container	var;
//	script_object *	result;
	script_container a, b, c;
	unsigned long opcode;
	unsigned long row;

//	script_function_declarator *	p;
//	unsigned int					code [16], * pcode;

//	cout << "--- execution ---" << endl;
//	int cap1 = stack.capacity ();

	// remember where stack starts
	local_stack_start = (long)stack.size ();


	try 
	{
		for (unsigned long i=position; i<(unsigned long)script.size (); i++) 
		{
			opcode = __DECODE_OPCODE (script [i]);
			row = __DECODE_ROW (script [i]);

			if (opcode == opcode_echo) {
	//			cout << "opcode_echo" << endl;
	//			cout << stack.size ();
//				c = stack.back ();
//				cout << c.to_string ();
	//			cout << "output: " << c.to_string () << endl;
//				stack.pop_back ();
			} else if (opcode == opcode_delete_topmost) {
	//			cout << "opcode_delete_topmost" << endl;
				stack.pop_back ();
			} else if (opcode == opcode_duplicate_topmost) {  // !!!!
	//			cout << "opcode_delete_topmost" << endl;
				c.set_empty_locally ();
				c = stack.back ();
				stack.push_back (c);

			// opcode_roll_stack_back
			} else if (opcode == opcode_roll_stack_back) {  // !!!!
	//			cout << "opcode_roll_stack_back" << endl;
				stack.resize (stack.size () - script [++i]);

			// exit program
			} else if (opcode == opcode_quit) {
				return;

			// dereference operator
			} else if (opcode == opcode_dereference) {
				a = stack.back (); stack.pop_back ();
				if (a.is_reference ()) {
					c = a.dereference ();
					stack.push_back (c);
				} else {
					throw script_exception ("have to be l-value");
				}

			// increment topmost element
			} else if (opcode == opcode_increment) {
	//			cout << "opcode_increment" << endl;
				a = stack.back ();
				if (a.is_reference ()) {
					c.set_empty_locally ();
					a.increment (c);
					c.assignment (a);
				} else {
					throw script_exception ("have to be l-value");
				}
			// decrement topmost element
			} else if (opcode == opcode_decrement) {
	//			cout << "opcode_decrement" << endl;
				a = stack.back ();
				if (a.is_reference ()) {
					c.set_empty_locally ();
					a.decrement (c);
					c.assignment (a);
				} else {
					throw script_exception ("have to be l-value");
				}

			} else if (opcode == opcode_pop_local || opcode == opcode_pop) {
	//			cout << "opcode_pop" << endl;
				script_container a = stack.back (); stack.pop_back ();
				script_container c = stack.back ();
				if (c.is_reference ()) {
	//				cout << c.to_string () << endl;
	//				cout << a.to_string () << endl;
					void * ppp1 = (void *)&stack[0];
					a.assignment (c);
	//				cout << c.to_integer () << endl;
				} else {
					throw script_exception ("have to be l-value");
				}
			} else if (opcode == opcode_push_ref) {
	//			cout << "opcode_push_ref" << endl;
				script_container c;
				c.set_reference (heap [script [++i]]);
				stack.push_back (c);
			} else if (opcode == opcode_push_local_ref) {
	//			cout << "opcode_push_local_ref" << endl;
				script_container c;
				c.set_reference (stack [local_stack_start + script [++i]]);
	//			cout << local_stack_start + script [i] << endl;
				void * ppp1 = (void *)&stack[0];
	//			int cap = stack.capacity ();
				stack.push_back (c);
				void * ppp2 = (void *)&stack[0];
	//			cap = stack.capacity ();
				b = stack [(long)stack.size () - 1];
				//cout << c.to_string () << endl;
				//cout << b.to_string () << endl;
				//cout << "----------------" << endl;
				//cout << "stack size: " << (long)stack.size () << endl;
				//cout << "--- stack ---" << endl;
				//for (vector<script_container>::iterator i=stack.begin (); i!=stack.end (); i++) {
				//	cout << "type: " << (* i).to_string () << endl;
				//}
				//cout << "----------------" << endl;
			} else if (opcode == opcode_push_local) {
	//			cout << "opcode_push_local" << endl;
				stack.push_back (stack [local_stack_start + script [++i]]);
			} else if (opcode == opcode_push) {
	//			cout << "opcode_push" << endl;
				stack.push_back (heap [script [++i]]);

			} else if (opcode == opcode_swap) {
	//			cout << "opcode_swap" << endl;
				c.set_empty_locally ();
				c = stack [stack.size () - 2];
				stack [stack.size () - 2] = stack [stack.size () - 1];
				stack [stack.size () - 1] = c;

			// opcode_custom_function_call
			} else if (opcode == opcode_custom_function_call) {
	//			cout << "opcode_custom_function_call" << endl;
				execute (script [++i]);

			// opcode_predefined_function_call
			} else if (opcode == opcode_predefined_function_call) {
	//			cout << "opcode_predefined_function_call" << endl;
				vector<script_container> args;
				script_predefined_function * p = (script_predefined_function *)script [++i];
				unsigned long count = script [++i];
				for (vector<script_container>::iterator i=(stack.end () - count); i!=stack.end (); i++) {
					args.push_back ((* i));
				}
				stack.resize (stack.size () - count);
				stack.push_back (p->_ptr (args));

			} else if (opcode == opcode_return) {
	//			cout << "opcode_return" << endl;
				stack.resize (local_stack_start);
				return;

			} else if (opcode == opcode_load_empty) {
	//			cout << "opcode_load_empty" << endl;
				c.set_empty_locally ();
				stack.push_back (c);
			} else if (opcode == opcode_allocate_stack_space) {
	//			cout << "opcode_load_empty" << endl;
				stack.resize (stack.size () + script [++i]);
				
			} else if (opcode == opcode_jump) {
	//			cout << "opcode_jump" << endl;
				i = script [++i] - 1;
			} else if (opcode == opcode_jump_if_false) {
	//			cout << "opcode_jump_if_false" << endl;
				if (!stack.back ().to_boolean ()) {
					i = script [++i] - 1;
				} else {
					i++;
				}
	//			cout << stack.back ().to_integer () << endl;
				stack.pop_back ();
			} else if (opcode == opcode_jump_if_true) {
	//			cout << "opcode_jump_if_true" << endl;
				if (stack.back ().to_boolean ()) {
					i = script [++i] - 1;
				} else {
					i++;
				}
				stack.pop_back ();

			// subscript operators
			} else if (opcode == opcode_array_subscript) {
	//			cout << "opcode_array_subscript" << endl;
				a = stack.back (); stack.pop_back ();
				b = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				b.array_subscript (c, a);
				stack.push_back (c);

			// unary operators
			} else if (opcode == opcode_bitwise_complement) {
	//			cout << "opcode_bitwise_complement" << endl;
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.bitwise_complement (c);
				stack.push_back (c);
			} else if (opcode == opcode_logical_not) {
	//			cout << "opcode_logical_not" << endl;
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.logical_not (c);
				stack.push_back (c);
			} else if (opcode == opcode_unary_negation) {
	//			cout << "opcode_unary_negation" << endl;
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.unary_minus (c);
				stack.push_back (c);

			// multiplicative operators
			} else if (opcode == opcode_multiplication) {
	//			cout << "opcode_multiplication" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.multiplication (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_division) {
	//			cout << "opcode_division" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.division (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_modulus) {
	//			cout << "opcode_modulus" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.modulus (c, b);
				stack.push_back (c);

			// additive operators
			} else if (opcode == opcode_addition) {
	//			cout << "opcode_addition" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.addition (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_subtraction) {
	//			cout << "opcode_subtraction" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.subtraction (c, b);
				stack.push_back (c);

			// shift operators
			} else if (opcode == opcode_right_shift) {
	//			cout << "opcode_right_shift" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.right_shift (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_left_shift) {
	//			cout << "opcode_left_shift" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.left_shift (c, b);
				stack.push_back (c);
		
			// relational & equality operators
			} else if (opcode == opcode_less_then) {
	//			cout << "opcode_less_then" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.less_than (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_greater_then) {
	//			cout << "opcode_greater_then" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.greater_than (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_less_then_or_equal_to) {
	//			cout << "opcode_less_then_or_equal_to" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.less_than_or_equal_to (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_greater_then_or_equal_to) {
	//			cout << "opcode_greater_then_or_equal_to" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.greater_than_or_equal_to (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_equality) {
	//			cout << "opcode_equality" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.equality (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_inequality) {
	//			cout << "opcode_inequality" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.inequality (c, b);
				stack.push_back (c);

			// bitwise operators
			} else if (opcode == opcode_bitwise_and) {
	//			cout << "opcode_bitwise_and" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.bitwise_and (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_bitwise_exclusive_or) {
	//			cout << "opcode_bitwise_exclusive_or" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.bitwise_exclusive_or (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_bitwise_inclusive_or) {
	//			cout << "opcode_bitwise_inclusive_or" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.bitwise_inclusive_or (c, b);
				stack.push_back (c);

			// logical operators
			} else if (opcode == opcode_logical_and) {
	//			cout << "opcode_logical_and" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.logical_and (c, b);
				stack.push_back (c);
			} else if (opcode == opcode_logical_or) {
	//			cout << "opcode_logical_or" << endl;
				b = stack.back (); stack.pop_back ();
				a = stack.back (); stack.pop_back ();
				c.set_empty_locally ();
				a.logical_or (c, b);
				stack.push_back (c);

			} else {
				throw script_exception ("Unknown opcode.");
			}

			//cout << "----------------" << endl;
			//cout << "stack size: " << (long)stack.size () << endl;
			//cout << "--- stack ---" << endl;
			//for (vector<script_container>::iterator i=stack.begin (); i!=stack.end (); i++) {
			//	cout << "type: " << (* i).to_string () << endl;
			//}
			//cout << "----------------" << endl;
		}
	}
	catch (script_exception e) {
		ostringstream ss;
		ss << "run-time error: (row: " << row << ")" << e.what ();
		throw script_exception (ss.str ());
	}
}

void script_parser::evaluate (istream& is)
{
	ostringstream ss;

	try {
		row = 1; column = 0;
//		cache.clear ();

		read_character (is);
		read_next_token (is);
		_function_scope = false;
		program (is, &memory_map);

		memory_map.construct (script, code_buffer);
		memory_map.resolve (script);
	}
	catch (script_exception e) 
	{
		ss << "row: " << token.row << ", col: " << token.column << ", " << e.what ();
		throw script_exception (ss.str ());
	}

	execute (0);

	//while (1) {
	//	script_token * read_next_token (is);
	//	if (token.token_type == tt_eof) break;
	//	cout << "row:" << token.row << ", col:" << t->column << ", token: " << token.content << endl;
	//}
}
