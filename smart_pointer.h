#ifndef __smart_pointer_h__
#define __smart_pointer_h__

template<class T>
class smart_pointer {
public:
	class countable {
	protected:
		unsigned long	_ref_counter;

	public:
		countable () : _ref_counter (0) {
		}
		void add_ref () {
			_ref_counter++;
		}
		void release () {
			_ref_counter--;
		}
		bool is_alive () {
			if (_ref_counter) {
				return true;
			}
			return false;
		}
	};

protected:
	T *	_ptr;

public:
	smart_pointer () : _ptr (0) {
	}
	smart_pointer (T * ptr) : _ptr (ptr) {
		ptr->add_ref ();
	}
	smart_pointer (const smart_pointer& p) {
		create (p);
	}
	~smart_pointer () {
		destroy ();
	}
	void create (const smart_pointer& p) {
		_ptr = p._ptr;
		_ptr->add_ref ();
	}
	void destroy () {
		if (_ptr) {
			_ptr->release ();
			if (!_ptr->is_alive ()) {
				delete _ptr;
			}
		}
	}
	smart_pointer& operator= (const smart_pointer& p) {
		destroy (); 
		create (p);
		return (* this);
	}
	T * operator-> () {
		return _ptr;
	}
};

#endif /* __smart_pointer_h__ */
