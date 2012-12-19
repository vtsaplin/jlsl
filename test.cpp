#include <stdio.h>
//#include <conio.h>			// win
#include <stdlib.h>
#include <errno.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#include "compiler.h"
#include "script_parser.h"
#include "smart_pointer.h"
#include "tree_helper.h"

class CTreeTest : public tree_helper<CTreeTest>
{
public:
	string	str;
	CTreeTest (string s) {
		str = s;
	}
	void print () {
		cout << str << endl;
		CTreeTest * p = get_head ();
		while (p) {
			p->print ();
			p = p->get_next ();
		}
	}
};

class str_test : public smart_pointer<str_test>::countable {
public:
	string	_str;
	str_test (string str) {
		_str = str;
	}
	~str_test () {
		cout << "deleted " << _str << endl;
	}
	void print () {
		cout << _str << endl;
	}
};

int main (int argc, char * argv [])
{
//	parser p;
	script_parser	parser;
	script_token	token;
	filebuf fb;


	try {
		if (argc > 1) {
			fb.open (argv [1], ios::in);
			if (fb.is_open ()) {
	  			istream is (&fb);
				parser.evaluate (is);
				//tokenizer.init (&is);
				//while (1) {
				//	token = tokenizer.read ();
				//	if (token.token_type == tt_eof) break;
				//	cout << "row:" << token.row << ", col:" << token.column << ", token: " << token.content << endl;
				//}
				//p.eval (is);
//				p.print_queue ();
	  			fb.close ();
			} else {
				cout << "ERROR: Couldn't open the file.\n";
			}
		} else {
			cout << "ERROR: You have to specify a filename.\n";
		}
	}
	catch (script_exception e) {
		cout << "error: " << e.what () << endl;
	}

/*	try {
		script_object * p1 = new script_integer_object (5);
		script_object * p2 = new script_real_object (5.0f);
		script_object * r;
		p2->multiplication (&r, p1);
		cout << "result: " << r->to_string_explicit () << endl;
	}
	catch (script_exception e) {
		cout << "error: " << e.what () << endl;
	} */

//	c = a.add

	//try {
	//	script_container a, b, c;
	//	script_container list, cell, id1, id2, id3, v1, v2;
	//	
	//	a.set_integer (1);
	//	b.set_integer (8);
	//	
	//	list.set_object (new script_collection_object ());

	//	cell.set_empty_locally ();
	//	id1.set_object (new script_string_object ("name"));
	//	v1.set_object (new script_string_object ("peter"));
	//	list.array_subscript (cell, id1);
	//	v1.assignment (cell);

	//	cell.set_empty_locally ();
	//	id2.set_object (new script_string_object ("age"));
	//	v2.set_integer (24);
	//	list.array_subscript (cell, id2);
	//	v2.assignment (cell);

	//	cell.set_empty_locally ();
	//	id3.set_object (new script_string_object ("array"));
	//	list.array_subscript (cell, id3);
	//	list.assignment (cell);

	//	cell.set_empty_locally ();
	//	list.array_subscript (cell, id2);
	//	cout << cell.to_string () << endl;

	//	cout << "-------------------\n";
	//	cout << "collector: alive objects before collect: " << __gc_count () << endl;
	//	list.collect ();
	//	__gc_collect ();
	//	cout << "collector: alive objects after collect: " << __gc_count () << endl;
	//	cout << "-------------------\n";
	//}
	//catch (script_exception e) {
	//	cout << "error: " << e.what () << endl;
	//}

	//CTreeTest * t1 = new CTreeTest ("1");
	//CTreeTest * t2 = new CTreeTest ("2");
	//CTreeTest * t3 = new CTreeTest ("3");
	//CTreeTest * t4 = new CTreeTest ("4");
	//CTreeTest * t5 = new CTreeTest ("5");

	//CTreeTest * t100 = new CTreeTest ("100");
	//CTreeTest * t200 = new CTreeTest ("200");

	//CTreeTest * root = new CTreeTest ("root");

	//root->attach (t1);
	//root->attach (t2);
	//root->attach (t3);
	//root->attach (t4);
	//root->attach (t5);

	//t5->insert_after (t100);
	//t1->insert_before (t200);
	//t3->insert_after (t200);

	//root->print ();

	//vector<unsigned long>	src_buffer;
	//vector<unsigned long>	dst_buffer;
	//unsigned long			start, count;

	//script_section_snippet * ss = new script_section_snippet ();

	//script_label_snippet * ls1 = new script_label_snippet ();
	//script_label_snippet * ls2 = new script_label_snippet ();

	//start = (unsigned long)src_buffer.size ();
	//src_buffer.push_back (10);
	//src_buffer.push_back (10);
	//src_buffer.push_back (10);
	//count = (unsigned long)src_buffer.size () - start;
	//script_code_snippet * cs10 = new script_code_snippet (start, count);

	//start = (unsigned long)src_buffer.size ();
	//src_buffer.push_back (5);
	//src_buffer.push_back (5);
	//src_buffer.push_back (5);
	//src_buffer.push_back (5);
	//count = (unsigned long)src_buffer.size () - start;
	//script_code_snippet * cs5 = new script_code_snippet (start, count);

	//start = (unsigned long)src_buffer.size ();
	//src_buffer.push_back (1);
	//src_buffer.push_back (1);
	//src_buffer.push_back (1);
	//src_buffer.push_back (1);
	//src_buffer.push_back (1);
	//src_buffer.push_back (1);
	//count = (unsigned long)src_buffer.size () - start;
	//script_code_snippet * cs1 = new script_code_snippet (start, count);

	//script_section_snippet * ss100 = new script_section_snippet ();

	//start = (unsigned long)src_buffer.size ();
	//src_buffer.push_back (110);
	//src_buffer.push_back (110);
	//src_buffer.push_back (110);
	//count = (unsigned long)src_buffer.size () - start;
	//script_code_snippet * cs110 = new script_code_snippet (start, count);

	//start = (unsigned long)src_buffer.size ();
	//src_buffer.push_back (100);
	//src_buffer.push_back (100);
	//count = (unsigned long)src_buffer.size () - start;
	//script_code_snippet * cs100 = new script_code_snippet (start, count);

	//ss100->attach (cs100);
	//ss100->attach (cs110);
	//ss100->attach (ls2);

	//ss->attach (ls1);
	//ss->attach (cs1);
	//ss->attach (ss100);
	//ss->attach (cs5);
	//ss->attach (cs10);

	//cout << " --- source ---" << endl;
	//for (vector<unsigned long>::iterator iter=src_buffer.begin (); iter!=src_buffer.end (); iter++) {
	//	cout << (* iter) << endl;
	//}

	//ss->construct (dst_buffer, src_buffer);

	//cout << " --- destination ---" << endl;
	//for (vector<unsigned long>::iterator iter=dst_buffer.begin (); iter!=dst_buffer.end (); iter++) {
	//	cout << (* iter) << endl;
	//}

	//vector<smart_pointer<str_test> >	list;

	//list.push_back (new str_test ("1"));
	//list.push_back (new str_test ("2"));
	//list.push_back (new str_test ("3"));
	//list.push_back (new str_test ("4"));
	//list.push_back (new str_test ("5"));

	//smart_pointer<str_test> a = list.back ();
	//smart_pointer<str_test> c = list.back ();

//	a->print ();

//	smart_pointer<str_test> a (new str_test ("1"));
//	smart_pointer<str_test> b, c;

//	smart_pointer<str_test> d (a);

//	b = a;
//	c = b;

//	a->print ();
//	b->print ();

//	getch ();
}
