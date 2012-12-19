#include "../script_parser.h"

#include <iostream>
#include <iomanip>
using namespace std;

script_container io_getch (vector<script_container>& args) {
	script_container c;
	string s;
	cin >> s;
	c.set_object (new script_string_object (s));
	return c;
}
script_predefined_function io_getch_def ("getch", io_getch, 0);

// echo
script_container io_echo (vector<script_container>& args) {
	script_container c;
	for (int i=0; i<(int)args.size (); i++) {
		cout << args [i].to_string ();
	}
	return c;
}
script_predefined_function io_echo_def ("echo", io_echo, 0);

// print
script_container io_print (vector<script_container>& args) 
{
	script_container	c;
	unsigned long		count = 1;

	string format = args [0].to_string ();
	for (int i=0; i<(int)format.size (); i++) {
		if (format [i] == '%') {
			if (count < args.size ()) {
				i++;
				if (format [i] == 'i' || format [i] == 'd') {
					cout << args [count].to_integer ();
				} else if (format [i] == 'u') {
					cout << args [count].to_unsigned_integer ();
				} else if (format [i] == 'h') {
					cout << hex << args [count].to_unsigned_integer () << dec;
//				} else if (format [i] == 'H') {
//					cout << hex << uppercase << args [count].to_unsigned_integer ()  << dec << nouppercase;
				} else if (format [i] == 'f') {
					cout << args [count].to_single ();
				} else if (format [i] == 's') {
					cout << args [count].to_string ();
				} else {
					throw script_exception ("print (): undefined format specifier.");
				}
				count++;
			} else {
				throw script_exception ("print (): number of agruments does not correspond to format.");
			}
		} else {
			cout << format [i];
		}
	}

	return c;
}
script_predefined_function io_print_def ("print", io_print, 1);
