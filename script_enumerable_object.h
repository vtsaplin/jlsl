#ifndef __script_enumerable_object_h__
#define __script_enumerable_object_h__

#include "script_predefined_function.h"
#include "script_object.h"
#include "script_container.h"

#include <string>
using namespace std;

class script_enumerable_object : virtual public script_object {
public:
	virtual void begin ();
	virtual void end ();
	virtual void backward ();
	virtual void forward ();
	virtual void get_current_key (script_container&);
	virtual void current (script_container&);
	virtual void remove ();
	virtual bool is_end ();
	virtual unsigned long count ();
};

#endif /* __script_enumerable_object_h__ */
