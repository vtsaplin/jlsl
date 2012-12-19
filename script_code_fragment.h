#ifndef __script_code_fragment_h__
#define __script_code_fragment_h__

#include "tree_helper.h"

#include <vector>
using namespace std;

class script_code_fragment;

struct script_jmp {
	unsigned long			_offset;
	script_code_fragment *	_destination;
};

class script_code_fragment : public tree_helper<script_code_fragment> {
protected:
	unsigned long		_start_before;
	unsigned long		_start_after;
	unsigned long		_code_size;
	vector<script_jmp>	_jmps;

public:
	script_code_fragment ();
	~script_code_fragment ();

	void construct (vector<unsigned long>&, vector<unsigned long>&);
	void resolve (vector<unsigned long>&);

	void set_code_start (unsigned long);
	void set_code_end (unsigned long);
	void set_jmp (unsigned long, script_code_fragment *);
};

#endif /* __script_code_fragment_h__ */
