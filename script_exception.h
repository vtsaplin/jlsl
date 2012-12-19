#ifndef __script_exception_h__
#define __script_exception_h__

#include <exception>
#include <string>
using namespace std;

class script_exception : public exception {
protected:
	string	_err;

public:
	script_exception ();
	script_exception (const char *);
	script_exception (const string);
	virtual const char * what ();
	virtual ~script_exception () throw ();
};

#endif /* __script_exception_h__ */
